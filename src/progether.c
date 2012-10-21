#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

float get_mem_total()
{
		char buffer[2048];
		char *match;
		size_t bytes_read;
		float value;
		FILE *fp;

		fp = fopen("/proc/meminfo", "r");

		bytes_read = fread(buffer, 1, sizeof(buffer), fp);

		/* If nothing is read or the buffer is totally full then bail */
		if (bytes_read == 0 || bytes_read == sizeof(buffer))
		{
			perror("Nothing Read or overflow\n");
			return 0;
		}

		buffer[bytes_read] = '\0';

		/* Find the line for desired value */
		match = strstr(buffer, "MemTotal");

		if (match == NULL)
		{
			perror("Memtotal line not found\n");
			return 0;
		}

		/* Extract value */
		sscanf (match, "MemTotal: %f", &value);

		return value;
}

float get_mem_free()
{
		char buffer[2048];
		char *match;
		size_t bytes_read;
		float value;
		FILE *fp;

		fp = fopen("/proc/meminfo", "r");

		bytes_read = fread(buffer, 1, sizeof(buffer), fp);

		/* If nothing is read or the buffer is totally full then bail */
		if (bytes_read == 0 || bytes_read == sizeof(buffer))
		{
			perror("Nothing Read or overflow\n");
			return 0;
		}

		buffer[bytes_read] = '\0';

		/* Find the line for desired value */
		match = strstr(buffer, "MemFree");

		if (match == NULL)
		{
			perror("Memtotal line not found\n");
			return 0;
		}

		/* Extract value */
		sscanf (match, "MemFree: %f", &value);

		return value;
}



int main(void) {

	for (int i = 0; i < 100; ++i) {

		 printf("\rTotal: %f Free: %f", get_mem_total(), get_mem_free());
		 fflush(stdout);
		 usleep(90000);

	}




	return EXIT_SUCCESS;
}
