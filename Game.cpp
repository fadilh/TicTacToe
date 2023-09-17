#include "Game.h"

using namespace std;

Game::Game()
{

    human = X;

    bot = O;

    winner = "T";

    xTurn = true;

    gameOver = false;

    board.assign(9, E);
}

Game::Game(square bot)
{

    this->bot = bot;

    human = (bot == X ? O : X);

    winner = "T";

    xTurn = true;

    gameOver = false;

    board.assign(9, E);
}

Game::Game(const Game &t)
{

    human = t.human;

    bot = t.bot;

    gameOver = t.gameOver;

    xTurn = t.xTurn;

    board = t.board;
}

bool Game::isMovesLeft(vector<square> newBoard)
{

    for (int i = 0; i < 9; i++)

        if (newBoard[i] == E)

            return true;

    return false;
}

void Game::humanMove(int pos)
{

    if (!isMovesLeft(board))
    {

        gameOver = true;
    }
    else
    {

        board.at(pos) = human;

        gameOver = checkWinner(board, human);

        xTurn = !xTurn;
    }
}

void Game::botMove()
{

    if (!isMovesLeft(board))
    {

        gameOver = true;

        return;
    }

    Move bestMove = minimax(board, bot, 0);

    board.at(bestMove.index) = bot;

    gameOver = checkWinner(board, bot);

    xTurn = !xTurn;

    cout << (bot == X ? "X " : "O ") << "chose position " << bestMove.index << endl;

    if (gameOver)
    {

        return;
    }
}

bool Game::checkWinner(vector<square> newBoard, square player)
{

    if ((newBoard.at(0) == player && newBoard.at(1) == player && newBoard.at(2) == player) ||

        (newBoard.at(3) == player && newBoard.at(4) == player && newBoard.at(5) == player) ||

        (newBoard.at(6) == player && newBoard.at(7) == player && newBoard.at(8) == player) ||

        (newBoard.at(0) == player && newBoard.at(3) == player && newBoard.at(6) == player) ||

        (newBoard.at(1) == player && newBoard.at(4) == player && newBoard.at(7) == player) ||

        (newBoard.at(2) == player && newBoard.at(5) == player && newBoard.at(8) == player) ||

        (newBoard.at(0) == player && newBoard.at(4) == player && newBoard.at(8) == player) ||

        (newBoard.at(2) == player && newBoard.at(4) == player && newBoard.at(6) == player))
    {

        winner = (player == X ? "X" : "O");

        return true;
    }

    if (!isMovesLeft(newBoard))
    {

        winner = "T";

        return true;
    }

    return false;
}

Move Game::minimax(vector<square> newBoard, square player, int depth)
{

    if (checkWinner(newBoard, human))
    {

        Move move;

        move.score = -10 + depth;

        return move;
    }

    if (checkWinner(newBoard, bot))
    {

        Move move;

        move.score = 10 - depth;

        return move;
    }

    if (!isMovesLeft(newBoard))
    {

        Move move;

        move.score = 0;

        return move;
    }

    vector<Move> moves;

    for (int i = 0; i < 9; i++)
    {

        if (newBoard[i] == E)
        {

            Move move;

            move.index = i;

            newBoard[i] = player;

            if (player == bot)
            {

                Move m = minimax(newBoard, human, depth + 1);

                move.score = m.score;
            }
            else
            {

                Move m = minimax(newBoard, bot, depth + 1);

                move.score = m.score;
            }

            newBoard[i] = E;

            moves.push_back(move);
        }
    }

    int bestMove;

    if (player == bot)
    {

        int bestScore = -1000;

        for (int i = 0; i < moves.size(); i++)
        {

            if (moves[i].score > bestScore)
            {

                bestScore = moves[i].score;

                bestMove = i;
            }
        }
    }
    else
    {

        int bestScore = 1000;

        for (int i = 0; i < moves.size(); i++)
        {

            if (moves[i].score < bestScore)
            {

                bestScore = moves[i].score;

                bestMove = i;
            }
        }
    }

    return moves[bestMove];
}

void Game::printBoard()
{

    cout << endl;

    int currPos = 0;

    for (int i = 0; i < 3; i++)

    {

        string line = "";

        for (int j = 0; j < 3; j++)

        {

            line += (j == 2 ? (board.at(currPos) == X ? "  X  " : board.at(currPos) == O ? "  O  "
                                                                                         : "  " + to_string(currPos) + "  ")

                            : (board.at(currPos) == X ? "  X  |" : board.at(currPos) == O ? "  O  |"
                                                                                          : "  " + to_string(currPos) + "  |"));

            currPos++;
        }

        cout << "     |     |     " << endl;

        cout << line << endl;

        cout << (i != 2 ? "_____|_____|_____" : "     |     |     ") << endl;
    }

    cout << endl;
}

int main()
{

    int choice;

    square human, bot;

    cout << "Choose player, type 1 for X or 2 for O: " << endl;

    cin >> choice;

    while (choice != 1 && choice != 2)
    {

        cout << "Please type 1 or 2" << endl;

        cout << "Choose player, type 1 for X or 2 for O: " << endl;

        cin >> choice;
    }

    human = (choice == 1 ? X : O);

    bot = (choice == 1 ? O : X);

    Game game = Game(bot);

    game.printBoard();

    do

    {

        if (game.xTurn == (game.bot == X ? true : false))
        {

            game.botMove();
        }
        else
        {

            int chosenPos;

            cout << "choose a position: " << endl;

            cin >> chosenPos;

            while (chosenPos < 0 || chosenPos >= 9 || game.board.at(chosenPos) != E)

            {

                cout << "give a number between 0 - 9 and choose an empty position" << endl;

                cout << "choose a position: " << endl;

                cin >> chosenPos;
            }

            game.humanMove(chosenPos);
        }

        game.printBoard();

    } while (!game.gameOver);

    cout << (game.winner == "T" ? "It is a tie" : game.winner + " wins.") << endl;

    return 0;
}