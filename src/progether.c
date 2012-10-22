#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include <defines.h>
#include <libMemInfo.h>
#include <libNetworkInfo.h>

int main(void) {

	NetworkInfo *ppp0, *wlan0;
	memInfo *memory;
	ppp0 = wlan0 = NULL;
	memory = NULL;

	memory = create_memory_struct(memory);
	get_mem_info(memory);

	ppp0 = create_networking_struct(ppp0);
	wlan0 = create_networking_struct(wlan0);
	get_network_info(ppp0, "ppp0");
	get_network_info(wlan0, "wlan0");

	printf("wlan0:\n");
	print_network_info(wlan0);

	printf("\nppp0:\n");
	print_network_info(ppp0);

	printf("\nMemory Info:\n");
	print_memory_info(memory);


	free(ppp0);
	free(wlan0);

	return EXIT_SUCCESS;
}
