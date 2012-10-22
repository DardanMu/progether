#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <defines.h>
#include <libMemInfo.h>

int main(void) {

	memInfo *memStruct = NULL;

	memStruct = create(memStruct);

	get_mem_info(memStruct);

	printf("Total %d", memStruct->total);


	free(memStruct);

	return EXIT_SUCCESS;
}
