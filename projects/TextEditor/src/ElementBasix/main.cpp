/*
   Created By: Sam Ramirez
   Created On: Fri, Aug 30, 2019 @ 10:52:35 AM
 */
#include "window.h"
#include <vector>
#include <fstream>

using namespace std;

int main(/*int argc, char* argv[]*/){  //argc is the arguement count, argv is the arguement var
	char input;
	Window wd;//creates window
	// string hello = "How the fuck am I this behind";
	// vector<char> nums = {};
	// for(int i = 0; i < hello.length(); i++) {
	// 	nums[i] = hello[i];
	// }
	// for(int i = 0; i < nums.size();i++){
	//
	// }
	wd.typing(input);    //logic behind typing on screen
	wd.reDraw();
	return 0;
}
