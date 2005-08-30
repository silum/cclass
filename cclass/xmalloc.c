/* $Id$
 * Copyright (C) 2005 Deneys S. Maartens <dsm@tlabs.ac.za>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
/**
 * @file
 * @brief Memory allocation function definition
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xmalloc.h"

USE_XASSERT

#ifndef DOXYGEN_SKIP
#define ALIGNMENT (sizeof(int))
#define DOALIGN(num) (((num)+ALIGNMENT-1)&~(ALIGNMENT-1))
compiler_assert(ISPOWER2(ALIGNMENT));
#endif

/* Prefix structure before every heap object */
#ifndef DOXYGEN_SKIP
typedef struct prefix_tag {
	struct prefix_tag *prev;	/* previous object in heap   */
	struct prefix_tag *next;	/* next object in heap       */
	struct postfix_tag *postfix;	/* ptr to postfix object     */
	const char *file;		/* file name ptr or 0        */
	long line;			/* line number or 0          */
	void *mem;			/* xnew() ptr of object      */
	classdesc *class;		/* class descriptor ptr or 0 */
} prefix;
#endif /* DOXYGEN_SKIP */

/* Postfix structure after every heap object */
#ifndef DOXYGEN_SKIP
typedef struct postfix_tag {
	struct prefix_tag *prefix;
} postfix;
#endif /* DOXYGEN_SKIP */

/* Verify alignment of prefix structure */
compiler_assert(!(sizeof(prefix) % ALIGNMENT));

/* Points to first object in linked list of heap objects */
#ifndef DOXYGEN_SKIP
static prefix *heap = 0;
#endif /* DOXYGEN_SKIP */

/* Local prototypes */

/**
 * @brief Add heap object to linked list)
 *
 * Add the given heap object into the doubly linked list of heap
 * objects
 *
 * @param p  prefix pointer to heap object
 */
static void list_insert(prefix *p);

/**
 * @brief Remove heap object from linked list)
 *
 * Remove the given heap object from the doubly linked list of heap
 * objects
 *
 * @param p  prefix pointer to heap object
 */
static void list_remove(prefix *p);

/**
 * @brief Verify heap pointer)
 *
 * Verify that a pointer points into that heap to a valid object in the
 * heap
 *
 * @param p  heap pointer to validate
 *
 * @return heap pointer is valid (true) or not (false)
 */
static bool list_verify(void *p);

/**
 * @brief Render description of heap object)
 *
 * Render a text description for the given heap object
 *
 * @param p  prefix pointer to heap object
 * @param buffer  where to place text description
 */
static void render(prefix *p, char *buffer);

void
list_insert(prefix *p)
{
	/* add before current head of list */
	if (heap) {
		p->prev = heap->prev;
		(p->prev)->next = p;
		p->next = heap;
		(p->next)->prev = p;
	}

	/* else first node */
	else {
		p->prev = p;
		p->next = p;
	}

	/* make new item head of list */
	heap = p;
}

void
list_remove(prefix *p)
{
	/* Remove from doubly linked list */
	(p->prev)->next = p->next;
	(p->next)->prev = p->prev;

	/* Possibly correct head pointer */
	if (p == heap) {
		heap = ((p->next == p) ? 0 : p->next);
	}
}

bool
list_verify(void *mem)
{
	bool ok = false;

	if (mem) {
		xassert(xtestptr(mem)) {
			prefix *p = (prefix *) mem - 1;
			xassert(p->mem == mem) {
				xassert(p->postfix->prefix == p) {
					ok = true;
				}
			}
		}
	}

	return (ok);
}

void
render(prefix *p, char *buffer)
{
	if (p->mem == &p[1]) {
		sprintf(buffer, "%8p ", p);
		if (p->file) {
			sprintf(buffer + strlen(buffer), "%12s %4ld ",
				p->file, p->line);
		}
		if (p->class) {
			sprintf(buffer + strlen(buffer), "%s",
				p->class->name);
		}
	} else {
		strcpy(buffer, "(bad)");
	}
}

void *
xfree(void *mem)
{
	if (list_verify(mem)) {
		prefix *p = (prefix *) mem - 1;
		size_t size = (char *) (p->postfix + 1) - (char *) p;
		list_remove(p);
		memset(p, 0, size);
		free(p);
	}

	return 0;
}

void *
xnew(size_t size,
     classdesc *class,
     const char *file,
     int line)
{
	prefix *p;
	size = DOALIGN(size);
	p = (prefix *) malloc(sizeof(prefix) + size + sizeof(postfix));
	if (p) {
		list_insert(p);
		p->postfix = (postfix *) ((char *) (p + 1) + size);
		p->postfix->prefix = p;
		p->file = file;
		p->line = line;
		p->mem = p + 1;
		p->class = class;
		memset(p->mem, 0, size);
	} else {
		/* Report out of memory error */
		asserterror();
	}

	return (p ? p + 1 : 0);
}

void *
xrealloc(void *old,
	 size_t size,
	 const char *file,
	 int line)
{
	void *new = 0;

	/* Try to realloc */
	if (old) {
		if (list_verify(old)) {
			prefix *p = (prefix *) old - 1;
			prefix *new_p;

			/* Try to reallocate block */
			list_remove(p);
			memset(p->postfix, 0, sizeof(postfix));
			size = DOALIGN(size);
			new_p = (prefix *) realloc(p, sizeof(prefix) +
						   size + sizeof(postfix));

			/* Add new (or failed old) back in */
			p = (new_p ? new_p : p);
			list_insert(p);
			p->postfix = (postfix *) ((char *) (p + 1) + size);
			p->postfix->prefix = p;
			p->mem = p + 1;

			/* Finish */
			new = (new_p ? &new_p[1] : 0);
			if (!new) {
				/* Report out of memory error */
				asserterror();
			}
		}
	}

	/* Else try new allocation */
	else {
		new = xnew(size, 0, file, line);
	}

	/* Return address to object */
	return new;
}

void *
xstrdup(const char *s,
	const char *file,
	int line)
{
	void *ret = 0;

	if (s) {
		size_t size = (size_t) (strlen(s) + 1);
		ret = xnew(size, 0, file, line);
		if (ret) {
			memcpy(ret, s, size);
		}
	}
	return ret;
}

bool
xtestptr(void *mem)
{
	return ((mem) && (!((long) mem & (ALIGNMENT - 1))));
}

int
xwalkheap()
{
	int alloced = 0;

	if (heap) {
		prefix *p = heap;
		while (list_verify(&p[1])) {
			char buffer[100];
			render(p, buffer);

			++alloced;

			/* print out buffer */
			printf("%s: %s\n", __func__, buffer);
			p = p->next;
			if (p == heap) {
				break;
			}
		}
	}

	return alloced;
}

