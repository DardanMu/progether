/*
 * libcurses_functions.h
 *
 *  Created on: 23/10/2012
 *      Author: fragmachine
 */

#ifndef LIBCURSES_FUNCTIONS_H_
#define LIBCURSES_FUNCTIONS_H_

#include <panel.h>

#include <libNetworkInfo.h>
#include <libMemInfo.h>
#include <defines.h>


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


#endif /* LIBCURSES_FUNCTIONS_H_ */
