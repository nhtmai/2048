/*************************************************************************
Name: Mai Nguyen
Date: June 19, 2020
File name: 2048
Description: This program will allow user to play a game of 2048.
Functions:
 getNum(int, int) returns int - gets an integer input from user within a
 provided range + error handling
 getChar() returns char - gets an character input from user + error handling
 moveBlocks(string, string, int array) returns nothing - moves the blocks
 in the direction of input
 generateBlocks() returns nothing - generate blocks on the board
 checkForMovables() returns nothing - checks if blocks can be moved if
 there's no empty space
 colorize(int) returns nothing - sets a background colour for each block
 in the game board
 displayGame() returns nothing - displays the header, scores, and gameboard
*************************************************************************/
 
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>
#include <string>
using namespace std;
 
//initializing the size of the board
const int rows = 4, columns = 4, width = 6;
 
//declaring arrays
int display[columns][rows];
int blank[columns][rows];
bool combined[columns][rows];
int tempBoard[columns][rows]; //to check if there are moves left even if there's no empty space
 
//variables to hold scores
bool newHighScore = true;
string highScoreName = "no one";
int score = 0, highScore = 0, prevHighScore = 0;
 
int counter; //variable used to generate new blocks and check if there is empty spaces in the gameboard
 
//booleans
bool moved = true; //check if the blocks have moved after a turn
bool movable = true; //check if there are moves left if there's no empty space
bool win, leave, again; //check if game needs to be exited
 
//declaring functions
int getNum(int min, int max);
char getChar();
void moveBlocks(string axis, string startAt, int board[][rows]);
void generateBlocks();
void checkForMovables();
void colorize(int num);
void displayGame();
 
int main() {
 
 //variables to take user input
 bool correct;
 int enteredInt;
 char enteredChar;
 
 //prepping time seed
 srand (time(NULL));
  //intro
 cout << "----------------------- 2048 -----------------------" << endl << endl;
 cout << "INSTRUCTIONS AND GAMEPLAY:" << endl;
 cout << "- The game will start with 2 blocks" << endl;
 cout << "- You input a move (w for up, a for left, s for down, d for right)" << endl;
 cout << "- The blocks will move in the direction of your input" << endl;
 cout << "- A random block (2 or 4) will be generated after every move" << endl;
 cout << "- If there are no more moves possible, game ends" << endl<< endl;
 cout << "SCORING:" << endl;
 cout << "- For every block combined together, add the new block to the score" << endl;
 cout << "- Display the score through every move and record the high score" << endl << endl;
 cout << "*NUMBERS LARGER THAN 4 DIGITS WILL NOT COMBINE*" << endl << endl;
 cout << "ENTER 1 TO START THE GAME: ";
 enteredInt = getNum(1, 1);
 cout << endl;
 
 do{
   //resetting the gameboards for the new game
   for(int i = 0; i < rows; i++){
     for(int j = 0; j < columns; j++){
       display[j][i] = 0;
       combined[j][i] = false;
     }
   }
 
   //resetting variables
   score = 0;
   newHighScore = false;
   moved = true;
   win = false;
   movable = true;
   leave = false;
  
   generateBlocks();
 
   do{
     //create new block if the previous move moved blocks
     if(moved == true){ generateBlocks(); }
     //check if there are moves left if there’s no empty space
     if(counter == 0){ checkForMovables(); }
    
     displayGame(); //displaying game board
 
     if(movable == true){ //if there are moves left
       //display menu
       cout << "INPUT YOUR MOVE:" << endl;
       cout << "w = up" << endl;
       cout << "a = left" << endl;
       cout << "s = down" << endl;
       cout << "d = right" << endl << endl;
       cout << "k = exit the game" << endl << endl;
       cout << "OPTION CHOSEN: ";
    
       do{
         correct = true;
      
         //user inputs the direction of moves
         enteredChar = getChar();
 
         //interprets direction
         switch (enteredChar){
           case 'W': case 'w': //up
             moveBlocks("column", "min", display); break;
           case 'A': case 'a': //left
             moveBlocks("row", "min", display); break;
           case 'S': case 's': //down
             moveBlocks("column", "max", display); break;
           case 'D': case 'd': //right
             moveBlocks("row", "max", display); break;
           case 'K': case 'k': //exit
             leave = true; break;
           default: //incorrect input
             correct = false;
             cout << "INVALID INPUT! Please try again: ";
             break;
         }
       }while(correct == false); //loops if input is incorrect
 
       //hold data to display new high score message
       if(score > highScore){
         prevHighScore = highScore;
         newHighScore = true;
       }
 
     }else{ //if there are no moves left, player loses
       win = false;
       leave = true;
 
       //displaying losing message
       cout << "GAME OVER!!" << endl;
       usleep(1750000);
     }
 
     if(win == true){ //if player won
       displayGame(); //displaying game board and scores
 
       //display winning message
       cout << "YOU WIN!" << endl << endl;
       usleep(1750000);
 
       cout << "Do you want to continue playing?" << endl;
       cout << "1 to continue" << endl;
       cout << "2 to quit" << endl << endl;
       cout << "OPTION CHOSEN: " << endl;
      
       //gets input from user to quit after winning
       enteredInt = getNum(1, 2);
       switch (enteredInt){
         case 1:
           leave = false;
           win = false;
           break;
         case 2:
           leave = true;
           break;
       }
 
       cout << endl;
     }
 
   }while(leave == false);
 
   //display new high score message if there's a high score
   if(newHighScore == true){
     highScore = score;
     cout << endl << "CONGRATULATIONS! YOU GOT A NEW HIGH SCORE!" << endl;
     cout << "Previous High Score: " << prevHighScore << endl;
     cout << "Your Score: " << score << endl << endl;
     cout << "Enter your name: ";
     getline(cin, highScoreName);
   }
 
   //ask player if they want to play again
   cout << endl << "Do you want to play again?" << endl;
   cout << "1 to play again" << endl;
   cout << "2 to quit the game" << endl << endl;
   cout << "OPTION CHOSEN: " << endl;
  
   //gets user input
   enteredInt = getNum(1, 2);
   cout << endl;
 
   //interpretting user input
   switch (enteredInt){
     case 1:
       again = true;
       break;
     case 2:
       cout << "The high score is " << highScore << ", currently held by " << highScoreName << '.' << endl << endl;
       cout << "Thank you for playing!" << endl;
       again = false;
       break;
   }
 
 }while(again == true);
 
}
 
char getChar(){
 char check;
 string scoop;//for error handling
 
 while(true){//error handling
   cin >> check;
   getline(cin, scoop);
   if(scoop.length() > 0){
     cout << "INVALID INPUT! Please try again: ";
     continue;
   }
   break;
 }
 
 return check;
}
 
int getNum(int min, int max){
 int num;
 string scoop;
 
 while(true){//error handling
   cin >> num;
   if(cin.fail() || num < min || num > max){//error handling
     cin.clear();
     cin.ignore(100, '\n');
     cout << "INVALID INPUT! Please try again: ";
     continue;
   }
   getline(cin , scoop);
   if(scoop.length() > 0){//error handling
     cout << "INVALID INPUT! Please try again: ";
     continue;
   }
   break;
 }
 
 return num;
}
 
void moveBlocks(string axis, string startAt, int board[][rows]){
 //declaring variables
 int start, end, next, moveX, moveY, restrX, restrY;
 int x, y, compare;
 bool nextIsCombinable;
 
 //defining variables to move the blocks depending on direction
 moved = false;
 if(startAt == "min"){
   start = 0;
   end = 3;
   next = 1;
 }else{
   start = 3;
   end = 0;
   next = -1;
 }
 if(axis == "column"){
   moveY = -1*next;
   moveX = 0;
   restrX = -5;
   restrY = start;
 }else{
   moveX = -1*next;
   moveY = 0;
   restrY = -5;
   restrX = start;
 }
  //goes row by row/column by column
 for(int h = 0; h < 4; h++){
   if(axis == "column"){ x = h; }
   if(axis == "row"){ y = h; }
 
   //goes block by block
   for(int c = start; c != end+next; c+= next){
     if(axis == "column"){ y = c; }
     if(axis == "row"){ x = c; }
 
     //moves block
     if(board[x][y] != 0){
       while(x != restrX && y != restrY){
         compare = board[x+moveX][y+moveY];
 
         //checks if blocks can be combined
         if(compare == board[x][y] &&
            combined[x+moveX][y+moveY] == false && combined[x][y] == false &&
            compare != 8192 && board[x][y] != 8192){
           nextIsCombinable = true;
         }else{
           nextIsCombinable = false;
         }
 
         if(compare == 0){//if there's empty space next to the block, move block by 1
           moved = true;
           board[x+moveX][y+moveY] = board[x][y];
           board[x][y] = 0;
         }else if(nextIsCombinable == true){ //combining blocks
           moved = true;
           board[x+moveX][y+moveY] *= 2;
           board[x][y] = 0;
           score += board[x+moveX][y+moveY];
           combined[x+moveX][y+moveY] = true;
           //if a block gets to 2048
           if(board[x+moveX][y+moveY] == 2048){ win = true; }
         }else{//if the block can't move
           break;
         }
 
         //set new coordinates
         x+=moveX;
         y+=moveY;
       }
     }
   }
 
 }
 
 //reset combined array
 for(int i = 0; i < rows; i++){
   for(int j = 0; j < columns; j++){
     combined[j][i] = false;
   }
 }
 
}
 
void generateBlocks(){
 //variables
 const int generateNums = 2;
 int generate[generateNums] = {2,4};
 int randLoc, randNum;
 counter = 0;
 
 //filling the blank array
 for(int i = 0; i < rows; i++){
   for(int j = 0; j < columns; j++){
     if(display[j][i] == 0){
       counter++;
       blank[j][i] = counter;
     }else{
       blank[j][i] = 0;
     }
   }
 }
 
 //randomizing the location and value of the block
 randLoc = rand() % counter + 1;
 randNum = rand() % generateNums;
 
 //generate and placing the block
 for(int i = 0; i < rows; i++){
   for(int j = 0; j < columns; j++){
     if(blank[j][i] == randLoc){
       display[j][i] = generate[randNum];
     }
   }
 }
 
 counter--;
}
 
void checkForMovables(){
 //declaring variables
 const int numOfMoves = 4;
 int scoreSaver;
 string checkAxis[numOfMoves] = {"column", "column", "row", "row"};
 string checkStartAt[numOfMoves] = {"min", "max", "min", "max"};
 movable = false;
 
 //make tempBoard identical to display
 for(int i = 0; i < rows; i++){
   for(int j = 0; j < columns; j++){
     tempBoard[j][i] = display[j][i];
   }
 }
 
 //saves the score if the score changes from the function
 scoreSaver = score;
 
 //moves the blocks in the tempBoard
 for(int g = 0; g < numOfMoves; g++){
   moveBlocks(checkAxis[g], checkStartAt[g], tempBoard);
 }
 
 //if the blocks in the tempBoard moved, then there are still moves left
 for(int i = 0; i < rows; i++){
   for(int j = 0; j < columns; j++){
     if(display[j][i] != tempBoard[j][i]){ movable = true; }
   }
 }
 
 //reset score to the original score
 score = scoreSaver;
 
}
 
void colorize(int num){
 string colour;
 
 switch(num){ //colour IDs
   case 2: colour = "33"; break;
   case 4: colour = "31"; break;
   case 8: colour = "29"; break;
   case 16: colour = "64"; break;
   case 32: colour = "66"; break;
   case 64: colour = "68"; break;
   case 128: colour = "105"; break;
   case 256: colour = "103"; break;
   case 512: colour = "101"; break;
   case 1024: colour = "136"; break;
   case 2048: colour = "209"; break;
   case 4096: colour = "211"; break;
   case 8192: colour = "213"; break;
   default: colour = "255"; break;
 }
 
 //setting background colours
 cout << "\033[1m\033[48;5;" << colour << "m";
 
}
 
void displayGame(){
 //declaring variables
 int spaces, digits;
 
 //displaying the header
 system("clear");
 cout << "----------------------- 2048 -----------------------" << endl << endl;
 
 //displaying scores
 cout << "HIGH SCORE: ";
 if(newHighScore == true){
   cout << score  << " NEW" << endl;
 }else{
   cout << highScore << " (" << highScoreName << ')' << endl;
 }
 cout << "SCORE: " << score << endl << endl;
 
 //displaying the board
 for(int i = 0; i < rows; i++){//goes row by row
   for(int f = 0; f < 3; f++){//goes line by line (3 lines per block)
     for(int j = 0; j < columns; j++){//goes block by block
       switch(f){
         case 0:
         case 2: //top and bottom row of a block
           colorize(display[j][i]);
           cout << setw(width) << "";
           cout << "\033[0m";
           break;
         case 1: //middle row of a block
           digits = to_string(display[j][i]).length();
           spaces = (width-digits)/2;
          
           colorize(display[j][i]);
           cout << setw(spaces) << "";
 
           if(display[j][i] == 0){ cout << ' ';}
           else{ cout << display[j][i];}
 
           cout << setw(spaces+(width-digits)%2) << "";
           cout << "\033[0m";
           break;
       }
     }
     cout << endl;
   }
 }
 
 cout << endl;
}