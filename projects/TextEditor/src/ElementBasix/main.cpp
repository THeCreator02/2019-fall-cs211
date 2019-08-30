/*
   Created By: Sam Ramirez
   Created On: Fri, Aug 30, 2019 @ 10:52:35 AM
 */

#include <iostream>
#include <curses.h>
#include <panel.h>

using namespace std;

int main(){
	WINDOW* main_window = nullptr;
	int num_cols = 0;
	int num_rows = 0;
	//Initializes Window
	main_window = initscr();
	//resize WINDOW
	getmaxx(main_window);
	resize_term(num_rows - 1, num_cols - 1);
	//turn off keyboard echo
	noecho();
	//Turn on keyboard input
	keypad(main_window, TRUE);

	//Hide cursor
	curs_set(FALSE);
	// Main program logic
	for(int i = 0; i < num_cols; i++) {
		mvaddch(0, i, ACS_BLOCK);

		mvaddch(num_rows - 1, i, ACS_BLOCK);
	}
	for(int i = 0; i < num_rows; i++) {
		mvaddch(i, 0, ACS_BLOCK);

		mvaddch(i, num_cols - 1, ACS_BLOCK);
	}

	//refresh tells curses to draw everything
	refresh();
	mvaddch(10, 10, 'X');
	//pause for user input;
	char input = getch();

	//endwin();
	return 0;
}
