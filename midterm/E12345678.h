// Random AI haha

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> Algorithm(vector < vector<int> >&, int, int, int);

int Helper1(int help) {
    return help;
}

bool Helper2() {
    return true;
}

vector<int> Algorithm(vector<vector<int>>& b, int my_color, int your_color, int phase) {
    srand(time(0));
    vector<int> action(8, 8);

    if (phase == 1) {
        int x, y;
        do {
            x = rand() % 7;
            y = rand() % 7;
        } while (b[x][y] != 0);

        action = { my_color, x, y, x, y, your_color, 8, 8 };
        b[x][y] = my_color;
    }
    else if (phase == 2) {
        vector<pair<int, int>> my_pieces;
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (b[i][j] == my_color) {
                    my_pieces.push_back({ i, j });
                }
            }
        }

        pair<int, int> piece_to_move = my_pieces[rand() % my_pieces.size()];
        int x, y;
        do {
            x = rand() % 7;
            y = rand() % 7;
        } while (b[x][y] != 0);

        action = { my_color, piece_to_move.first, piece_to_move.second, x, y, your_color, 8, 8 };
        b[piece_to_move.first][piece_to_move.second] = 0;
        b[x][y] = my_color;
    }

    return action;
}
