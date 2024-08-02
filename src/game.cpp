#include <bits/stdc++.h>
#include "CustomErrors.h"
using namespace std;
using ll = long long;
using vvi = vector<vector<int>>;

vvi clear_board(int rows, int columns) {
    return vvi(rows, vector<int>(columns, 0));
}

void change_turn(int& current) {
    if (current == 1) {
        current = 2;
        return;
    }
    current = 1;
}

char player_char(int player) {
    switch (player) {
        case 1:
            return 'X';
        case 2:
            return 'O';
        default:
            return '_';
    }
}

void printState(vvi& board) {
    int rows = board.size();
    int columns = board[0].size();
    cout << "  ";
    for (int i = 1; i <= columns; i++) {
        cout << i << " ";
    }
    cout << "\n";
    for (int i = 0; i < rows; i++) {
        cout << i+1 << " ";
        for (int j = 0; j < columns; j++) {
            cout << player_char(board[i][j]) << " ";
        }
        cout << "\n";
    }
}

void handle_input(string line, int & x, int & y) {
    string aux = "";
    int j = 0;
    try {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] != ' ') {
                aux += line[i];
                continue;
            }
            x = stoi(aux);
            j = i;
            break;
        }
        aux = "";
        for (int i = j; i < line.length(); i++) {
            aux += line[i];
        }
        y = stoi(aux);
    } catch (exception) {
        throw FaultyInput("Value is not an integer");
    }
}

/*
TODO TASKLIST:
    - change position in board
    - choose between 2 player and vs ai
    - explanation of the coordinates
    - simple random ai
*/

int main() {
    const int ROWS=4, COLUMNS=4, PLAYERS=2;
    int currentTurn=1;
    vvi board;

    board = clear_board(ROWS, COLUMNS);

    while (true) {
        int x, y;
        string inputLine;
        cout << "\n";
        cout << "It is the " << player_char(currentTurn) << " player's turn." << "\n";
        printState(board);
        cout << "What will be your move, " << player_char(currentTurn) << "?" << "\n";
        

        try {
            getline(cin, inputLine);

            handle_input(inputLine, x, y);

            if (x <= 0 or y <= 0 or x > COLUMNS or y > ROWS) {
                throw FaultyInput("Invalid coordinates.");
            }
        } catch (FaultyInput) {
            cout << "Please insert a valid coordinate." << "\n";
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }
        x--;
        y--;
        

    }



    return 0;
}