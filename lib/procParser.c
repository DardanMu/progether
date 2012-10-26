#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>



typedef struct{
	int key; //aka pid #
	int hashedKey;
	char pidName[256];
	char state;
	int threads;
	int memTotal;
	int memRam;
	int cpuUsage;
}hashEntry;


void get_process_name(char process_path[], char buffer[], hashEntry *ph)
{
	char *p = NULL;

	/* Find desired line */
	p = strstr(buffer, "Name:");

	if(p)
		sscanf(p, "Name:\t%s", ph->pidName);
}

void get_process_state(char process_path[], char buffer[], hashEntry *ph)
{
	char *p = NULL;

	/* Find desired line */
	p = strstr(buffer, "State:");

	if (p)
		/* Store value in struct */
		sscanf(p, "State:\t%c", &ph->state);

}

void get_process_memtotal(char process_path[], char buffer[], hashEntry *ph)
{
	 char *p = NULL;

	 /* Find desired line */
	 p = strstr(buffer, "VmSize:");

	 if (p)
		 /* Store value in struct */
		sscanf(p, "VmSize:\t%d", &ph->memTotal);

}

void get_process_threads(char process_path[], char buffer[], hashEntry *ph)
{
	 char *p = NULL;

	 /* Find desired line */
	 p = strstr(buffer, "Threads:");

	 if (p)
		 /* Store value in struct */
		 sscanf(p, "Threads:\t%d", &ph->threads);

}

void get_process_memram(char process_path[], char buffer[], hashEntry *ph)
{
	 char *p = NULL;

	 /* Find desired line */
	 p = strstr(buffer, "VmRSS:");

	 if (p)
		 /* Store value in struct */
		 sscanf(p, "VmRSS:\t%d", &ph->memRam);

}

void init_hash_entry(hashEntry *ph)
{
	strcpy(ph->pidName, "");
	ph->state = ' ';
	ph->memTotal = 0;
	ph->threads = 0;
	ph->memTotal = 0;
	ph->memRam = 0;
}

void print_process(hashEntry *ph)
{
	printf("Name: %s\nState: %c\nThreads: %d\nMemTotal: %d\nMemRam: %d\n\n",
			ph->pidName,
			ph->state,
			ph->threads,
			ph->memTotal,
			ph->memRam);
}

void get_process_data(hashEntry *ph, char process_name[])
{	/* Gets a processes's information from /proc/<process_name>/status. 						*/
	/* Reads the entire file into buffer, then selects each piece of data and adds to struct.	*/


	int fd = open(process_name, O_RDONLY);
	int bytes_read;

	/* If something goes wrong bail */
	if (fd == -1)
		return;

	char buffer[1024];

	/* Initialize values in hash */
	init_hash_entry(ph);

	bytes_read = read(fd, buffer, 1024);

	/* If nothing read, bail */
	if(bytes_read < 1)
		return;

	buffer[bytes_read] = '\0';

	/* Get all the data */
	get_process_name(process_name, buffer, ph);
	get_process_state(process_name, buffer, ph);
	get_process_memtotal(process_name, buffer, ph);
	get_process_threads(process_name, buffer, ph);
	get_process_memram(process_name, buffer, ph);


	/* Done */
	close(fd);
}


int main(void)
{
	struct dirent **dir_entries;
	int n, len;
	const int BUFFER_SIZE = 1024;
	char path_buffer[BUFFER_SIZE];

	hashEntry *ph;
	ph = malloc(sizeof(hashEntry));


	n = scandir("/proc", &dir_entries, 0, alphasort);


	if( n == -1)
	{
		perror("Error parsing proc (<function_name>)\n");
		return 1;
	}

	while(n--)
	{
		/* If the first char is a digit it should be a process directory 	*/
		/* Might want to add another check here... 							*/
		if (isdigit(dir_entries[n]->d_name[0]))
		{
			len = snprintf(path_buffer, BUFFER_SIZE, "/proc/%s/status", dir_entries[n]->d_name);
			if(len > BUFFER_SIZE || len < 1)
			{
				perror("Error reading file\n");

			} else {

				/* If all is good get the data and print it */
				get_process_data(ph, path_buffer);
				print_process(ph);
			}
		}

		/* Free the entry now so don't have to do it later */
		free(dir_entries[n]);
	}

	/* Free all the rest of the memory */
	free(dir_entries);
	free(ph);

	return 0;
}
