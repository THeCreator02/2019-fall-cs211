#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <panel.h>
#include <string>
#include <time.h>
#include <vector>
#define BACKSPACE char(127)
#define UP char(141)
#define DOWN char(145)
#define LEFT char(115)
#define RIGHT char(116)
using namespace std;

class Window {
private:
int w;//window width
int h;//window height
int cols = 3;//keeps track of the cursors current column
int index = 1;//keeps track of what row the user is on
char line;//initial blank var for welcome message
char* greeting;//Keep getting seg fault
char* in;//so pointers were made for each window

//Helpful function to convert strings into char* arrays
char* convert(string message, char* name){
	char* holder = new char[message.size() + 1];
	strcpy(holder, message.c_str());
	name = holder;
	holder = NULL;
	return name;
}

public:
WINDOW* main_window = nullptr;
Window(){
	main_window = initscr();//Initializes Window
	getmaxyx(main_window, h, w);//resize WINDOW
	resize_term(h - 1, w - 1);
	noecho();//turn off keyboard echo
	keypad(main_window, TRUE);//Turn on keyboard input
	curs_set(FALSE);//Hide cursor
	cbreak();//stops line buffering.
	scrollok(main_window, TRUE); //allows for scrolling after last line
	update();//logic behind the disappearing welcome message
	setBorder();//adds indexs and top border to window
	setTime();//displays current time in right hand bottom corner
}

void setBorder(int i = 0){
	//adds line numbers
	for(int i = 0; i < h; i++) {
		char num[3];
		int j = i + 1;
		string id = to_string(j);
		in = convert(id, in);
		mvaddstr(i + 1, 0, in);
	}
}
void update(){
	if(line == '\0') {
		helloThere();  //adds greeting to window
		mvgetch(0, 0);
		clrtobot();
		line = getch(); //once a char is detected
	}
}
void helloThere(string greet = "Welcome to Basix"){
	int y = h / 2; //Aligns the greeting to the center of the screen
	y -= 1;
	int x = w / 2;  //Aligns the greeting to the center of the screen
	x -= 10;
	greeting = convert(greet, greeting);
	mvaddstr(y, x, greeting);  //Adds greeting to the middle of the screen
}
void setTime(){
	time_t rawtime; //gives time in a struct form
	struct tm* timeinfo; //need a pointer for simlpy the time
	time(&rawtime); //converts global time to a time readable format
	timeinfo = localtime(&rawtime); //converts time depending on time zone
	string curTime = asctime(timeinfo);//takes current time and converts to a string
	char* tiempo; //Time in spanish
	tiempo = convert(curTime, tiempo);
	mvaddstr(h - 2, w - 30, tiempo);//adds time to bottom right corner
}

void reDraw(){
	clear();
	//main_window = initscr();//Initializes Window
	//resize_term(0, 0);
	getmaxyx(main_window, h, w);//resize WINDOW
	resize_term(h + 1, w + 1);
	scrollok(main_window, TRUE); //allows for scrolling after last line
	setBorder();//adds indexs and top border to window
}

void typing(char nxt){
	mvgetch(index, cols); //places curser to the top left
	curs_set(TRUE);//displays the cursor
	while(nxt != '\n') { //while not a new line
		nxt = getch();
		cols++;
		if(nxt == '0') { //exit case for testing
			endwin();
			exit(1);
		}
		if(nxt == BACKSPACE) { //case for handling backspace key
			mvdelch(index, cols - 2);
			cols -= 2;
		}
		else{
			addch(nxt); //display and slide over cursor
		}
	}

	reDraw();
	index++; //update index for row
	cols = 3; //set column back to far left
	mvgetch(index, cols); //move cursor to new row
	nxt = '\0'; //make new line break an empty char
	typing(nxt); //continue typing
}

};
#endif
