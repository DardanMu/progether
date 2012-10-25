#include <panel.h>
#include <libcurses_functions.h>


int main(){
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

    while(exit){
        show_panel(my_panels[window]);
        do {
            /* Clear values in struct just in case */
            init_networking_struct(interface_device);
    
            draw_box_with_label(my_wins[window], "Interface:", 1, 0, 0);
            get_network_info(interface_device, device_names[window]);
            print_in_network_box(my_wins[window], interface_device);
    
            update_panels();
            doupdate();
            usleep(500000);
    
        }while ((ch=getch()) == ERR);
        /* ERR is the value returned by getch() when nodelay() is set and there     */
        /* are there are no characters waiting in the buffer.                       */
        /* We can loop on ERR and it will break whenever the user inputs something  */

        if (  ch == (int)'q')
            exit = 0;

        /* If the char is tab (9) increment window to scroll through devices */
        if (ch == 9){
            window++;
            if (window == interface_num)
                window = 0;
        }

    }
    free(interface_device);
    endwin();

    return 0;
}

