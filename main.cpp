/**
   Description: Shunting Yard algorithm implementation
   Author: Aahana Sapra
   Date: 03/15/2026
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Node.h"

using namespace std;

// Define function protoypes
void push(); // STACK
void pop(); // STACK
void peek(); // STACK
void enqueue(); // QUEUE
void dequeue(); // QUEUE

int main() {
  // Define const var for input comparison
  const string INPUT = "INPUT";
  const string OUTPUT = "OUTPUT";
  const string INFIX = "INFIX";
  const string PREFIX = "PREFIX";
  const string POSTFIX = "POSTFIX";
  const string QUIT = "QUIT";

  string userCommand = ""; // Declare str for user input

  // Continue prompting user for input until QUIT command
  bool newInput = true;
  while (newInput) {
    // read in user input
    cout << "Enter a command (INPUT, OUTPUT, QUIT): ";
    getline(cin, userCommand);

    // convert input to uppercase for comparison
    for (int i = 0; i < userCommand.size(); i++) {
      userCommand[i] = toupper(userCommand[i]);
    }
    
    // Validate input and call appropriate method or exit program
    if (userCommand == INPUT) {
      // read in infix expression
      string infix = "";
      cout << "Enter infix expression: ";
      getline(cin, infix);

      // Parse one by one
      for (int i = 0; i < infix.size(); i++) {
	char c = infix[i];

	// check char type
	if (isdigit(c)) {
	  
	} else if (isOperator(c)) {

	} else if (c == '(') {

	} else if (c == ')') {

	}
      }
      
    } else if (userCommand == OUTPUT) {
      // prompt user for type of output
      string outputType = "";
      cout << "Enter output type (INFIX, PREFIX, POSTFIX): ";
      getline(cin, outputType);

      // TO-DO: define function for uppercase conversion
      // convert input to uppercase for comparison
      for (int i = 0; i < userCommand.size(); i++) {
	userCommand[i] = toupper(userCommand[i]);
      }

      // Validate input and print appropriate output type
      if (outputType == INFIX) {

      } else if (outputType == PREFIX) {

      } else if (outputType == POSTFIX) {

      } else {
	cout << "Please input INFIX, PREFIX, or POSTFIX." << endl;
      }
      
    } else if (userCommand == QUIT) {

    } else {
      cout << "Please input INPUT, OUTPUT, or QUIT." << endl;
    }
  }

  return 10;
}
