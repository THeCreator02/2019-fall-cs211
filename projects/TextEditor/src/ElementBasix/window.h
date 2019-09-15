#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <panel.h>
#include <string>
#include <vector>

#define BACKSPACE char(127)
#define UP char(141)
#define DOWN char(145)
#define LEFT char(115)
#define RIGHT char(116)
using namespace std;

class Window {
private:
int h, w;
int cols = 4;//keeps track of the cursors current column
int index = 0;//keeps track of what row the user is on
char line;//initial blank var for welcome message
char* str;//Keep getting seg fault
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

void setBorder(int i = 0){
	//adds line numbers
	if(i >= h) {
		h++;
	}
	for(; i < h; i++) {
		char num[3];
		int j = i + 1;
		string id = to_string(j);
		str = convert(id, str);
		mvaddstr(i, 0, str);
	}
}

void openingMessage(){
	if(line == '\0') {
		helloThere();  //adds greeting to window
		mvgetch(0, 0);
		clrtobot();
		line = getch(); //once a char is detected
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


void typing(char nxt){
	mvgetch(index, cols); //places curser to the top left
	curs_set(TRUE);//displays the cursor
	while(nxt != '\n') { //while not a new line
		nxt = getch();
		cols++;
		if(nxt == BACKSPACE) { //case for handling backspace key
			mvdelch(index, cols - 2);
			cols -= 2;
		}
		else{
			addch(nxt); //display and slide over cursor
		}
	}
	index++; //update index for row
	setBorder(index);
	cols = 4; //set column back to far left
	//mvgetch(index, cols); //move cursor to new row
	nxt = '\0'; //make new line break an empty char
	typing(nxt); //continue typing
}

};
#endif
