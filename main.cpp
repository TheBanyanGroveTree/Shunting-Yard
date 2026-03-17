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

int precedence(char c);
bool leftAssociativity(char c);
void algoPostfixOutput(Node* current, string& output);

void binaryExpressionTree(Node*& root, string postfix);
void pushTree(Node*& root, Node* subtree);
Node* popTree(Node*& root);
void treeInfixOutput(Node* current);
void treePrefixOutput(Node* current);
void treePostfixOutput(Node* current);


int main() {
  // Define stack head Node
  Node* head = nullptr; // apparently nullptr is better than NULL T^T

  // Define queue front and rear Nodes
  Node* front = nullptr;
  Node* rear = nullptr;

  // Define binary expression tree starting Node
  Node* root = nullptr;
  
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

	// Check char type and implement Shunting Yard algo
	if (isdigit(c)) {
	  enqueue(front, rear, c); // enqueue numbers
	  
	} else if (c == '(') {
	  push(head, c); // push LEFT parenthesis to stack
	  
	} else if (c == ')') {
	  while ((!isEmpty(head)) && (peek(head) != '(')) {
	    enqueue(front, rear, pop(head)); // enqueue all oper until matching parentheses
	  }
	  pop(head); // bye-bye '('
	  
	} else if (!isspace(c)){ // handle operators
	  // enqueue top of stack if higher precedence and left associated
	  while ((!isEmpty(head)) &&
		 (precedence(peek(head)) >= precedence(c)) &&
		 (leftAssociativity(c))) {
	    enqueue(front, rear, pop(head));
	  }
	  push(head, c); // otherwise push to stack
	}
      }

      // Enqueue remaining operators in stack
      while (!isEmpty(head)) {
	enqueue(front, rear, pop(head));
      }

      // Postfix output string
      string outputString = "";
      algoPostfixOutput(front, outputString);
      cout << "Postfix: " << outputString << endl;

      // Create binary expression tree
      binaryExpressionTree(root, outputString);
      
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
	treePostfixOutput(root);
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


// Calculate operator with highest precedence using PEMDAS rules
int precedence(char c) {
  if ((c == '+') || (c == '-')) {
    return 1;
  } else if ((c == '*') || (c == '/')) {
    return 2;
  } else if ((c == '^')) {
    return 3;
  } else {
    return -1;
  }
}


// Determine if a token is left or right associated
bool leftAssociativity(char c) {
  if ((c == '+') || (c == '-') || (c == '*') || (c == '/')) {
    return true;
  }
  return false;
}


// Recursively iterate through linked list
void algoPostfixOutput(Node* current, string& output) {
  // Base case: check if empty or reached last Node
  if (isEmpty(current)) {
    return;
  }

  // Append Node value to output string
  output += current->getValue();

  // Recursive call
  algoPostfixOutput(current->getNext(), output);
}


// Build tree using postfix esspresion
void binaryExpressionTree(Node*& root, string postfix) {
  for (char c : postfix) {
    if (isdigit(c)) { // number
      push(root, c); // create new node and push onto stack
    } else { // operator
      // pop two nodes from track to form subtrees
      char op2 = peek(root);
      pop(root);
      char op1 = peek(root);
      pop(root);

      // create new Nodes and linked popped Nodes as children
      Node* opNode = new Node(c);
      Node* op1Node = new Node(op1);
      opNode->setLeft(op1Node);
      Node* op2Node = new Node(op2);
      opNode->setRight(op2Node);

      pushTree(root, opNode); // push subtree onto stack
    }
  }
}


// Push existing Node to binary expression tree stack
void pushTree(Node*& root, Node* subtree) {
  subtree->setNext(root);
  root = subtree;
}


// Pop Node from stack
Node* popTree(Node*& root) {
  // check if stack is empty
  if (isEmpty(root)) {
    cout << "Stack UNDERflow, NOT overflow." << endl;
    return nullptr;
  }

  Node* tempNode = root;
  root = root->getNext(); // shift
  tempNode->setNext(nullptr); // detach from stack
  return tempNode;
}


/**
// Construct infix expr
void treeInfixOutput(Node* current);

// Construct prefix expr
void treePrefixOutput(Node* current);
*/


// Perform postorder traversal of tree to construct postfix expr
void treePostfixOutput(Node* current) {
  // Base case: check if tree is empty or reached root Node
  if (isEmpty(current)) {
    cout << endl;
    return;
  }

  treePostfixOutput(current->getLeft()); // traverse left subtree

  treePostfixOutput(current->getRight()); // traverse right subtree

  cout << current->getValue(); // print value
}
