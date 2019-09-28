/*
   Created By: Sam Ramirez
   Created On: Fri, Aug 30, 2019 @ 10:52:35 AM
 */
#include "window.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){  //argc is the arguement count, argv is the arguement var
	if(argc == 2) {
		string line = argv[1];
		int n = line.find(".txt");
		ifstream file;
		//ofstream save;
		file.open(line);
		//save.open("/Users/TheCreation/Desktop/CS211/projects/TextEditor/src/ElementBasix/copy.cpp");
		if(file.good() && n > 0) {
			while (file.good()) {
				string nxt;
				getline(file, nxt);
				cout << nxt << endl;
				//save << nxt << endl;
			}
			//save.close();
		}
	}else{
		cout << "Making New File\n";
		int w;         //window width
		int h;    //window height
		int input;
		WINDOW* main_window;
		main_window = initscr();    //Initializes Window
		getmaxyx(main_window, h, w);    //resize WINDOW
		resize_term(h - 1, w - 1);

		Window wd(main_window, h, w);

		noecho();    //turn off keyboard echo
		keypad(main_window, TRUE);    //Turn on keyboard input
		curs_set(FALSE);    //Hide cursor
		cbreak();    //stops line buffering.
		scrollok(main_window, TRUE);     //allows for scrolling after last line
		wd.openingMessage();    //logic behind the disappearing welcome message
		wd.typing(input);      //logic behind typing on screen
	}
	return 0;
}
