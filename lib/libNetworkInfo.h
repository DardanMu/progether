/*
 * libNetworkInfo.h
 *
 *  Created on: 22/10/2012
 *      Author: fragmachine
 */

#ifndef LIBNETWORKINFO_H_
#define LIBNETWORKINFO_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <defines.h>

typedef struct {

	char device_name[50];
	long unsigned int bytes_recieved;
	long unsigned int bytes_sent;
	long unsigned int packets_recieved;
	long unsigned int packets_sent;

}NetworkInfo;

void init_networking_struct(NetworkInfo *device)
{
	/* Initialize Variables */
	strcpy(device->device_name,  "");
	device->bytes_recieved = 0;
	device->bytes_sent = 0;
	device->packets_recieved = 0;
	device->packets_sent = 0;
}

NetworkInfo *create_networking_struct(NetworkInfo *device)
{
	/* Allocate Memory and init NetworkInfo struct */
	device = (NetworkInfo *)malloc(sizeof(NetworkInfo));
	init_networking_struct(device);

	return device;
}


int get_network_info(NetworkInfo *device, char device_name[])
{
	char buffer[2048];
	char *match;
	size_t bytes_read;
	FILE *fp;

	/* Format for sscanf. The '*' characters skip the unwanted ints. */
	char sscanf_format[] = ": %d %d %*d%*d%*d%*d%*d%*d%d%d";
	char sscanf_key[200];

	/* Concatenate the device name and the format so we can just pass the device name into the function */
	sprintf(sscanf_key, "%s%s", device_name, sscanf_format);

	fp = fopen("/proc/net/dev", "r");
	bytes_read = fread(buffer, 1, sizeof(buffer), fp);
	fclose(fp);

	/* If nothing is read or the buffer is totally full then bail */
	if (bytes_read == 0 || bytes_read == sizeof(buffer))
	{
		perror("Error Reading Buffer (get_network_info)\n");
		return 0;
	}

	buffer[bytes_read] = '\0';

	/* Find the line for desired value */
	match = strstr(buffer, device_name);

	if (match == NULL)
		{
			perror("Error parsing value (get_network_info)\n");
			return 0;
		}

	sscanf (match, sscanf_key,
			&device->bytes_recieved,
			&device->packets_recieved,
			&device->bytes_sent,
			&device->packets_sent);

	strcpy(device->device_name, device_name);

	return 0;

}

int get_available_interfaces(char interface_names[][20], int array_size)
{
	/* Gets interface names from proc/net/dev. Returns the number of interface names read or 0 on error */

		char *token;
		char buffer[1024];
		int interface_num = 0;

		FILE *fp = NULL;

		fp = fopen("/proc/net/dev", "r");

		if (fp == NULL)
		{
			perror("Error reading file (get_available_interfaces)\n");
			return 0;
		}

		while(fgets(buffer, 1024, fp) != NULL)
		{
			token = strtok(buffer, ":");

			if (interface_num >= array_size)
			{
				perror("Too many interfaces (get_avaliable_interfaces)\n");
				return interface_num;
			}

			/* The first token recieved is not what we want, this prevents the info being read */
			if (strlen(token) < 10)
			{
				strcpy(interface_names[interface_num++], token);
			}
		}

		return interface_num;
}

void print_network_info(NetworkInfo *device)
{
	printf("Packets Received: %ld\nBytes Received: %ld\nPackets Sent: %ld\nBytes Sent: %ld\n"
			"",
			device->packets_recieved,
			device->bytes_recieved,
			device->packets_sent,
			device->bytes_sent);
}



#endif /* LIBNETWORKINFO_H_ */
