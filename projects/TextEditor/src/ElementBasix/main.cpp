/*
   Created By: Sam Ramirez
   Created On: Fri, Aug 30, 2019 @ 10:52:35 AM
 */

#include <iostream>
#include <string>
#include <curses.h>
#include <panel.h>
#include <time.h>

using namespace std;

char* convert(string message, char* names){
	char name[message.size() + 1];
	strcpy(name, message.c_str());
	names = name;
	cout << names << endl;
	return names;
}

int main(){
	// string name = "Hello my name is Sam";
	// char* sam;
	// sam = convert(name, sam);
	// cout << sam << endl;

	//Grabs current time in string format
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	string curTime = asctime(timeinfo);

	//Sets up window in terminal
	WINDOW* main_window = nullptr;

	int width;
	int height;

	//Initializes Window
	main_window = initscr();

	//resize WINDOW
	getmaxyx(main_window, height, width);
	resize_term(height - 1, width - 1);

	//turn off keyboard echo
	noecho();
	//Turn on keyboard input
	keypad(main_window, TRUE);
	//Hide cursor
	curs_set(FALSE);
	cbreak();

	// Adds a border at the top of the screen;
	for(int i = 0; i < width; i++) {
		mvaddch(0, i, '#');
	}
	//adds line numbers
	for(int i = 0; i < height; i++) {
		char num[3];
		int index = i + 1;
		string sidebar = to_string(index);
		strcpy(num, sidebar.c_str());
		mvaddstr(i + 1, 0, num);
	}

	//Adds current time to bottom of window
	char currentTime[curTime.size() + 1];
	strcpy(currentTime, curTime.c_str());
	mvaddstr(height - 2, width - 30, currentTime);
	refresh();

	//Displays the initial message on the screen
	char line;
	while(line == '\0') {
		refresh();
		//grabs a character from the user
		line = getch();
		//Adds greeting to the middle of the screen
		string greeting = "Welcome to Basix";
		char greet[greeting.size() + 1];
		strcpy(greet, greeting.c_str());
		//Aligns the greeting to the center of the screen
		int y = height / 2;
		y -= 1;
		int x = width / 2;
		x -= 10;
		mvaddstr(y, x, greet);
		//Resets time after adding message
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		string curTime = asctime(timeinfo);
		char currentTime[curTime.size() + 1];
		strcpy(currentTime, curTime.c_str());
		mvaddstr(height - 2, width - 30, currentTime);
		refresh();
	}

	//Is suppose to display the character to the screen
	char typing;
	wmove(main_window, 1, 2);
	curs_set(TRUE);
	wrefresh(main_window);
	typing = getch();
	waddch(main_window, typing);
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	curTime = asctime(timeinfo);
	strcpy(currentTime, curTime.c_str());
	mvaddstr(height - 2, width - 30, currentTime);
	refresh();

	endwin();
	return 0;
}
