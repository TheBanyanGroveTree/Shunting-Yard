#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

// Constructor
Node::Node(int value) {
  this->value = value;
  left = nullptr;
  right = nullptr;
  next = nullptr;
}

// Get value
int Node::getValue() {
  return value;
}

// Set left Node ptr
void Node::setLeft(Node* left) {
  this->left = left;
}

// Get left Node ptr
Node* Node::getLeft() {
  return left;
}

// Set right Node ptr
void Node::setRight(Node* right) {
  this->right = right;
}

// Get right Node ptr
Node* Node::getRight() {
  return right;
}

// Set next Node ptr
void Node::setNext(Node* next) {
  this->next = next;
}

// Get next Node ptr
Node* Node::getNext() {
  return next;
}

// Destructor
Node::~Node() {
  next = nullptr;
}
