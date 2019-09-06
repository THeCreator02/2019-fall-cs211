#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <panel.h>
#include <string>
#include <time.h>
using namespace std;

class Window {
private:
int w;//window width
int h;//window height
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
	cbreak();//still have no idea what cbreak does.
	setBorder();//adds indexs and top border to window
	setTime();//displays current time in right hand bottom corner
	update();//logic behind the disappearing welcome message
}

void setBorder(){
	// Adds a border at the top of the screen;
	for(int i = 0; i < w; i++) {
		mvaddch(0, i, '#');
	}
	//adds line numbers
	for(int i = 0; i < h; i++) {
		char num[3];
		int j = i + 1;
		string id = to_string(j);
		in = convert(id, in);
		mvaddstr(i + 1, 0, in);
	}
}

void helloThere(string greet = "Welcome to Basix"){
	int y = h / 2; //Aligns the greeting to the center of the screen
	y -= 1;
	int x = w / 2;  //Aligns the greeting to the center of the screen
	x -= 15;
	if(greet == "                ") {
		convert(greet, greeting);
		mvaddstr(y, x, greeting);//Deletes the greeting, still trying to get char off the screen
	}
	greeting = convert(greet, greeting);
	mvaddstr(y, x, greeting);  //Adds greeting to the middle of the screen
}

void update(){
	if(line == '\0') {
		helloThere();  //adds greeting to window
		line = getch(); //once a char is detected
		helloThere("                ");//the greeting is "deleted" simply overwritten
		mvgetch(index, 3);//places curser to the top left
	}
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

void typing(char nxt){
	curs_set(TRUE);//displays the cursor
	while(nxt != '\n') {//while not a new line
		if(nxt == '0') {//exit case for testing
			endwin();
			exit(1);
		}
		if(nxt == '\0') {//if the char is blank grab a new char from user
			nxt = getch();
			addch(nxt);//display and slider cursor over
		}
		else{
			nxt = '\0'; //if the char is not blank make it blank
			nxt = getch();//grab from user
			addch(nxt);//display and slide over cursor
		}
	}
	setTime();//update the time after every new line
	index++;//update index for row
	mvgetch(index, 3);//move cursor to new row
	nxt = '\0';//make new line break an empty char
	typing(nxt);//continue typing
}
};
#endif
