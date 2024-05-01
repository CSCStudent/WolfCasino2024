/*Nathan Rodarmel
* Professor: Robert Gilanyi
* CSC2034 Computer Science C++
* 30 April 2024
*
* CSC2034 Capstone Project
* Red vs Blue TicTacToe Game!
* Created by: Nathan Rodarmel
*
*
* Program Description: This program is a traditional TicTacToe game that allows two players to play against each other. The game is
*                      played on a standard 3x3 board where players take turns to place their markers (X or O) on the board. The game
*                      uses standard tic-tac-toe rules therefore, the first player to get three of their markers in a row (horizontally,
*                      vertically, or diagonally) wins the game. If all places on the board are filled and no player has won, the game
*                      will end in a draw. The game is implemented using a class called tttGameLogic that contains methods to initialize
*                      the board, print the board, check if a player has won, check if the game is a draw, and perform a player move. The
*                      game is run using the run() method that randomly selects a player to start the game and alternates between the two
*                      players until a win or draw condition is met. The game results are recorded in a file called Red_vs_Blue_match_results.txt,
*                      which logs the start date and time of each game and the winner of each game. The game also includes color-coded markers for
*                      each player (red for X and blue for O) to enhance the overall user experience.
*/

#include "S02591408.h" // Include TicTacToeNR.h for the tttGameLogic class
#include <iostream>     // Needed for input/output
#include <cstdlib>     // Needed for the <cstdlib> header for the rand() function
#include <ctime>      // Needed for the <ctime> header for seeding the random number generator
#include <fstream>   // Needed for file input/output

using namespace std; // Using the standard namespace

//Start of namespace CSC2034
namespace S02591408 {

    // Factory method to create an instance of Tic-tac-toe game logic
    tttGameLogic* tttGameLogic::makeGame() {
        return new tttGameLogic;
    }

    // Start the game
    void tttGameLogic::start()
    {
        run(); // Run the TicTacToe game
    }

    // Constructor
    tttGameLogic::tttGameLogic() {}

    // Destructor
    tttGameLogic::~tttGameLogic() {}

    // Define the size of the TicTacToe board
    const int boardSize = 3;
    // Define player markers
    const char player1 = 'X';
    const char player2 = 'O';

    // Board for the actual TicToeToe game
    char board[boardSize][boardSize];

    // Initialize the board with empty spaces
    void tttGameLogic::initialize_board() {
        for (int row = 0; row < boardSize; row++) {
            for (int column = 0; column < boardSize; column++) {
                board[row][column] = ' ';
            }
        }
    } // end of initialize_board

    // Print the TicTacToe board with row and column numbers
    void tttGameLogic::print_board() {
        cout << endl;
        cout << "    1   2   3\n";      // Print column numbers
        cout << "  -------------\n";    // Print horizontal line for board (formatting)
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " | ";
            for (int j = 0; j < 3; j++) {
                // Print markers with colors
                if (board[i][j] == 'X') {
                    cout << "\033[1;31m" << board[i][j] << "\033[0m"; // Red color for X
                }
                else if (board[i][j] == 'O') {
                    cout << "\033[1;34m" << board[i][j] << "\033[0m"; // Blue color for O
                }
                else {
                    cout << board[i][j];
                }
                cout << " | ";           // Print vertical line for board (formatting)
            }
            cout << endl;
            cout << "  -------------\n";  // Print horizontal line for board (formatting)
        }
        cout << endl;
    } // end of print_board

    // Check if a player has won
    bool tttGameLogic::check_win(char marker) {
        // Check rows
        for (int row = 0; row < boardSize; row++) {
            bool rowWin = true;
            // Check for row win condition
            for (int column = 0; column < boardSize; column++) {
                if (board[row][column] != marker) {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin) {
                return true;
            }
        }
        // Check columns
        for (int column = 0; column < boardSize; column++) {
            bool collumWin = true;
            //Check for column win condition
            for (int row = 0; row < boardSize; row++) {
                if (board[row][column] != marker) {
                    collumWin = false;
                    break;
                }
            }
            if (collumWin) {
                return true;
            }
        }
        // Check for diagonal win condition
        bool diagonal_LR_win = true;
        bool diagonal_RL_Win = true;
        for (int i = 0; i < boardSize; i++) {
            // Check diagonal from top left to bottom right
            if (board[i][i] != marker) {
                diagonal_LR_win = false;
            }
            // Check diagonal from top right to bottom left
            if (board[i][boardSize - i - 1] != marker) {
                diagonal_RL_Win = false;
            }
        } // if any of the diagonal win conditions are met, return true
        if (diagonal_LR_win || diagonal_RL_Win) {
            return true;
        }
        // If no win condition is met, return false
        return false;
    }  // end of check_win

    // Check if the game is a draw
    bool tttGameLogic::check_draw() {
        for (int row = 0; row < boardSize; row++) {
            for (int column = 0; column < boardSize; column++) {
                if (board[row][column] == ' ') {
                    return false;
                }
            }
        }
        return true;
    } // end of check_draw

    // Perform a player move
    void tttGameLogic::player_move(char player) {
        int row, column;
        string playerName = (player == 'X') ? "Player X" : "Player O";
        string playerColor = (player == 'X') ? "\033[1;31m" : "\033[1;34m"; // Red color for X, Blue color for O
        cout << playerColor << playerName << "\033[0m's turn" << endl; // Set color for player's marker and reset after displaying player's name

        bool validMove = false;
        while (!validMove) {
            cout << playerColor << playerName; // Print player with color
            cout << "\033[0m"; // Reset color
            cout << " Enter row (1-3): "; // Print prompt without color
            cin >> row;
            cout << playerColor << playerName; // Print player with color
            cout << "\033[0m"; // Reset color
            cout << " Enter column (1-3): "; // Print prompt without color
            cin >> column;
            row--;
            column--;

            // Check if the move is valid
            if (row < 0 || row >= boardSize || column < 0 || column >= boardSize || board[row][column] != ' ') {
                cout << "Invalid move! Try again." << endl;
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                continue;
            }
            // If the move is valid, place the player's marker on the board
            else {
                validMove = true;
                board[row][column] = player;
            }
        }
    } // end of player_move

  // Run the TicTacToe game
    void tttGameLogic::run() {
        ofstream outputFile;
        outputFile.open("Red_vs_Blue_match_results.txt", ios::app); // Open the file for recording game results 
        if (!outputFile.is_open()) {
            cout << "Error: Unable to open file for writing!" << endl; // Print error message if file cannot be opened
            return;
        }

        cout << endl;
        cout << "Created by: \033[38;5;208mNathan Rodarmel\033[0m" << endl;// Print the creator's name in bright orange to the console

        // Initialize the game loop
        bool playAgain = true;
        while (playAgain) {
            // Get current date and time (used for logging game wins, losses, and draws)
            time_t now = time(0);
            tm localTime;
            localtime_s(&localTime, &now); // Use localtime_s instead of localtime (avioding unsafe function notification)
            char dateTime[100];
            strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %X", &localTime); // Format the date and time (Had to google this)
            outputFile << "Game started at: " << dateTime << endl;           // Print the start date and time to the console and to the file

            // Print the welcome message to the console
            cout << endl;
            cout << "-------------------------------------" << endl;
            cout << "| Welcome to \033[1;31mRed\033[0m \033[1;37mVS\033[0m \033[1;34mBlue\033[0m TicTacToe! |" << endl;  // Print the game title respective colors
            cout << "-------------------------------------" << endl;
            cout << endl;

            char readyChoice;          // Variable to store the user's choice if they are ready to play
            bool playersReady = false; // Variable to check if players are ready to play

            while (!playersReady) {
                string playerXColor = "\033[1;31mPlayer X\033[0m";  // Red color for Player X
                string playerOColor = "\033[1;34mPlayer O\033[0m";  // Blue color for Player O
                cout << "Are " << playerXColor << " and " << playerOColor << " ready? (Y/N): ";  // Print ready message compelete with player names and respective colors
                cin >> readyChoice;
                // Check if players are ready to play
                if (toupper(readyChoice) == 'Y') {
                    playersReady = true;
                }
                // End the game if players are not ready
                else if (toupper(readyChoice) == 'N') {
                    cout << "Exiting..." << endl;
                    outputFile << "Game exited without playing." << endl;
                    outputFile.close(); // Close the results file 
                    return;
                }
                // Prompt the user to enter a valid choice if the input is invalid (input is not 'Y' or 'N')
                else {
                    cout << "Invalid choice! Please enter Y or N." << endl;
                }
            } // end of while(!playersReady)

            // Initialize the board and print it to console
            initialize_board();
            print_board();

            srand(time(0)); // Seed the random number generator
            int randomNumber = rand(); // Generate a random number
            char currentPlayer = (randomNumber % 2 == 0) ? 'X' : 'O'; // Randomly select the player to start the game

            while (true) {
                // Player's turn
                player_move(currentPlayer);
                print_board();
                if (check_win(currentPlayer)) {
                    // Print the game winner in the console in color and to the file, recording the results
                    cout << (currentPlayer == 'X' ? "\033[1;31mPlayer X wins!\033[0m\n" : "\033[1;34mPlayer O wins!\033[0m\n"); // Print the winner in color (red or blue respectively)
                    outputFile << (currentPlayer == 'X' ? "Player X was the winner (Red)!\n" : "Player O was the winner  (Blue)!\n"); // Record the winner in the file
                    break;
                }
                if (check_draw()) {
                    // Print the game result "draw" in the console and to the file
                    cout << "It's a draw!" << endl;
                    outputFile << "Match ended in a draw!" << endl;
                    break;
                }
                // Switch to the other player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            } // end of while(true)

            char playAgainOption;
            cout << "Do you want to play again? (Y/N): ";
            cin >> playAgainOption;
            // Check if the user wants to play again
            if (toupper(playAgainOption) != 'Y') {
                playAgain = false;
                cout << endl;
                // Print the closing message to the console
                cout << "Thank you for playing TicTacToe!" << endl;
                cout << "To see the winners of each round check the game_results.txt file!" << endl;
                cout << endl;
            }
            else {
                cout << endl;
                cout << "Restarting the game..." << endl;  // Print the restart message to the console
            }
        } // end of while(playAgain)

        outputFile.close(); // Close the file stream
    } // end of tttGameLogic::run


} // end of namespace CSC2034