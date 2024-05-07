#include <iostream>
#include <ctime>
#include "S02469787.h"
#include <iomanip>
#include <limits>

//defined namespace for project
namespace S02469787 {
    //Constructor
    TicTacToe::TicTacToe()
    {
        for ( int i = 0; i < 3; ++i )
        {
            for ( int j = 0; j < 3; ++j )
            {
                board[i][j] = ' ';
            }
        }
    }

    TicTacToe* TicTacToe::makeGame() {
        return new TicTacToe;
    }

    //The game!
    void TicTacToe::start() {
        TicTacToe game;
        int playerNum = -1;
        std::cout << "Game has started" << std::endl;
        game.print( );
        std::cout << "Player 1" << std::endl << std::endl;
        while ( !game.checkWinner( ))
        {
            game.playerMove( playerNum );
           
        }


    }

    void TicTacToe::print( )
    {
        int num = 0;
        // Print column labels
        cout << setw( 10 ) << "  0   1   2   <- x values" << endl;
        cout << setw( 10 ) << "  --|---|---| y values " << endl;

        // Print rows with row labels and board content
        for ( int i = 0; i < 3; ++i )
        {
            for ( int j = 0; j < 3; ++j )
            {
                cout << "| " << board[i][j] << " ";
            }
            cout << "| " << num << endl;
            num++;
        }
    }


    bool TicTacToe::playerMove(int & playerNum )
    {
        if ( playerNum == -1 )
        {
            playerNum = 1;
        }
        int xValue = -1;
        int yValue = -1;
        try
        {
            cout << "enter in a X value" << endl;
            cin >> yValue;
            if ( !cin )
            {
                cin.clear( ); // Clear error state
                cin.ignore( numeric_limits<streamsize>::max( ), '\n' ); // Discard the input buffer
                throw invalid_argument( "Invalid input. Please enter a number." );
            }
            cout << "enter in a Y value" << endl;
            cin >> xValue;
            if ( !cin )
            {
                cin.clear( ); // Clear error state
                cin.ignore( numeric_limits<streamsize>::max( ), '\n' ); // Discard the input buffer
                throw invalid_argument( "Invalid input. Please enter a number." );
            }
            if ( xValue < 0 || xValue > 2 || yValue < 0 || yValue > 2 )
            {
                throw out_of_range( "Coordinates out of range. ENTER COORDINATES AGAIN" );
            }

            if ( board[xValue][yValue] == 'X' || board[xValue][yValue] == 'O' )
            {
                throw invalid_argument( "Cell already occupied. ENTER COORDINATES AGAIN" );
            }

            if ( playerNum == 1 )
            {
                board[xValue][yValue] = 'X';
            }
            else
            {
                board[xValue][yValue] = 'O';
            }

            print( );
            if ( playerNum == 1 )
            {
                playerNum = 2;
                cout << "Player 2" << endl;
            }
            else if ( playerNum == 2 )
            {
                playerNum = 1;
                cout << "Player 1" << endl;
            }
            return true;
        }
        catch ( const out_of_range& e )
        {
            cout << "Error: " << e.what( ) << endl;
        }
        catch ( const invalid_argument& e )
        {
            cout << "Error: " << e.what( ) << endl;
        }
        catch ( ... )
        {
            cout << "An unexpected error occurred. ENTER COORDINATES AGAIN" << endl;
        }
        return false;
    }

    bool TicTacToe::checkWinner( )
    {
        int xCount = 0;
        int oCount = 0;
        int count = 0;
        int emptySpaces = 0;
        bool isFull = false;
        bool threeInRow = false;
        //horizontal check 
      
        while ( count < 1 )
        {
            for ( int j = 0; j < 3; j++ ) // Loop through columns
            {
                for ( int i = 0; i < 3; i++ ) // Loop through rows
                {
                    if ( board[j][i] == 'X' )
                    {
                        xCount++;
                    }
                    else if ( board[j][i] == 'O' )
                    {
                        oCount++;
                    }
                }
                // If any player has 3 in a row horizontally, the loop should end
                if ( xCount == 3 || oCount == 3 )
                {
                    count = 1;
                    threeInRow = true;
                    break; 
                }

                xCount = 0;
                oCount = 0;
            }

            if ( threeInRow == true )
            {
                break;
            }
            xCount = 0;
            oCount = 0;
            // vertical check
            for ( int j = 0; j < 3; j++ ) // Loop through rows
            {
                for ( int i = 0; i < 3; i++ ) // Loop through columns
                {
                    if ( board[i][j] == 'X' )
                    {
                        xCount++;
                    }
                    else if ( board[i][j] == 'O' )
                    {
                        oCount++;
                    }
                }
                // If any player has 3 in a row horizontally, the loop should end
                if ( xCount == 3 || oCount == 3 )
                {
                    count = 1;
                    threeInRow = true;
                    break; // Exit the loop if 3 in a row is found
                }
                xCount = 0;
                oCount = 0;
            }


            if ( threeInRow == true )
            {
                break;
            }
            xCount = 0;
            oCount = 0;
        
            // horizontal check left to right
            for ( int i = 0; i < 3; i++ )
            {
                if ( board[i][i] == 'X' )
                {
                    xCount++;
                }
                else if ( board[i][i] == 'O' )
                {
                    oCount++;
                }
            }
            if ( xCount >= 3 || oCount >= 3 )
            {
                threeInRow = true;
                break;
            }
            if ( threeInRow == true )
            {
                break;
            }
            xCount = 0;
            oCount = 0;
            //check right to left
            for ( int i = 0, j = 2; i < 3; i++ )
            {
                if ( board[j][i] == 'X' )
                {
                    xCount++;
                    j--;
                }
                else if ( board[j][i] == 'O' )
                {
                    oCount++;
                    j--;
                }
                else
                {
                    j--;
                }
            }
            if ( xCount >= 3 || oCount >= 3 )
            {
                break;
            }
            count++;
        }
    

        if ( xCount >= 3  )
        {
            cout << "player 1 has won" << endl;
            return true;
        }
        else if ( oCount >= 3 )
        {
            cout << "player 2 has won" << endl;
            return true;
        }
        //check if game is a draw
        else
        {
            for ( int i = 0; i < 3; ++i )
            {
                for ( int j = 0; j < 3; ++j )
                {
                    if ( board[i][j] != 'X' && board[i][j] != 'O')
                    {
                        emptySpaces++;
                    }
                   
                }
            }
            if ( emptySpaces >= 1 )
            {
                isFull = false;

            }
            else
            {
                isFull = true;
            }
            if ( isFull == true )
            {
                cout << "Game is a draw end of game" << endl;
                return true;
            }
            else
            {
                return false;
            }
        }
  
    }


} // end of namespace