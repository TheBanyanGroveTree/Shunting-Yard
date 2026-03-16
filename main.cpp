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

char peek(Node* head); // STACK & QUEUE
bool isEmpty(Node* head); // STACK & QUEUE

void enqueue(Node*& front, Node*& rear, char value); // QUEUE
char dequeue(Node*& front, Node*& rear); // QUEUE


int main() {
  // Define stack head Node
  Node* head = nullptr; // apparently nullptr is better than NULL T^T

  // Define queue front and rear Nodes
  Node* front = nullptr;
  Node* head = nullptr;
  
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
    cout << "Stack UNDERflow, NOT overflow." << endl;
    return '\0';
  }

  // update linked list
  Node* tempNode = head; // store value to delete ptr later
  char tempValue = head->getValue();
  head = head->getNext();

  delete tempNode; // delete OG ptr
  return tempValue;
}


// Return element at top of DS
char peek(Node* head) {
  // check if DS is empty
  if (isEmpty(head)) {
    cout << "Either the stack has yet to be stacked || "
	 << "or you need to add some songs to your queue." << endl;
    return '\0';
  }

  return head->getValue();
}


// Check if stack OR queue is empty (same for both DS)
bool isEmpty(Node* head) {
  return (head == nullptr);
}


// Insert new value at the rear of the queue (FIFO)
void enqueue(Node*& front, Node*& rear, char value) {
  Node* newNode = new Node(value); // create new Node

  // check if queue is empty
  if (isEmpty(front)) {
    front = rear = newNode;
  }
  // update rear of queue
  else {
    rear->setNext(newNode);
    rear = newNode;
  }
}


// Remove value from the front of the queue (FIFO)
char dequeue(Node*& front, Node*& rear) {
  // check if queue is empty 
  if (isEmpty(front)) {
    cout << "Queue underflow, unlike the atmosphere these days" << endl;
    return '\0';
  }

  // store front Node and update front of queue
  Node* tempNode = front;
  char tempValue = front->getValue();
  front = front->getNext();

  // empty queue case
  if (front == nullptr) {
    rear = nullptr;
  }

  delete tempNode;
  return tempValue;
}
