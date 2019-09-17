#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <panel.h>
#include <string>
#include <vector>
#include <unistd.h>

#define BACKSPACE 127

using namespace std;

class Window {
private:
int h, w;
int cols = 4;//keeps track of the cursors current column
int index = 0;//keeps track of what row the user is on
char line;//initial blank var for welcome message
char* str;//Keep getting seg fault
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
	List test;
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
		//usleep(10);
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
	setBorder(index);
	mvgetch(index, cols); //places curser to the top left
	curs_set(TRUE);//displays the cursor
	while((nxt = getch()) != '\n') { //while not a new line
		switch(nxt) {
		case BACKSPACE: {
			mvdelch(index, cols - 1);
			cols--;
			break;
		}
		case KEY_UP: {
			mvgetch(index - 1, cols);
			index--;
			break;
		}
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
		default: {
			printw("%c", nxt);
			line.push_back(nxt);
			cols++;
			break;
		}
		}
	}
	index++; //update index for row
	cols = 4; //set column back to far left
	nxt = '\0'; //make new line break an empty char
	typing(nxt); //continue typing
}

};
struct Node {
	vector <char> data;
	Node* next;
	void print(){
		for(int i = 0; i < data.size(); i++) {
			cout << data[i];
		}
	}
};

class List {
private:
Node *head, *tail;
public:
List()
{
	head = NULL;
	tail = NULL;
}
void push(vector<char> value)
{
	Node *temp = new Node;
	temp->data = value;
	temp->next = NULL;
	if(head == NULL)
	{
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void display()
{
	Node *temp = new Node;
	temp = head;
	while(temp != NULL)
	{
		temp->print();
		cout << "\n";
		temp = temp->next;
	}
	//delete temp;
}
};
#endif
