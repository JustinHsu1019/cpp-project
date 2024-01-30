#include<iostream>
#include<vector>
#define STUDENT 2
#include"Poor_AI.h"
#include"E12345678.h"
using namespace std;

//-1 means invalid place, 0 means valid place, 1 means there is white on it, 2 means there is black on it
vector<vector<int>> initial_board =
{
	{ 0,-1,-1, 0,-1,-1, 0},
	{-1, 0,-1, 0,-1, 0,-1},
	{-1,-1, 0, 0, 0,-1,-1},
	{ 0, 0, 0,-1, 0, 0, 0},
	{-1,-1, 0, 0, 0,-1,-1},
	{-1, 0,-1, 0,-1, 0,-1},
	{ 0,-1,-1, 0,-1,-1, 0}
};

vector<vector<int>> prev_board =
{
	{ 0,-1,-1, 0,-1,-1, 0},
	{-1, 0,-1, 0,-1, 0,-1},
	{-1,-1, 0, 0, 0,-1,-1},
	{ 0, 0, 0,-1, 0, 0, 0},
	{-1,-1, 0, 0, 0,-1,-1},
	{-1, 0,-1, 0,-1, 0,-1},
	{ 0,-1,-1, 0,-1,-1, 0}
};

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


vector<int> remain_count = {0, 9, 9};	//remain piece count
int Game_Phase = 0;		//1 means placing phase, 2 means moving phase
bool IS_NOT_GAME_OVER = 1;
bool Compare_board(vector<int> action, vector<vector<int>>prev_board, vector<vector<int>>new_board, int phase);
bool Legal_Move(vector<int> action);
bool Is_Milled(vector<int> action, vector<vector<int>>new_board);
bool Legal_take(vector<int> action, bool new_milled, vector<vector<int>>new_board, vector<vector<int>>prev_board);


int main() {
	int P1_WIN_COUNTER = 0;
	int P2_WIN_COUNTER = 0;
	int Draw_Counter = 0;
	int step_counter = 0;



	vector<int>(*agents[STUDENT])(vector < vector<int> > &b, int my_color, int your_color, int phase);

	int game_amount_counter = 0;
	while(game_amount_counter < 30){
		prev_board.assign(initial_board.begin(), initial_board.end());
		new_board.assign(initial_board.begin(), initial_board.end());
		int my_color = 1;
		int your_color = 2;
		bool WHITE_WIN = 0;
		bool BLACK_WIN = 0;
		bool DRAW_GAME = 0;
	
		if (game_amount_counter % 2 == 0) {
			agents[0] = poor;
			agents[1] = Algorithm; 	//your AI
		}
		else if (game_amount_counter % 2 == 1) {
			agents[0] = Algorithm;	//your AI
			agents[1] = poor;
		}

		Game_Phase = 1;
		IS_NOT_GAME_OVER = 1;
		remain_count = {0, 9, 9};
		bool compare_board_flag = 0;
		bool legal_move_flag = 0;
		bool new_milled = 0;
		bool legal_take_flag = 0;
		int step = 0;

	
		while (IS_NOT_GAME_OVER) {
			//white move first
			if (step % 2 == 0) {
				my_color = 1;	//white
				your_color = 2;	//black
			}
			else {
				my_color = 2;
				your_color = 1;
			}
			// action: [my_color, original_x, original_y, dest_x, dest_y, your_color, remove_x, remove_y]
			// placing_phase: dest == original
			// if no remove, remove_x = remove_y = 8
			vector<int> action_done = agents[step % 2](new_board, my_color, your_color, Game_Phase);
			if (Game_Phase == 1 && step < 18) {
				compare_board_flag = Compare_board(action_done, prev_board, new_board, 1);
				if (compare_board_flag) {
					if (my_color == 1)
						BLACK_WIN = 1;
					else
						WHITE_WIN = 1;
					break;
				}
				new_milled = Is_Milled(action_done, new_board);
				legal_take_flag = Legal_take(action_done, new_milled, new_board, prev_board);
			}

			else if (Game_Phase == 2 && remain_count[my_color] == 3) { 		// GamePhase = flying phase
				compare_board_flag = Compare_board(action_done, prev_board, new_board, 2);
				if (compare_board_flag) {
					if (my_color == 1)
						BLACK_WIN = 1;
					else
						WHITE_WIN = 1;
					break;
				}
				new_milled = Is_Milled(action_done, new_board);
				legal_take_flag = Legal_take(action_done, new_milled, new_board, prev_board);
			}
			else if (Game_Phase == 2) {
				compare_board_flag = Compare_board(action_done, prev_board, new_board, 2);
				if (compare_board_flag) {
					if (my_color == 1)
						BLACK_WIN = 1;
					else
						WHITE_WIN = 1;
					break;
				}
				legal_move_flag = Legal_Move(action_done);
				new_milled = Is_Milled(action_done, new_board);
				legal_take_flag = Legal_take(action_done, new_milled, new_board, prev_board);
			}

			if (compare_board_flag || legal_move_flag || legal_take_flag) {
				if (my_color == 1)
					BLACK_WIN = 1;
				else
					WHITE_WIN = 1;
				IS_NOT_GAME_OVER = 0;
			}
			if (remain_count[1] == 2) {
				BLACK_WIN = 1;
				IS_NOT_GAME_OVER = 0;
			}
			if (remain_count[2] == 2) {
				WHITE_WIN = 1;
				IS_NOT_GAME_OVER = 0;
			}
			step++;
			if (step == 18)
				Game_Phase = 2;

			if (step == 400) {	//If steps = 400, game ends
				if (remain_count[1] > remain_count[2])
					WHITE_WIN = 1;
				else if (remain_count[2] > remain_count[1])
					BLACK_WIN = 1;
				else if (remain_count[1] == remain_count[2])
					DRAW_GAME = 1;
				break;
			}
			prev_board.assign(new_board.begin(), new_board.end());
		//cout the board
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
						if (prev_board[i][j] != -1)
							cout << " ";
						cout << prev_board[i][j] << " ";			
				}
				cout << endl;
			}
		}

		
		cout<<"Result of Gmae No. "<<(game_amount_counter+1)<<" is ~~~";
		if (WHITE_WIN) {
			cout << "WHITE WIN!!!" << endl;
			if (game_amount_counter % 2 == 0)
				P1_WIN_COUNTER++;
			else if (game_amount_counter % 2 == 1)
				P2_WIN_COUNTER++;
		}
		else if (BLACK_WIN) {
			cout << "BLACK WIN!!!" << endl;
			if (game_amount_counter % 2 == 0)
				P2_WIN_COUNTER++;
			else if (game_amount_counter % 2 == 1)
				P1_WIN_COUNTER++;
		}
		else if (DRAW_GAME) {
			Draw_Counter ++;
			cout << "DRAW GAME!!!" << endl;
		}
		game_amount_counter ++;
		cout << "Remained white piece = " << remain_count[1] << endl;
		cout << "Remained black piece = " << remain_count[2] << endl;
		cout<<"Step = "<<step<<endl<<endl;
		step_counter  = step_counter + step;

	}

	cout << "GAMES P1 Won: "<< P1_WIN_COUNTER << endl;
	cout << "GAMES P2 Won: "<< P2_WIN_COUNTER << endl;
	cout<<"DRAW GAMES: "<<Draw_Counter<<endl;
	cout << "Total step = " << step_counter <<endl;

}

bool Compare_board(vector<int> action, vector<vector<int>>prev_board, vector<vector<int>>new_board, int Game_Phase) {
	bool flag = 0;
		
	//Action size must be 8
	if (action.size() != 8) {
		flag = 1;
		cout << "Invalid Action Size" << endl;
		return flag;
	}

	//Check invalid board access
	for(int i = 0; i < action.size(); i++){
		if(action[i] < 0)
			flag = 1;
		else if (action[i] > 6){
			if(i < 6)
				flag = 1;
			else if (action[i] == 7 || action[i] > 8)
				flag = 1;
		}
	}
	
	if(action[6] == 8){
		if(action[7] != 8)
			flag = 1;
	}

	if(action[7] == 8){
		if(action[6] != 8)
			flag = 1;
	}
	if(flag == 1){
		cout<<"ACTION ERROR"<<endl;
		return flag;
	}

	//Don't change the board
	if (prev_board.size() != new_board.size()) {
		flag = 1;
		cout << "Don't change the board" << endl;
		return flag;
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (prev_board[i][j] == -1 && new_board[i][j] != -1) {
				flag = 1;
				cout << "Don't try to change invalid places" << endl;
				return flag;
			}
		}
	}

	
	//dest_pos check
	if (Game_Phase == 1) {
		if (prev_board[action[1]][action[2]] != 0 || new_board[action[1]][action[2]] != action[0]) {
			flag = 1;
		}
		if (action[1] != action[3] || action[2] != action[4]) {
			flag = 1;
		}
	}
	else {
		if (prev_board[action[1]][action[2]] != action[0] || new_board[action[1]][action[2]] != 0) {
			flag = 1;
		}
		if (prev_board[action[3]][action[4]] != 0 || new_board[action[3]][action[4]] != action[0]) {
			flag = 1;
		}
	}

	//remove_pos check
	if (action[6] != 8 || action[7] != 8) { 
		if (prev_board[action[6]][action[7]] != action[5] || new_board[action[6]][action[7]] != 0) {
			flag = 1;
		}
	}

	if (flag == 1) {
		cout << "Unreal Movement" << endl;
	}
	return flag;

}

bool Legal_Move(vector<int> action) {
	bool flag = 0;
	//Left>>Up>>Right>>Down
//row 0
	if (action[1] == 0 && action[2] == 0) {
		if (!((action[3] == 0 && action[4] == 3) || (action[3] == 3 && action[4] == 0)))
			flag = 1;
	}
	else if (action[1] == 0 && action[2] == 3) {
		if (!((action[3] == 0 && action[4] == 0) || (action[3] == 1 && action[4] == 3) || (action[3] == 0 && action[4] == 6)))
			flag = 1;
	}
	else if (action[1] == 0 && action[2] == 6) {
		if (!((action[3] == 0 && action[4] == 3) || (action[3] == 3 && action[4] == 6)))
			flag = 1;
	}

//row 1
	else if (action[1] == 1 && action[2] == 1) {
		if (!((action[3] == 1 && action[4] == 3) || (action[3] == 3 && action[4] == 1)))
			flag = 1;
	}
	else if (action[1] == 1 && action[2] == 3) {
		if (!((action[3] == 1 && action[4] == 1) || (action[3] == 0 && action[4] == 3) || (action[3] == 1 && action[4] == 5) || (action[3] == 2 && action[4] == 3)))
			flag = 1;
	}
	else if (action[1] == 1 && action[2] == 5) {
		if (!((action[3] == 1 && action[4] == 3) || (action[3] == 3 && action[4] == 5)))
			flag = 1;
	}

//row 2
	else if (action[1] == 2 && action[2] == 2) {
		if (!((action[3] == 2 && action[4] == 3) || (action[3] == 3 && action[4] == 2)))
			flag = 1;
	}
	else if (action[1] == 2 && action[2] == 3) {
		if (!((action[3] == 2 && action[4] == 2) || (action[3] == 1 && action[4] == 3) || (action[3] == 2 && action[4] == 4)))
			flag = 1;
	}
	else if (action[1] == 2 && action[2] == 4) {
		if (!((action[3] == 2 && action[4] == 3) || (action[3] == 3 && action[4] == 4)))
			flag = 1;
	}

//row 3
	else if (action[1] == 3 && action[2] == 0) {
		if (!((action[3] == 0 && action[4] == 0) || (action[3] == 3 && action[4] == 1) || (action[3] == 6 && action[4] == 0)))
			flag = 1;
	}
	else if (action[1] == 3 && action[2] == 1) {
		if (!((action[3] == 3 && action[4] == 0) || (action[3] == 1 && action[4] == 1) || (action[3] == 3 && action[4] == 2) || (action[3] == 5 && action[4] == 1)))
			flag = 1;
	}
	else if (action[1] == 3 && action[2] == 2) {
		if (!((action[3] == 3 && action[4] == 1) || (action[3] == 2 && action[4] == 2) || (action[3] == 4 && action[4] == 2)))
			flag = 1;
	}
	else if (action[1] == 3 && action[2] == 4) {
		if (!((action[3] == 2 && action[4] == 4) || (action[3] == 3 && action[4] == 5) || (action[3] == 4 && action[4] == 4)))
			flag = 1;
	}
	else if (action[1] == 3 && action[2] == 5) {
		if (!((action[3] == 3 && action[4] == 4) || (action[3] == 1 && action[4] == 5) || (action[3] == 3 && action[4] == 6) || (action[3] == 5 && action[4] == 5)))
			flag = 1;
	}
	else if (action[1] == 3 && action[2] == 6) {
		if (!((action[3] == 3 && action[4] == 5) || (action[3] == 0 && action[4] == 6) || (action[3] == 6 && action[4] == 6)))
			flag = 1;
	}

//row 4
	else if (action[1] == 4 && action[2] == 2) {
		if (!((action[3] == 3 && action[4] == 2) || (action[3] == 4 && action[4] == 3)))
			flag = 1;
	}
	else if (action[1] == 4 && action[2] == 3) {
		if (!((action[3] == 4 && action[4] == 2) || (action[3] == 4 && action[4] == 4) || (action[3] == 5 && action[4] == 3)))
			flag = 1;
	}
	else if (action[1] == 4 && action[2] == 4) {
		if (!((action[3] == 4 && action[4] == 3) || (action[3] == 3 && action[4] == 4)))
			flag = 1;
	}

//row 5
	else if (action[1] == 5 && action[2] == 1) {
		if (!((action[3] == 3 && action[4] == 1) || (action[3] == 5 && action[4] == 3)))
			flag = 1;
	}
	else if (action[1] == 5 && action[2] == 3) {
		if (!((action[3] == 5 && action[4] == 1) || (action[3] == 4 && action[4] == 3) || (action[3] == 5 && action[4] == 5) || (action[3] == 6 && action[4] == 3)))
			flag = 1;
	}
	else if (action[1] == 5 && action[2] == 5) {
		if (!((action[3] == 5 && action[4] == 3) || (action[3] == 3 && action[4] == 5)))
			flag = 1;
	}

//row 6
	else if (action[1] == 6 && action[2] == 0) {
		if (!((action[3] == 3 && action[4] == 0) || (action[3] == 6 && action[4] == 3)))
			flag = 1;
	}
	else if (action[1] == 6 && action[2] == 3) {
		if (!((action[3] == 6 && action[4] == 0) || (action[3] == 5 && action[4] == 3) || (action[3] == 6 && action[4] == 6)))
			flag = 1;
	}
	else if (action[1] == 6 && action[2] == 6) {
		if (!((action[3] == 6 && action[4] == 3) || (action[3] == 3 && action[4] == 6)))
			flag = 1;
	}


	if (flag == 1)
		cout << "Invalid Movement" << endl;

	return flag;
}

bool Is_Milled(vector<int> action, vector<vector<int>>new_board) {
	int milled_count_1 = 0; // chesses that are same color in row 
	int milled_count_2 = 0; // chesses that are same color in column
	bool flag = 0;

	//check row or column is milled or not
	if (action[3] != 3 && action[4] != 3) {
		for (int i = 0; i <= 6; i++) {
			if (new_board[action[3]][i] == action[0]) {
				milled_count_1++;//row is milled
			}
			if (new_board[i][action[4]] == action[0]) {
				milled_count_2++;//column is milled
			}
		}
	}
	//when the new chess is on the upper half of the column
	else if (action[3] <= 2 && action[4] == 3) {
		for (int i = 0; i <= 6; i++) {
			if (new_board[action[3]][i] == action[0]) {
				milled_count_1++;
			}
		}
		for (int j = 0; j <= 2; j++) {
			if (new_board[j][action[4]] == action[0]) {
				milled_count_2++;
			}
		}
	}
	//when the new chess is on the lower half of the column
	else if (action[3] >= 4 && action[4] == 3) {
		for (int i = 0; i <= 6; i++) {
			if (new_board[action[3]][i] == action[0]) {
				milled_count_1++;
			}
		}
		for (int j = 4; j <= 6; j++) {
			if (new_board[j][action[4]] == action[0]) {
				milled_count_2++;
			}
		}
	}
	//when the new chess is on the left half of the row
	else if (action[3] == 3 && action[4] <= 2) {
		for (int i = 0; i <= 2; i++) {
			if (new_board[action[3]][i] == action[0]) {
				milled_count_1++;
			}
		}
		for (int j = 0; j <= 6; j++) {
			if (new_board[j][action[4]] == action[0]) {
				milled_count_2++;
			}
		}
	}
	//when the new chess is on the right half of the row
	else if (action[3] == 3 && action[4] >= 4) {
		for (int i = 4; i <= 6; i++) {
			if (new_board[action[3]][i] == action[0]) {
				milled_count_1++;
			}
		}
		for (int j = 0; j <= 6; j++) {
			if (new_board[j][action[4]] == action[0]) {
				milled_count_2++;
			}
		}
	}

	if (milled_count_1 == 3 || milled_count_2 == 3) {
		flag = 1;
	}

	return flag;
}

bool Legal_take(vector<int> action, bool new_milled, vector<vector<int>>new_board, vector<vector<int>>prev_board) {

	bool flag = 0;
	bool milled_flag = 1;
	vector<vector<int>> milled_board = {
	{ 0,-1,-1, 0,-1,-1, 0},
	{-1, 0,-1, 0,-1, 0,-1},
	{-1,-1, 0, 0, 0,-1,-1},
	{ 0, 0, 0,-1, 0, 0, 0},
	{-1,-1, 0, 0, 0,-1,-1},
	{-1, 0,-1, 0,-1, 0,-1},
	{ 0,-1,-1, 0,-1,-1, 0}
	};

	milled_board.assign(prev_board.begin(), prev_board.end());

	//does not milled and remove cordination is not 8,8
	if (new_milled == 0 && (action[6] != 8 || action[7] != 8)) {
		flag = 1;
		cout << "Invalid Take1" << endl;
		return flag;
	}
	//should remove chess but did not remove opponent's chess
	if(new_milled == 1 && action[6] < 7 && action[7] < 7){
		if (milled_board[action[6]][action[7]] != action[5]) {
			flag = 1;
			cout << "Invalid Take2" << endl;
			return flag;
		}
	}
	//should remove chess but did not remove
	else if(new_milled == 1 && (action[6] > 6 || action[7] > 6)){
		flag = 1;
		cout << "Invalid Take3" << endl;
		return flag;
	}

	//transfer the code of opponent's chess that is milled(1->3, 2->4)
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			if (milled_board[i][j] == action[5]) {
				int count_1 = 0;//how many opponent's chess in same row
				int count_2 = 0;//how many opponent's chess in same column

				//not in the middle row and middle column
				if (i != 3 && j != 3) {
					for (int k = 0; k <= 6; k++) {
						if (milled_board[i][k] == action[5] || milled_board[i][k] == (action[5] + 2)) {
							count_1++;
						}
						if (milled_board[k][j] == action[5] || milled_board[k][j] == (action[5] + 2)) {
							count_2++;
						}
					}
					// row is milled
					if (count_1 == 3) {
						for (int r = 0; r <= 6; r++) {
							if (milled_board[i][r] == action[5]) {
								milled_board[i][r] += 2;
							}
						}
					}
					// column is milled
					if (count_2 == 3) {
						for (int s = 0; s <= 6; s++) {
							if (milled_board[s][j] == action[5]) {
								milled_board[s][j] += 2;
							}
						}
					}
				}
				//when the chess is on the upper half of the column
				else if (i <= 2 && j == 3) {
					for (int k = 0; k <= 6; k++) {
						if (milled_board[i][k] == action[5] || milled_board[i][k] == (action[5] + 2)) {
							count_1++;
						}
					}
					for (int p = 0; p <= 2; p++) {
						if (milled_board[p][j] == action[5] || milled_board[p][j] == (action[5] + 2)) {
							count_2++;
						}
					}

					if (count_1 == 3) {
						for (int q = 0; q <= 6; q++) {
							if (milled_board[i][q] == action[5]) {
								milled_board[i][q] += 2;
							}
						}
					}
					if (count_2 == 3) {
						for (int r = 0; r <= 2; r++) {
							if (milled_board[r][j] == action[5]) {
								milled_board[r][j] += 2;
							}
						}
					}
				}
				//when the chess is on the lower half of the column
				else if (i >= 4 && j == 3) {
					for (int k = 0; k <= 6; k++) {
						if (milled_board[i][k] == action[5] || milled_board[i][k] == (action[5] + 2)) {
							count_1++;
						}
					}
					for (int p = 4; p <= 6; p++) {
						if (milled_board[p][j] == action[5] || milled_board[p][j] == (action[5] + 2)) {
							count_2++;
						}
					}

					if (count_1 == 3) {
						for (int q = 0; q <= 6; q++) {
							if (milled_board[i][q] == action[5]) {
								milled_board[i][q] += 2;
							}
						}
					}
					if (count_2 == 3) {
						for (int r = 4; r <= 6; r++) {
							if (milled_board[r][j] == action[5]) {
								milled_board[r][j] += 2;
							}
						}
					}
				}
				//when the chess is on the left half of the row
				else if (i == 3 && j <= 2) {
					for (int k = 0; k <= 2; k++) {
						if (milled_board[i][k] == action[5] || milled_board[i][k] == (action[5] + 2)) {
							count_1++;
						}
					}
					for (int p = 0; p <= 6; p++) {
						if (milled_board[p][j] == action[5] || milled_board[p][j] == (action[5] + 2)) {
							count_2++;
						}
					}

					if (count_1 == 3) {
						for (int q = 0; q <= 2; q++) {
							if (milled_board[i][q] == action[5]) {
								milled_board[i][q] += 2;
							}
						}
					}
					if (count_2 == 3) {
						for (int r = 0; r <= 6; r++) {
							if (milled_board[r][j] == action[5]) {
								milled_board[r][j] += 2;
							}
						}
					}
				}
				//when the chess is on the right half of the row
				else if (i == 3 && j >= 4) {
					for (int k = 4; k <= 6; k++) {
						if (milled_board[i][k] == action[5] || milled_board[i][k] == (action[5] + 2)) {
							count_1++;// row 連線
						}
					}
					for (int p = 0; p <= 6; p++) {
						if (milled_board[p][j] == action[5] || milled_board[p][j] == (action[5] + 2)) {
							count_2++;
						}
					}

					if (count_1 == 3) {
						for (int q = 4; q <= 6; q++) {
							if (milled_board[i][q] == action[5]) {
								milled_board[i][q] += 2;
							}
						}
					}
					if (count_2 == 3) {
						for (int r = 0; r <= 6; r++) {
							if (milled_board[r][j] == action[5]) {
								milled_board[r][j] += 2;
							}
						}
					}
				}
			}
		}
	}

	//check if there is any non-milled chess of opponent
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			//there is non-milled chess on the board
			if (milled_board[i][j] == action[5]) {
				milled_flag = 0;
				break;
			}
		}
	}

	//there are non-milled chesses on the board but player take the milled chess 
	if (new_milled == 1) {
		//remove chess
		remain_count[action[5]] --;

		if (milled_board[action[6]][action[7]] == (action[5] + 2) && milled_flag == 0) {
			flag = 1;
			cout << "Invalid Take" << endl;
		}
	}

	return flag;
}