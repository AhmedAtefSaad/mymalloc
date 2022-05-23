/*
 * mymalloc.h
 *
 *  Created on: May 21, 2022
 *      Author: AhmedAtef
 */

#ifndef MYMALLOC_H_
#define MYMALLOC_H_
#define MAX_MALLOC_SIZE (1024*1024*16)

#include<stdio.h>
#include<stddef.h>

unsigned char memory[MAX_MALLOC_SIZE];
void initmyMalloc();
void *mymalloc(int size);
void myfree(void*buffer);
void printmyMallocFreeList();


#endif /* MYMALLOC_H_ */
