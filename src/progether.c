#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include <defines.h>
#include <libMemInfo.h>
#include <libNetworkInfo.h>

int main(void) {

	NetworkInfo *interface_device;
	memInfo *memory;
	interface_device = NULL;
	memory = NULL;

	char interface_names[20][20];
	int interface_num = 0;

	interface_num = get_available_interfaces(interface_names, 20);

	interface_device = create_networking_struct(interface_device);

	for (int i = 0; i < interface_num; ++i) {
		get_network_info(interface_device, interface_names[i]);

		printf("\nDevice: %s\n", interface_names[i]);
		print_network_info(interface_device);
		init_networking_struct(interface_device);
	}

	memory = create_memory_struct(memory);
	get_mem_info(memory);
	printf("\nMemory:\n");
	print_memory_info(memory);

	free(interface_device);
	free(memory);

	return EXIT_SUCCESS;
}
