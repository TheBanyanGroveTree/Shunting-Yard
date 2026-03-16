#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
 public:
  Node(char);
  char getValue();
  void setLeft(Node*);
  Node* getLeft();
  void setRight(Node*);
  Node* getRight();
  void setNext(Node*);
  Node* getNext();
  ~Node();
 private:
  char value;
  Node* left;
  Node* right;
  Node* next;
};

#endif
