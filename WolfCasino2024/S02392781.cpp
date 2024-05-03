#include <iostream> // cin & cout
#include "S02392781.h"
#include <algorithm>

//defined namespace for project
namespace S02392781
{

//Constructor
Twenty48::Twenty48() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            board[i][j] = 0;
        }
    }
}

Twenty48::~Twenty48(){}

Twenty48* Twenty48::makeGame() {
    return new Twenty48;
}

void Twenty48::print(){
    // Display the board
    cout << "---------------------" << std::endl;
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                cout << "|    ";
            } else {
                cout << "|" << board[i][j];
                size_t numSpaces = 4 - to_string(board[i][j]).length();
                for (int k = 0; k < numSpaces; ++k) {
                    cout << " ";
                }
            }
        }
        cout << "|" << std::endl;
        cout << "---------------------" << std::endl;
    }
}

void Twenty48::addPiece(){
    // use random number generator to pick a row & column where to add piece,
    // check if it is open, if open add and if not, reroll indeces
    
    // Seed the random number generator with current time
    srand((double)time(nullptr));
    
    int row = rand() % 4;
    int col = rand() % 4;
    int newNum = (rand() % 2) + 1;
    
    while (board[row][col] > 0) {
        row = rand() % 4;
        col = rand() % 4;
    }
    board[row][col] = newNum;
}

void Twenty48::shiftTiles(char direction) {
    if (direction == 'w') {
        for (int i = 1; i < 4; i++) { // starts at row 1 because row 0 cannot move
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != 0) { // Check if the current tile is not empty
                    int k = i;
                    while (k > 0 && board[k - 1][j] == 0) { // Shift the tile upwards as long as there are empty tiles above
                        board[k - 1][j] = board[k][j];
                        board[k][j] = 0;
                        k--;
                    }
                }
            }
        }
    } else if (direction == 'a') {
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j < 4; j++) { // starts at col 1 because col 0 cannot move
                if (board[i][j] != 0) { // Check if the current tile is not empty
                    int k = j;
                    while (k > 0 && board[i][k - 1] == 0) { // Shift the tile to the left as long as there are empty tiles to the left
                        board[i][k - 1] = board[i][k];
                        board[i][k] = 0;
                        k--;
                    }
                }
            }
        }
    } else if (direction == 's') {
        for (int i = 2; i >= 0; i--) { // ends at row 2 because row 3 cannot move
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != 0) { // Check if the current tile is not empty
                    int k = i;
                    while (k < 3 && board[k + 1][j] == 0) { // Shift the tile downwards as long as there are empty tiles below
                        board[k + 1][j] = board[k][j];
                        board[k][j] = 0;
                        k++;
                    }
                }
            }
        }
    } else if (direction == 'd') {
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) { // ends at col 2 because col 3 cannot move
                if (board[i][j] != 0) { // Check if the current tile is not empty
                    int k = j;
                    while (k < 3 && board[i][k + 1] == 0) { // Shift the tile to the right as long as there are empty tiles to the right
                        board[i][k + 1] = board[i][k];
                        board[i][k] = 0;
                        k++;
                    }
                }
            }
        }
    }
}

void Twenty48::mergeTiles(char direction) {
    if (direction == 'w') {
        for (int i = 1; i < 4; i++) { // Start at row 1 because row 0 cannot move
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == board[i - 1][j]) { // Check if current space equals space above
                    board[i - 1][j] *= 2; // Combine spaces by doubling the value of the above space
                    board[i][j] = 0; // Empty the current space
                }
            }
        }
    } else if (direction == 'a') {
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j < 4; j++) { // Start at column 1 because column 0 cannot move
                if (board[i][j] == board[i][j - 1]) { // Check if current space equals space to the left
                    board[i][j - 1] *= 2; // Combine spaces by doubling the value of the space to the left
                    board[i][j] = 0; // Empty the current space
                }
            }
        }
    } else if (direction == 's') {
        for (int i = 2; i >= 0; i--) { // Start at row 2 because row 3 cannot move
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == board[i + 1][j]) { // Check if current space equals space below
                    board[i + 1][j] *= 2; // Combine spaces by doubling the value of the space below
                    board[i][j] = 0; // Empty the current space
                }
            }
        }
    } else if (direction == 'd') {
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) { // Start at column 2 because column 3 cannot move
                if (board[i][j] == board[i][j + 1]) { // Check if current space equals space to the right
                    board[i][j + 1] *= 2; // Combine spaces by doubling the value of the space to the right
                    board[i][j] = 0; // Empty the current space
                }
            }
        }
    }
}

void Twenty48::moveBoard(char direction){
    // create copy of board to compare with after move/merge
    int copyArray[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            copyArray[i][j] = board[i][j];
        }
    }
    
    // given wasd, move all game pieces & collapse if needed
    // ie all items must end up against far left or far right
    while (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd') {
        cout << "Please pick a valid letter: w for up, a for left, s for down, d for right" << endl;
        cin >> direction;
    }
    
    shiftTiles(direction);
    mergeTiles(direction);
    shiftTiles(direction);
    
    // while board has not changed, ask user to try again
    while(equal(&copyArray[0][0], &copyArray[0][0] + 16, &board[0][0])) {
        cout << "Whoops! You cannot move in that direction currently. Pick another letter: ";
        cin >> direction;
        
        while (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd') {
            cout << "Please pick a valid letter: w for up, a for left, s for down, d for right" << endl;
            cin >> direction;
        }
        
        shiftTiles(direction);
        mergeTiles(direction);
        shiftTiles(direction);
    }
}

bool Twenty48::endGame() {
    //bool moveable = true;
    // return true if any index == 2048
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (board[i][j] == 2048) {
                cout << "Congratulations! You've achieved 2048!" << endl;
                cout << ":)" << endl;
                return true;
            }
        }
    }
    
    // first check if there's still an empty space to add pieces too
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    
    // next check if there's any pieces that can be combined by the player to make an empty space
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if ((i > 0 && board[i][j] == board[i - 1][j]) ||  // Check above
                (i < 3 && board[i][j] == board[i + 1][j]) ||  // Check below
                (j > 0 && board[i][j] == board[i][j - 1]) ||  // Check left
                (j < 3 && board[i][j] == board[i][j + 1])) { // Check right
                return false; // Game can continue since there are adjacent cells with the same value
            }
        }
    }
    
    cout << "You've lost!" << endl;
    cout << ":(" << endl;
    return true;
}

//The game!
void Twenty48::start() {
    Twenty48 game;
    char direction;
    cout << "Use your arrow keys to move the tiles. Tiles with the same number merge into one when they touch. Add them up to reach 2048!" << endl;
    
    while (!endGame()) {
        // TODO test that game runs correctly
        addPiece();
        print();
        cout << "Enter next move: ";
        cin >> direction;
        moveBoard(direction);
    }
}
} // end of namespace
