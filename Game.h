#ifndef Game_h
#define Game_h

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

enum square {
    E = 0, X = 1, O = 2
};

struct Move {
    int index;
    int score;
};

class Game {
public:
    vector<square> board;
    bool xTurn;
    square human, bot;
    bool gameOver;
    string winner;

    Game();
    Game(square bot);
    Game(const Game &t);

    void humanMove(int pos);
    void botMove();
    bool isMovesLeft(vector<square> newBoard);
    bool checkWinner(vector<square> newBoard, square player);
    void printBoard();
    Move minimax(vector<square> newBoard, square player, int depth);
};

#endif

