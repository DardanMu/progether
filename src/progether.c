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
	ppp0 = wlan0 = NULL;

	ppp0 = create_net(ppp0);
	wlan0 = create_net(wlan0);

	get_network_info(ppp0, "ppp0");
	get_network_info(wlan0, "wlan0");


	print_network_info(wlan0);

	free(ppp0);
	free(wlan0);

	return EXIT_SUCCESS;
}
