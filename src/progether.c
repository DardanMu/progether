#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <panel.h>

#include <defines.h>
#include <libMemInfo.h>
#include <libNetworkInfo.h>
#define NLINES 10
#define NCOLS 40


void init_curses()
{
	/* Initialize curses */
		initscr();
		start_color();
		cbreak();
		noecho();
		keypad(stdscr, TRUE);

	/* This prevents getch() from hanging the while loop */
		nodelay(stdscr, true);
		wtimeout(stdscr, true);

}

void init_wins(WINDOW **wins, int n, int x, int y)
{
	/* Create n windows */
	for(int i = 0; i < n; ++i)
	{
		wins[i] = newwin(NLINES, NCOLS, y, x);
	}
}

void init_panels(PANEL **panels, WINDOW** windows, int n)
{	/* Attach a panel to each window */
	for (int i = 0; i < n; ++i) {
		panels[i] = new_panel(windows[i]);
	}
}


/* Show the window with a border and a label */
void draw_box_with_label(WINDOW *win, char *label, int label_color, int x, int y)
{
	int height, width;

	getmaxyx(win, height, width);

	box(win, x, y);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	mvwprintw(win, 1, 1, "%s", label);
}



void print_in_network_box(WINDOW *win, NetworkInfo *interface_device)
{
	int row = 4;
	int col = 4;

	mvwprintw(win, 1, 10, "%s", interface_device->device_name);

	mvwprintw(win, row++,col,"Bytes Recieved: %ld\r", interface_device->bytes_recieved);
	mvwprintw(win,row++,col,"Packets Recieved: %ld\r", interface_device->packets_recieved);
	mvwprintw(win,row++,col,"Bytes Sent: %ld\r", interface_device->bytes_sent);
	mvwprintw(win,row++,col,"Packets Sent: %ld\r", interface_device->packets_sent);
	refresh();
}


int main()
{

	NetworkInfo *interface_device;
	interface_device = NULL;
	char device_names[20][20];

	/* We'll use interface_num to determine how many windows and panels to create */
	int interface_num = get_available_interfaces(device_names, 20);
	int ch;

	/* Allocate memory for the struct */
	interface_device = create_networking_struct(interface_device);

	WINDOW *my_wins[interface_num];
	PANEL  *my_panels[interface_num];

	/* Set up curses and the windows */
	init_curses();
	init_wins(my_wins, interface_num, 0, 0);
	init_panels(my_panels, my_wins, interface_num);


	/* Show usage message on the screen */
	mvprintw(LINES - 3, 0, "Press Tab to scroll through devices");
	mvprintw(LINES - 2, 0, "'q' to Exit");
	doupdate();

	int exit = 1;
	int window = 0;

	while(exit)
	{

		show_panel(my_panels[window]);

				do {
					/* Clear values in struct just in case */
					draw_box_with_label(my_wins[window], "Interface:", 1, 0, 0);
					init_networking_struct(interface_device);

					get_network_info(interface_device, device_names[window]);
					print_in_network_box(my_wins[window], interface_device);

					update_panels();
					doupdate();
					usleep(9000);

				}while ((ch=getch()) == ERR);
				/* ERR is the value returned by getch() when nodelay() is set and there		*/
				/* are there are no characters waiting in the buffer. 						*/
				/* We can loop on ERR and it will break whenever the user inputs something 	*/

				if (  ch == (int)'q')
					exit = 0;

				/* If the char is tab (9) increment window to scroll through devices */
				if (ch == 9)
						{
							window++;

							if (window == interface_num)
								window = 0;
						}

	}
	free(interface_device);
	endwin();

	return 0;
}

