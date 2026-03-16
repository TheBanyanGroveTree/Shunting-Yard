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
void push(Node*& head, char value); // STACK
char pop(Node*& head); // STACK
char peek(Node* head); // STACK
bool isEmpty(Node* head); // STACK
void enqueue(); // QUEUE
void dequeue(); // QUEUE

int main() {
  // Define stack head node
  Node* head = nullptr; // apparently nullptr is better than NULL T^T
  
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

// Insert new value at the head of the stack (LIFO)
void push(Node*& head, char value) {
  Node* newNode = new Node(value); // create new Node
  newNode->setNext(head); // set next ptr of new Node
  head = newNode; // set head to new Node
}

// Remove value from head of stack (LIFO)
char pop(Node*& head) {
  // check if stack is empty
  if (isEmpty(head)) {
    return '\0';
  }

  // update linked list
  Node* tempNode = head; // store value to delete ptr later
  char tempValue = head->getValue();
  head = head->getNext();
  delete tempNode; // delete OG ptr
  
  return tempValue;
}

// Return element at top of stack
char peek(Node* head) {
  // check if stack is empty
  if (isEmpty(head)) {
    return '\0';
  }

  return head->getValue();
}

// Check if stack is empty
bool isEmpty(Node* head) {
  if (head == nullptr) {
    return true;
  }

  return false;
}
