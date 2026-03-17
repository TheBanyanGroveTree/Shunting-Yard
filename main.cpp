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
void stringUpper(string& input);

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

void quit(Node* head);


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

    stringUpper(userCommand); // convert input to uppercase for comparison

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

      stringUpper(outputType); // convert input to uppercase for comparison

      // Validate input and print appropriate output type
      if (outputType == INFIX) {
	treeInfixOutput(root);
	cout << endl;
      } else if (outputType == PREFIX) {
	treePrefixOutput(root);
	cout << endl;
      } else if (outputType == POSTFIX) {
	treePostfixOutput(root);
	cout << endl;
      } else {
	cout << "Please input INFIX, PREFIX, or POSTFIX." << endl;
      }
      
    } else if (userCommand == QUIT) {
      quit(head); // delete stack
      quit(front); // delete queue
      quit(root); // delete root
      
      newInput = false;
      
    } else {
      cout << "Please input INPUT, OUTPUT, or QUIT." << endl;
    }
  }

  return 10;
}


// Convert string to uppercase
void stringUpper(string& input) {
  for (int i = 0; i < input.size(); i++) {
      input[i] = toupper(input[i]);
    }
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
  // base case: check if empty or reached last Node
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
      Node* newNode = new Node(c);
      pushTree(root, newNode); // create new node and push onto stack
    } else { // operator
      // pop Nodes to form subtrees
      Node* right = popTree(root); // right FIRST
      Node* left = popTree(root);

      // connect tree Nodes
      Node* opNode = new Node(c);
      opNode->setLeft(left);
      opNode->setRight(right);

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


// Perform in-order traversal of tree to construct infix expr
// Left subtree, then root node, and finally right subtree
void treeInfixOutput(Node* current) {
  // base case: check if tree is empty or reached root Node
  if (isEmpty(current)) {
    return;
  }

  // add left parenthesis
  if (!isdigit(current->getValue())) {
    cout << "(";
  }
  
  treeInfixOutput(current->getLeft()); // traverse left subtree
  
  cout << current->getValue(); // print value
  
  treeInfixOutput(current->getRight()); // traverse right subtree

  // add right parenthesis
  if (!isdigit(current->getValue())) {
    cout << ")";
  }
}


// Perform pre-order traversal of tree to construct prefix expr
// Root node, then left subtree, and finally right subtree
void treePrefixOutput(Node* current) {
  // base case: check if tree is empty or reached root Node
  if (isEmpty(current)) {
    return;
  }

  cout << current->getValue(); // print value

  treePrefixOutput(current->getLeft()); // traverse left subtree

  treePrefixOutput(current->getRight()); // traverse right subtree
}


// Perform post-order traversal of tree to construct postfix expr
// Left subtree, then right subtree, and finally root
void treePostfixOutput(Node* current) {
  // base case: check if tree is empty or reached root Node
  if (isEmpty(current)) {
    return;
  }

  treePostfixOutput(current->getLeft()); // traverse left subtree

  treePostfixOutput(current->getRight()); // traverse right subtree

  cout << current->getValue(); // print value
}


// Delete dynamically allocated memory
void quit(Node* head) {
  // base case: empty
  if (isEmpty(head)) {
    return;
  }

  // recursive call
  quit(head->getNext());
  delete head; // delete current head
}
