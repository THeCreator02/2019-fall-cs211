/*
   Created By: Sam Ramirez
   Created On: Fri, Aug 30, 2019 @ 10:52:35 AM
 */

#include <iostream>
#include <string>
#include <curses.h>
#include <panel.h>

using namespace std;

int main(){
	WINDOW* main_window = nullptr;
	int num_cols = 177;
	int num_rows = 52;
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
		mvaddch(0, i, '#');
		mvaddch(num_rows - 1, i, '*');
	}

	for(int i = 0; i < num_rows; i++) {
		char num[3];
		int index = i + 1;
		string sidebar = to_string(index);
		strcpy(num, sidebar.c_str());
		mvaddstr(i + 1, 0, num);
	}

	//add initial greeting when opening application
	string greeting = "Welcome to Basix";
	char greet[greeting.length() + 1];
	strcpy(greet, greeting.c_str());
	mvaddstr(20, 73, greet);
	//refresh tells curses to draw everything
	refresh();

	//pause for user input;
	char input = getch();
	//Ends program when user inputs n
	endwin();
	return 0;
}
