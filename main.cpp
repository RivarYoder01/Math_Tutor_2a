#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

/*-----------------------------------------------------------------------------------------------
Program--------;Simple Math Tutor
Programmer-----:Alyssa Yoder
Date-----------:September 16th 2022
Repl.it--------:https://replit.com/@Alyode01/Alyssa-Yoder-Math-Tutor#main.cpp
-------------------------------------------------------------------------------------------------
Description----:This program will display a welcome message and then ask for the
---------------:users name. It will then generate 2 numbers to be added,
subtracted,
---------------:multiplied, or divided. If the first number is larger than the
second
---------------:number, the two numbers will be swapped in order to avoid
negative
---------------:numbers. If a divisor is generated the first number is
multiplied by
---------------:the second number to avoid decimals. The user gets 3 tries to
get a
---------------:question right will be given the percentage they get right. All
this
---------------:in contained in a while loop, the user will receive a report at
the
---------------:end showing what they got right and wrong
-------------------------------------------------------------------------------------------------*/

int main() {
  enum MathType { ADD, SUB, MULT, DIV };
  string userName = "?";
  string contGame = "y";
  char mathOp = '?'; // type of math opperator determined by mathType
  const int MAX_ATTEMPTS = 3;
  int leftNum = 0;        // random number between 1 and 10
  int rightNum = 0;       // random number between 1 and 10
  int mathType = 0;       // random number between 0 and 3
  int temp = 0;           // temporary variable incase leftNum > rightNum
  int correctAwns = 0;    // correct awnser to math question
  int userGuess = 0;      // user input, must match correctAwns
  int totalQuestions = 0; // amount of questions that have been asked
  int totalCorrect = 0;   // amount of times the user getts a question right
  int attempts = 0;       // amount of attempts the user uses
  vector<vector<int>> mathQuestions; // 2D vector used to store leftNum, mathOp,
                                     // and rightNum

  cout << "*--------------------------------------------*" << endl;
  cout << "|                Math Tutor                  |" << endl;
  cout << "*--------------------------------------------*" << endl;
  cout << endl;

  cout << "Please enter your first name." << ' ';
  // user inputs their first name
  getline(cin, userName);

  cout << "Hello, " << userName << "! :3";
  cout << endl;

  srand(time(0));

  while (contGame == "yes" || contGame == "y") {
    totalQuestions++;
    leftNum = rand() % 10 + 1;  // random number between 1 and 10
    rightNum = rand() % 10 + 1; // random number between 1 and 10
    mathType = rand() % 4;      // random number between 0 and 3, this determine
                                // the sign between the two numbers

    if (leftNum < rightNum) { // if leftNum < rightNum the two must be swapped
                              // to avoid a negative number result
      temp = leftNum;
      leftNum = rightNum;
      rightNum = temp;
    } // The random number generated for mathType will determine the math signs

    switch (mathType) {
    case ADD:
      mathOp = '+';
      correctAwns = leftNum + rightNum;
      break;
    case SUB:
      mathOp = '-';
      correctAwns = leftNum - rightNum;
      break;
    case MULT:
      mathOp = '*';
      correctAwns = leftNum * rightNum;
      break;
    case DIV:
      mathOp = '/';
      correctAwns =
          leftNum; // to avoid decimals, leftNum is multiplied by rightNum
      leftNum *= rightNum;
      correctAwns = leftNum / rightNum;
      break;
    default: // if the mathType is invalid an error will appear and end the
             // program]
			
      cout << endl;
      cout << "Invalid question type: " << mathType << endl;
      cout << "Program ended with an error -1" << endl;
      cout << "Please report this error to Alyssa Yoder :/ " << endl;
      return -1;
    }

    vector<int> row = {leftNum, mathType, rightNum};
    // 2D vector that will store information for each question
    for (int i = 0; i <= MAX_ATTEMPTS;
         i++) { // MAX_ATTEMPTS is the maximun amount of attempt
      cout << leftNum << ' ' << mathOp << ' ' << rightNum << " = ";
      // math question displays and user inputs their awnser as userGuess

      while (!(cin >> userGuess)) { // logic used to make sure input is numaric
        cin.clear();
        cin.ignore();
        cout << "Invalid. Please input a number." << endl;
        cout << endl;
      }
      if (correctAwns == userGuess) {
        row.push_back(userGuess);   // stores userGuess into vector
        row.push_back(correctAwns); // stores correctAwns into vector
        totalCorrect++;
        cout << endl;
        cout << "Correct! :D" << endl;
        break;
      } else {
        row.push_back(userGuess);   // stores userGuess into vector
        row.push_back(correctAwns); // stores correctAwns into vector
        attempts++;
        cout << endl;
        cout << "Incorrect. :(" << endl;
        cout << "You have " << MAX_ATTEMPTS - i << " tries left." << endl;
        // user is told how many tries they have left

        if (i == MAX_ATTEMPTS) {
          cout << "You are out of tries. The correct awnser is: " << correctAwns
               << endl;
          row.push_back(0);
          // if MAX_ATTEMPTS reaches 0, the user will be given a new question
        }
      }
    }
    mathQuestions.push_back(row);

    // logic used to make sure correct information is being stored
    /* for (int i = 0; i < mathQuestions.size(); i++) {
        for (int j = 0; j < mathQuestions.at(i).size(); j++) {
          cout << mathQuestions.at(i).at(j);
        }
        cout << endl;
     } */

    cout << "   --------------------------------------     " << endl;
    cout << endl;
    cout << "Would you like another question?" << ' ';
    contGame = '?';

    while (contGame != "y" && contGame != "yes" && contGame != "n" &&
           contGame != "no") {
      cin >> contGame;
      // user is asked to continue, if they put in n or no, the game ends and
      // report is made
      for (int i = 0; i < contGame.size(); i++) {
        (contGame.at(i)) = tolower(contGame.at(i));
      }
      // logic used to make sure user input is all lower case
      if (contGame != "y" && contGame != "yes" && contGame != "n" &&
          contGame != "no") {
        cout << "Invalid. Please enter y, yes, n, or no.";
        // logic used to make sure user putts in y, yes, n, or no
      }
    }
  }
  cout << endl;
  cout << "*--------------------------------------------*" << endl;
  cout << "           Math Tutor Detail Report           " << endl;
  cout << "*--------------------------------------------*" << endl;
  cout << "       Questions         Right or wrong       " << endl;
  cout << "----------------------------------------------" << endl;

  for (int i = 0; i < mathQuestions.size(); i++) {
    leftNum = mathQuestions.at(i).at(0);
    mathType = mathQuestions.at(i).at(1);
    rightNum = mathQuestions.at(i).at(2);
    userGuess = mathQuestions.at(i).at(3);
    correctAwns = mathQuestions.at(i).at(4);
    // pulling information from 2D vector
    switch (mathType) { // switch used to redisplay previous questions
    case 0:
      mathOp = '+';
      correctAwns = leftNum + rightNum;
      break;
    case 1:
      mathOp = '-';
      correctAwns = leftNum - rightNum;
      break;
    case 2:
      mathOp = '*';
      correctAwns = leftNum * rightNum;
      break;
    case 3:
      mathOp = '/';
      correctAwns = leftNum / rightNum; // divide logic is no longer different
      break;
    }

    cout << "     " << setw(2) << leftNum << left << ' ' << mathOp << ' '
         << rightNum << " = " << setw(3) << left << correctAwns
         << "           ";
    // displays previous questions in line with '='
    if (userGuess ==
        correctAwns) // displays correct if the user got the awnser right,
                     // incorrect if the user got the question wrong
      cout << "Correct" << endl;
    else
      cout << "Incorrect" << endl;
  }
  cout << "*--------------------------------------------*" << endl;
  cout << "                    Summary                   " << endl;
  cout << "*--------------------------------------------*" << endl;
  cout << "Amount Correct: " << totalCorrect << endl;
  cout << "Amount Incorrect: " << totalQuestions - totalCorrect << endl;
  cout << endl;
  cout << "Thanks for playing, " << userName << "! See you next time! ^.^"
       << endl;
  cout << "*--------------------------------------------*" << endl;
  return 0;
}
