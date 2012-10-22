/*
 * libMemInfo.h
 *
 *  Created on: 22/10/2012
 *      Author: fragmachine
 */

#ifndef LIBMEMINFO_H_
#define LIBMEMINFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <defines.h>

typedef struct MemInfo
{
	unsigned int total;
	unsigned int free;
	unsigned int cached;
	unsigned int active;
	unsigned int inactive;
	unsigned int swap_total;
	unsigned int swap_free;

}memInfo;

memInfo *init_memory_struct(memInfo *memory)
{
	memory->total = 0;
	memory->free = 0;
	memory->cached = 0;
	memory->active = 0;
	memory->inactive = 0;
	memory->swap_total = 0;
	memory->swap_free = 0;

	return memory;
}

memInfo *create_memory_struct(memInfo *memory)
{
	/* Creates and initializes the struct */

	memory = (memInfo *)malloc(sizeof(memInfo));

	memory = init_memory_struct(memory);

	return memory;
}


int get_mem_info(memInfo *memory)
{
	char buffer[2048];
	char *match;
	size_t bytes_read;
	int sscanf_values[7];
	FILE *fp;


	char strstr_keys[][KEY_STRING_SIZE] = {
			"MemTotal",
			"MemFree",
			"Cached",
			"Active",
			"Inactive",
			"SwapTotal",
			"SwapFree",
	};

	char sscanf_keys[][KEY_STRING_SIZE] = {
			"MemTotal: %i",
			"MemFree: %i",
			"Cached: %i",
			"Active: %i",
			"Inactive: %i",
			"SwapTotal: %i",
			"SwapFree: %i",
	};



	fp = fopen("/proc/meminfo", "r");

	bytes_read = fread(buffer, 1, sizeof(buffer), fp);

	/* If nothing is read or the buffer is totally full then bail */
	if (bytes_read == 0 || bytes_read == sizeof(buffer))
	{
		perror("Error Reading Buffer (get_mem_info)\n");
		return 1;
	}

	buffer[bytes_read] = '\0';

	for (int i = 0; i < sizeof(sscanf_keys) / KEY_STRING_SIZE; i++) {
		/* Find the line for desired value */
		match = strstr(buffer, strstr_keys[i]);

			if (match == NULL)
			{
				perror("Error parsing value (get_mem_info)\n");
				return 1;
			}

			/* Extract value */
			sscanf (match, sscanf_keys[i], &sscanf_values[i]);

			/* Reset match to NULL just in case */
			match = NULL;
	}

	/* Assign to memory struct */
	memory->total = sscanf_values[0];
	memory->free = sscanf_values[1];
	memory->cached = sscanf_values[2];
	memory->active = sscanf_values[3];
	memory->inactive = sscanf_values[4];
	memory->swap_total = sscanf_values[5];
	memory->swap_free = sscanf_values[6];

	fclose(fp);
	return 0;
}

void print_memory_info(memInfo *memory)
{
	printf("Total: %d\nFree: %d\nCached: %d\nActive: %d\nInactive: %d\nSwap: %d\nSwap Free: %d\n",
			memory->total,
			memory->free,
			memory->cached,
			memory->active,
			memory->inactive,
			memory->swap_total,
			memory->swap_free);
}


#endif /* LIBMEMINFO_H_ */
