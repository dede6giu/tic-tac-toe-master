#include <bits/stdc++.h>
#include "CustomErrors.h"
using namespace std;
using ll = long long;
using vvi = vector<vector<int>>;

int rows=4, columns=4, players=2, sequence=3;

vvi clear_board(int rows, int columns) {
    return vvi(rows, vector<int>(columns, 0));
}

void change_turn(int& current, int playeramnt) {
    if (current == playeramnt) {
        current = 1;
        return;
    }
    current++;
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

void handle_board(vvi & board, int player, int x, int y) {
    if (board[x][y] == 0) {
        board[x][y] = player;
        return;
    }
    throw FaultyGameplay("Space already has an owner.");
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

bool check_horizontal(vvi board, int seq, int player) {
    // BUGGY!!!
    if (board[0].size() < seq) {
        return false;
    }
    bool found = false;
    int aux = 0;
    for (int i = 0; i < rows; i++) {
        int j = 0;
        while (j < columns - seq + 1) {
            if (board[i][j] == 0) {
                j++;
                continue;
            }
            if (found and board[i][j] == player) {
                aux++;
            } else if (board[i][j] == player) {
                aux = 1;
                found = true;
            } else {
                found = false;
            }
            j++;
            if (aux == seq) return true;
        }
    }
    return false;
}

bool check_victory(vvi board, int seq, int player) {
    if (check_horizontal(board, seq, player)) {
        return true;
    }
    return false;
}

/*
TODO TASKLIST:
    - choose between 2 player and vs ai
    - explanation of the coordinates
    - simple random ai
*/

int main() {
    int currentTurn=1;
    vvi board;

    board = clear_board(rows, columns);

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

            if (x <= 0 or y <= 0 or x > columns or y > rows) {
                throw FaultyInput("Invalid coordinates.");
            }
            x--;
            y--;
            
            handle_board(board, currentTurn, x, y);
        } catch (FaultyInput) {
            cout << "Please insert a valid input." << "\n";
            this_thread::sleep_for(chrono::milliseconds(700));
            continue;
        } catch (FaultyGameplay) {
            cout << "That space is already occupied!" << "\n";
            this_thread::sleep_for(chrono::milliseconds(700));
            continue;
        }

        if (check_victory(board, sequence, currentTurn)) {
            cout << player_char(currentTurn) << " won!" << "\n";
            break;
        }

        change_turn(currentTurn, players);
    }



    return 0;
}