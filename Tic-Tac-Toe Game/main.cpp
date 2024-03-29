#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void graphics(char gamePosition[3][3]) { // The graphics function displays the gameboard
    cout << "\n\n" << setw(30) <<"Tic Tac Toe\n";
    cout << "\n"<< setw(38)<< "Player 1 (X)-Player 2 (O)\n\n";
    cout << setw(30) << "|        | \n";
    cout << setw(15) << gamePosition[0][0] << "   |   " << gamePosition[0][1] << "    |   " << gamePosition[0][2] << endl;
    cout << setw(30) << "|        | \n";
    cout << setw(37) << "__________________________\n";
    cout << setw(30) << "|        | \n";
    cout << setw(15) << gamePosition[1][0] << "   |   " << gamePosition[1][1] << "    |   " << gamePosition[1][2] << endl;
    cout << setw(30) << "|        | \n";
    cout << setw(37) << "__________________________\n";
    cout << setw(30) << "|        | \n";
    cout << setw(15) << gamePosition[2][0] << "   |   " << gamePosition[2][1] << "    |   " << gamePosition[2][2] << endl;
    cout << setw(30) << "|        | \n";
}

string name(bool currentPlayer) { // The name function assigns the name of the player
    char currentChar;
    if (currentPlayer == true) {
        currentChar = 'X';
        return "Player 1";
    }
    else {
        currentChar = 'O';
        return "Player 2";
    }
}

char symbol(bool currentPlayer) { // The name function assigns the name of the player
    if (currentPlayer == true) {
        return 'X';
    }
    else {
        return 'O';
    }
}

bool gameLogic(char gamePosition[3][3]) { // The gameLogic function checks if there is a winner
    for (int i = 0; i < 3; i++) { // Finds horizontal and vertical win condition
        if (gamePosition[i][0] == 'X' && gamePosition[i][1] == 'X' && gamePosition[i][2] == 'X') {          
            return true;
        }
        else if (gamePosition[0][i] == 'X' && gamePosition[1][i] == 'X' && gamePosition[2][i] == 'X') {
            
            return true;
        }
        if (gamePosition[i][0] == 'O' && gamePosition[i][1] == 'O' && gamePosition[i][2] == 'O') {
            return true;
        }
        else if (gamePosition[0][i] == 'O' && gamePosition[1][i] == 'O' && gamePosition[2][i] == 'O') {

            return true;
        }
    }
    if (gamePosition[0][0] == 'X' && gamePosition[1][1] == 'X' && gamePosition[2][2] == 'X') { // Finds diagonal win condition
        return true;
    }
    else if (gamePosition[0][2] == 'X' && gamePosition[1][1] == 'X' && gamePosition[2][0] == 'X') { // Finds diagonal win condition
        return true;
    }
    if (gamePosition[0][0] == 'O' && gamePosition[1][1] == 'O' && gamePosition[2][2] == 'O') { // Finds diagonal win condition
        return true;
    }
    else if (gamePosition[0][2] == 'O' && gamePosition[1][1] == 'O' && gamePosition[2][0] == 'O') { // Finds diagonal win condition
        return true;
    }
    return false;
}

bool freeSpace(char gamePosition[3][3], int row, int column) { // The freeSpace function checks if spot is avaliable
    row--;
    column-- ;
    if (gamePosition[row][column] == 'X' || gamePosition[row][column] == 'O') {
        return false;
    }
    else {
        return true;
    }
}

bool userInput(bool currentPlayer, char gamePosition[3][3], int *row, int *column ) { // The user input gets the position the player wants
    bool validSpot = false;
    string playerName = name(currentPlayer);

    while (validSpot == false) {
        while (*row < 1 || *row > 3) {
            cout << setw(11) << playerName << " please enter a row number(1-3): ";
            cin >> *row;
            if (*row < 1 || *row >3) {
                cout << setw(16) << "Invalid Row!\n";
            }
        }
        while (*column < 1 || *column >3 ) {
            cout << setw(11) << playerName << " please enter a column number(1-3): ";
            cin >> *column;
            if (*column < 1 || *column>3) {
                cout << setw(19) << "Invalid Column!\n";
            }
        }
        if (freeSpace(gamePosition, *row, *column) == false) {
            cout << setw(34) << "Spot already taken! Try Again!\n";
            *row = 0;
            *column = 0;
        }
        else {
            validSpot = true;
        }
    }
    return true;
}

void main() {
    // Intializes variables  
    bool currentPlayer = true;
    bool gameOn = true;
    bool gameWon = false;

    while (gameOn == true) {
        char gamePosition[3][3] = { {'*','*','*'}, 
                                    {'*','*','*'}, 
                                    {'*','*','*'}}; // Intializes gameboard and resets it
        int turnCounter = 0; // Counts the number of turns
        char playAgain = ' ';
        graphics(gamePosition); // Displays game graphics
        while (gameWon == false) { // While loop that keeps game on
            int row = 0;
            int column = 0;
            bool validSpot = false;
            while (validSpot == false) { // Checks if spot is valid
                string playerName = name(currentPlayer);               
                validSpot = userInput(currentPlayer, gamePosition, &row, &column);
            }
            char currentChar = symbol(currentPlayer);
            gamePosition[row - 1][column - 1] = currentChar; // Assigns place in gameboard with current symbol
            gameWon = gameLogic(gamePosition);
            system("cls"); // Clears screen to make game more fluid
            graphics(gamePosition); // Reprints gameboard
            if (gameWon == true) { // Ends and congratulates the winner 
                string playerName = name(currentPlayer);
                cout << setw(19) << "Congradulations " << playerName << "! You Win!\n";
                break;
            }
            currentPlayer = !currentPlayer; // Changes player at the end of each turn
            turnCounter++;
            if (turnCounter > 8) { // Ends game if there is a tie
                cout << setw(25) << "Tie Game! Nobody Wins!" << endl;
                break;
            }
         }
        
        while (playAgain != 'y' && playAgain != 'n') { // while loop ask if players want to play again
            cout << setw(39) << "Would you like to play again? (y/n) ";
            cin >> playAgain;
            if (playAgain != 'y' && playAgain != 'n') {
                cout << setw(21) << "Invalid Response!\n";
            }
        }
        if (playAgain == 'n') {
            gameOn = false;
        }
        if (playAgain == 'y') {
            gameWon = false;
            system("cls");
        }
     }
 }
