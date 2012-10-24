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

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void edit_network_window(WINDOW *win, NetworkInfo *interface_device);
void print_in_network_box(WINDOW *win, int starty, int startx, int width, NetworkInfo *interface_device, chtype color);

int main()
{	WINDOW *my_wins[3];
	PANEL  *my_panels[3];
	int ch;


	NetworkInfo *interface_device;
	interface_device = NULL;

	char device_names[20][20];

	interface_device = create_networking_struct(interface_device);
	get_available_interfaces(device_names, 20);


	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_wins(my_wins, 3);

	/* Attach a panel to each window */ 	/* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */


	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	attron(COLOR_PAIR(4));
	mvprintw(LINES - 3, 0, "Show or Hide a window with 'a'(first window)  'b'(Second Window)  'c'(Third Window)");
	mvprintw(LINES - 2, 0, "'q' to Exit");

	attroff(COLOR_PAIR(4));
	doupdate();

	char str[200];
	int testn = 0;

	/* This prevents getch() from hanging the while loop */
	nodelay(stdscr, true);
	nodelay(my_wins[0], true);
	nodelay(my_wins[1], true);
	nodelay(my_wins[2], true);
	wtimeout(my_wins[0], true);
	wtimeout(my_wins[1], true);
	wtimeout(my_wins[2], true);
	wtimeout(stdscr, true);

	int exit = 1;

	while(exit)
	{
		ch = getch();

			show_panel(my_panels[0]);
				do {
					ch=getch();
					get_network_info(interface_device, device_names[0]);
					edit_network_window(my_wins[0], interface_device);
					update_panels();
					doupdate();
					usleep(9000);

				}while (ch==ERR);

			if (ch == 'b')
			{
				show_panel(my_panels[1]);

				do {
					ch=getch();
					sprintf(str, "Panel two %d\r", testn++);
					//edit_window(my_wins[1], str);
					update_panels();
					doupdate();
					usleep(9000);

				}while (ch==ERR);
			}


			if (ch == 'c')
			{
				show_panel(my_panels[2]);
				do {
					ch=getch();
					sprintf(str, "Panel three %d\r", testn++);
					//edit_window(my_wins[2], str);
					update_panels();
					doupdate();
					usleep(9000);

				}while (ch==ERR);
			}


				if (  ch == 'q')
				exit = 0;

	}
	endwin();
	return 0;
}

/* Put all the windows */
void init_wins(WINDOW **wins, int n)
{	int x, y, i;
	char label[80];

	y = 2;
	x = 10;
	for(i = 0; i < n; ++i)
	{	wins[i] = newwin(NLINES, NCOLS, y, x);
		sprintf(label, "Window Number %d", i + 1);
		win_show(wins[i], label, i + 1);

	}
}

void edit_network_window(WINDOW *win, NetworkInfo *interface_device)
{
	print_in_network_box(win, 0, 0, 40, interface_device, 1);
}


/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void print_in_network_box(WINDOW *win, int starty, int startx, int width, NetworkInfo *interface_device, chtype color)
{
	int x, y;
	getyx(win, y, x);


	mvwprintw(win, 3,4,"Bytes Recieved: %ld\r", interface_device->bytes_recieved);
	mvwprintw(win,4,4,"Packets Recieved: %ld\r", interface_device->packets_recieved);
	mvwprintw(win,5,4,"Bytes Sent: %ld\r", interface_device->bytes_sent);
	mvwprintw(win,6,4,"Packets Sent: %ld\r", interface_device->packets_sent);
	refresh();
}
