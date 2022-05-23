/*
 ============================================================================
 Name        : mallocAssessment.c
 Author      : AhmedAtef
 Version     :
 Copyright   : AhmedAtef
 Description : Dynamic Allocation
 ============================================================================
 */

#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "mymalloc.h"

struct mm_block_def
{
	struct mm_block_def *next;
	struct mm_block_def *prev;
	int size;
	int free;    // this flag is used to know whether the block described by the metadata structure if free or not  if free it is set to 1 otherwise 0//
	unsigned char *buffer;
};
struct mm_block_def *curr;
struct mm_block_def*freeList=(void*)memory;


void initmyMalloc(struct mm_block_def *mm_block_def){
	mm_block_def->size= sizeof(memory) - sizeof(struct mm_block_def);// or16000-sizeof(struct mm_block_def);
	mm_block_def->free=1;
	mm_block_def->next=NULL;
	mm_block_def->prev=NULL;
	mm_block_def->buffer = (unsigned char *)(memory + sizeof(struct mm_block_def));
}

void split (struct mm_block_def *fitting_slot,size_t size){
	struct mm_block_def *new=(void*)((void*)fitting_slot+size+sizeof(struct mm_block_def));
	new->size=(fitting_slot->size)-size-sizeof(struct mm_block_def);
	new->free=1;
	new->next=fitting_slot->next;
	fitting_slot->size=size;
	fitting_slot->free=0;
	fitting_slot->next=new;
}

void *mymalloc(int size){
	struct mm_block_def *link = (struct mm_block_def*) malloc(sizeof(struct mm_block_def));
	void *result;                               //This result pointer is to return the starting address of the allocated chunk of memory.

	 curr=freeList;                            //Now we make the temporary pointer curr to point to the start of the metadata block list.
	//If this condition is met, the metadata block we checked cannot be used for the allocation. So we execute the following statements.
	//That is you go on checking one metadata block at a time.
	 while((((curr->size)<size)||((curr->free)==0))&&(curr->next!=NULL))
	{
		 link->prev=curr;
		 curr=curr->next;
	   printf("One block checked\n");
	 }
	 //If this condition is met, the metadata block we checked refers to a chunk of memory that exactly fits the required size.
	 //So set the free flag to 0, indicating that it is allocated. Then return the starting address of the block of allocated memory.
	 if((curr->size)==size)
	 {
		 curr->free=0;
	    result=(void*)(++curr);
	    printf("Exact fitting block allocated\n");
	    return result;
	  }
	 //If this condition is met, the metadata block we checked refers to a chunk of memory that is of size greater than what is required.
	 //So invoke the split() function to allocate only the block which is required and then return the starting address of the block of allocated memory.
	 else if((curr->size)>(size+sizeof(struct mm_block_def)))
	 {
	    split(curr,size);
	    result=(void*)(++curr);
	    printf("Fitting block allocated with a split\n");
	    return result;
	  }
     //Else it means that there is no sufficient memory to allocate so you should return a NULL pointer.
	  else{
	    result=NULL;
	    printf("Sorry. No sufficient memory to allocate\n");
	    return result;
	   }
}

void merge(){
 struct mm_block_def *buffer;
 buffer=freeList;
 while(buffer && buffer->next){
  if (buffer + sizeof(struct mm_block_def)+ buffer->size == buffer->next){
	  buffer->size+=(buffer->next->size)+sizeof(struct mm_block_def);
	  buffer->next=buffer->next->next;
  }
  else{
	  buffer->prev=buffer;
	  buffer=buffer->next;
 }
}
}

void myfree(void*buffer){
	if(((void*)memory<=buffer)&&(buffer<=(void*)(memory+16000))){
	  struct mm_block_def* curr=buffer;
	  --buffer;
	  curr->free=1;
	  merge();
	 }
	 else printf("Please provide a valid pointer allocated by MyMalloc\n");
	}

void printmyMallocFreeList(){
	struct mm_block_def *ptr;
    while(ptr != NULL)
  {
	 printf(" %d size:",ptr->size);
	 printf(" %p next:",ptr->next);
	 printf(" %p prev:",ptr->prev);
	 printf(" %p buffer:",ptr->buffer);

  }

     printf(" [null]\n");
}

