#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <kernel/tty.h>

typedef uint32_t     page_t;
typedef uint32_t     pde_t;

typedef page_t      *pagetable_t;
typedef pde_t       *pagedir_t;

void paging_init();
void *request_page();
void *request_pages(size_t num_pages);
void free_page(void *ptr);
void free_pages(void *ptr, size_t num_pages);


void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#endif // !_KERNEL_PAGING_H
