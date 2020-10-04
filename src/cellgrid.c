#include <stdio.h>
#include <ncurses.h>

int main (int argc, char* argv[]) 
{
    // Start ncurses
    initscr();
    // Don't echo() while getch is called
    noecho();
    
    // Get terminal screen size
    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);

    printf("%d %d\n", ymax, xmax);

    // Create window
    int margin = 10; // margin to the left and right of the window inside the terminal
    WINDOW* win = newwin(6, xmax-margin*2, 2, margin);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    // getch so the program doesn't exit straight away
    getch();

    // End ncurses
    endwin();

    return 1;
}