#include <iostream>
#include<vector>
using namespace std;

vector<int> poor(vector < vector<int> > &, int, int, int);

vector<int> poor(vector < vector<int> > &b, int my_color, int your_color, int phase) {
	int me = my_color; //Record the color main function assigns for this AI
	int opponent = your_color; //Record the color main function assigns for another AI
	vector<int> action;
	//Write a simple AI for testing









	
	//-1 means invalid place, 0 means valid place, 1 means there is white on it, 2 means there is black on it
	vector<vector<int>> new_board =
    {
	    { 0,-1,-1, 0,-1,-1, 0},
	    {-1, 0,-1, 0,-1, 0,-1},
	    {-1,-1, 0, 0, 0,-1,-1},
	    { 0, 0, 0,-1, 0, 0, 0},
	    {-1,-1, 0, 0, 0,-1,-1},
	    {-1, 0,-1, 0,-1, 0,-1},
	    { 0,-1,-1, 0,-1,-1, 0}
    };

    // you have to change the board into the board after your action.
    b = new_board;

    // action: [my_color, original_x, original_y, dest_x, dest_y, your_color, remove_x, remove_y]
    // placing_phase: dest == original
    // if no remove, remove_x = remove_y = 8
	return action;
}