#include "hi.h"
#include <stdio.h>


int main(int argc, char **argv) {
	void *context = NULL;
	int err;

	if((err = hi_init(&context)) != OK) {
		printf("hi_init returned %d\n", err);
		return err;
	}

	printf("hi_init ok\n");

	// Loop until libhi tells us to exit
	while(hi_update(context) == 0);
	// context is an invalid pointer at this point, don't use it again.
	context = NULL;
	printf("hi_update returned nonzero, we're done!\n");
	hi_destroy(context);

	return 0;
}
