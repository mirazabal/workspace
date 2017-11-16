#include "naive_malloc.h"
#include <unistd.h>

static int init = 0;

struct mem_ctrl_blck{
	size_t size;
	size_t in_use;
	struct mem_ctrl_blck* next;
	struct mem_ctrl_blck* previous;
	
};


static void* actual_heap_pos = NULL;
static void* first_position = NULL;

void* enhance_heap(size_t size, void* previous_addr)
{

	void* heap_pos = sbrk(0);

	void* new_addr;
	new_addr = heap_pos + sizeof(struct mem_ctrl_blck) + size;

	int ret_val = brk(new_addr);
	if( brk(new_addr) == -1)
		return NULL;

	((struct mem_ctrl_blck*)(heap_pos+1))->size = size;
	((struct mem_ctrl_blck*)(heap_pos+1))->next = NULL;
	((struct mem_ctrl_blck*)(heap_pos+1))->previous = previous_addr;

	if(previous_addr != NULL)
		((struct mem_ctrl_blck*)(heap_pos+1))->previous->next = heap_pos + 1; 

	((struct mem_ctrl_blck*)(heap_pos+1))->in_use = 1;

	actual_heap_pos = heap_pos + 1;

	return sizeof(struct mem_ctrl_blck) + heap_pos + 1;
}

void* first_time(size_t size){
	
	first_position = sbrk(0) + 1;
	void* ret_addr = enhance_heap(size, NULL);
	init=1;
	return ret_addr;
}

void check_previous_blck_free(struct mem_ctrl_blck* blck)
{
	if(blck->previous->in_use == 0 ){
		blck->previous->size = blck->previous->size + blck->size + sizeof(struct mem_ctrl_blck);
		blck->next->previous = blck->previous;
		blck->previous->next = blck->next;
	}
}


void naive_free( void* ptr)
{
	if(ptr == NULL)
		return;

	struct mem_ctrl_blck* blck = ((struct mem_ctrl_blck*)(ptr - sizeof(struct mem_ctrl_blck))); 
/*	
	if(blck->previous != NULL ){
		check_previous_blck_free(blck);		
	}

	if(blck->next != NULL){
	
	}
*/

	blck->in_use =0;
}

void* naive_malloc(size_t size){

	if(size == 0)
		return NULL;

	if(!init)
		return first_time(size);

	void* loop_addr = first_position;
	while(loop_addr != actual_heap_pos ){
		if (((struct mem_ctrl_blck*)loop_addr)->in_use == 0 && (((struct mem_ctrl_blck*)loop_addr)->size  >= size)){
				((struct mem_ctrl_blck*)loop_addr)->in_use = 1; 
				return loop_addr + sizeof(struct mem_ctrl_blck);
		}
		loop_addr = ((struct mem_ctrl_blck*)loop_addr)->next;
	}
		
	return enhance_heap(size, actual_heap_pos);
}

