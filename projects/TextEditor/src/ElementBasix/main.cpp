/*
   Created By: Sam Ramirez
   Created On: Fri, Aug 30, 2019 @ 10:52:35 AM
 */
//#include "window.h"
#include <vector>
#include <string>
#include <iostream>
//#include <fstream>
using namespace std;


int main(/*int argc, char* argv[]*/){  //argc is the arguement count, argv is the arguement var
	// int w;//window width
	// int h;//window height
	// int input;
	List test;
	vector<char> str;
	vector <char> str2;
	for(int i = 0; i < 10; i++) {
		str.push_back('B');
	}
	test.push(str);

	for(int i = 0; i < 10; i++) {
		str2.push_back('A');
	}
	test.push(str2);
	test.display();
	// WINDOW* main_window;
	// main_window = initscr();//Initializes Window
	// getmaxyx(main_window, h, w);//resize WINDOW
	// resize_term(h - 1, w - 1);
	//
	// Window wd(main_window, h, w);
	//
	// noecho();//turn off keyboard echo
	// keypad(main_window, TRUE);//Turn on keyboard input
	// curs_set(FALSE);//Hide cursor
	// cbreak();//stops line buffering.
	// scrollok(main_window, TRUE); //allows for scrolling after last line
	// wd.openingMessage();//logic behind the disappearing welcome message
	// wd.typing(input);  //logic behind typing on screen
	// endwin();
	return 0;
}
