#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <panel.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#define BACKSPACE 127

using namespace std;
ofstream input;
ifstream ouput;

class Window {
private:
int h, w;
vector<vector<char> > text;
int cols = 4;//keeps track of the cursors current column
int index = 0;//keeps track of what row the user is on
char line; //initial blank var for welcome message
char* str; //Keep getting seg fault
char* nums;
WINDOW* main_window = nullptr;
//Helpful function to convert strings into char* arrays
char* convert(string message, char* name){
	char* holder = new char[message.size() + 1];
	strcpy(holder, message.c_str());
	name = holder;
	holder = NULL;
	return name;
}

public:
Window(WINDOW* main, int height, int width){
	main_window = main;
	h = height;
	w = width;
}

void setBorder(int i){
	//adds line numbers
	while(i < h) {
		char num[3];
		int j = i + 1;
		string id = to_string(j);
		str = convert(id, str);
		mvaddstr(i, 0, str);
		i++;
	}
}

void openingMessage(){
	if(line == '\0') {
		helloThere();  //adds greeting to window
		mvgetch(0, 0);
		clrtobot();
	}
}

void helloThere(){
	string greet = "Welcome to Basix";
	int y = h / 2;  //Aligns the greeting to the center of the screen
	y -= 1;
	int x = w / 2;  //Aligns the greeting to the center of the screen
	x -= 10;
	str = convert(greet, str);
	mvaddstr(y, x, str);  //Adds greeting to the middle of the screen
}

void typing(int nxt){
	vector<char> line;
	setBorder(index);
	mvgetch(index, cols); //places curser to the top left
	curs_set(TRUE);//displays the cursor
	while((nxt = getch()) != '\n') { //while not a new line
		switch(nxt) {
		case BACKSPACE: {
			mvdelch(index, cols - 1);
			line.erase(line.end() - 1);
			cols--;
			break;
		}
		// case KEY_UP: {
		// 	mvgetch(index - 1, cols);
		// 	index--;
		// 	break;
		// }
		case KEY_DOWN: {
			mvgetch(index + 1, cols);
			index++;
			break;
		}
		case KEY_LEFT: {
			mvgetch(index, cols - 1);
			cols--;
			break;
		}
		case KEY_RIGHT: {
			mvgetch(index, cols + 1);
			cols++;
			break;
		}
		case KEY_UP: {
			text.push_back(line);
			endwin();
			string fileName;
			cout << "What do you wish to call the saved file?";
			getline(cin, fileName);
			fileName = "./" + fileName;
			input.open(fileName);
			for(int i = 0; i < text.size(); i++) {
				for(int j = 0; j < text[i].size(); j++) {
					text[i].size();
					input << text[i][j];
				}
				input << '\n';
			}
			break;
		}
		default: {
			printw("%c", nxt);
			line.push_back(nxt);
			cols++;
			break;
		}
		}
	}
	text.push_back(line);
	index++; //update index for row
	cols = 4; //set column back to far left
	nxt = '\0'; //make new line break an empty char
	typing(nxt); //continue typing
}

};

#endif
