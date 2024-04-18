#include <iostream>
#include <ctime>
#include "TicTacToeGame.h"
#include <stdio.h>
#include <sqlite3.h> 

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   sqlite3_close(db);
} //yes i added an sqlite3

//defined namespace for project
namespace CSC2034
{
    //Constructor
    TicTacToeGame::TicTacToeGame()
    {

    }

    TicTacToeGame* TicTacToeGame::makeGame() {
        return new TicTacToeGame;
    }

    //The game!
    void TicTacToeGame::start() {

    }

} // end of namespace
