#include "naive_malloc.h"


struct foo{
	char a[4];
	int b;
	double c;


};


int main()
{
	void* ptr1 =  naive_malloc( 4096*sizeof(struct foo));
	void* ptr2 =  naive_malloc( 2 * 4096*sizeof(struct foo));
	void* ptr3 =  naive_malloc( 3 * 4096*sizeof(struct foo));

	naive_free(ptr1);
	naive_free(ptr2);
	void* ptr4 =  naive_malloc( 3*4096*sizeof(struct foo));
	naive_free(ptr4);
	ptr4 =  naive_malloc( 2*4096*sizeof(struct foo));

	naive_free(ptr3);
	naive_free(ptr4);


	return 0;
}
