#include <iostream>
#include <iomanip>
#include <string>
#include <array>

#pragma once

using namespace std;
typedef struct SEW {
	int s;
	int e;
	int w;
}; //create a structure that store side edge and weight

typedef struct vertex_weight { //(To)
	int vertex;
	int weight; //structre store the vertex and weight

	bool used;
};


class LinkedList {

	class Node {
	public:
		vertex_weight vw;
		Node* next;
	}; //create a linkedlist class and node for store weight and next pointer

private:
	int size; //size of the linkedlist that connect with "FROM" node
	Node* firsthead; //the firstnode of "TO" node

public:
	LinkedList();
	~LinkedList();
	int getsize();
	void insertEdge(vertex_weight vw);
	vertex_weight get(int index);
	Node* getNode(int index); //defined all functions
};

typedef struct head { //(From)
	int vertex; //the head array contains all vertices that connected with
	int degree;
	int color;
	LinkedList vwList; 
};struct head* heads; //create the array for head struct

int lengthOfHeads = 0; //initialize the leangth of array

void createLinkList(int nodeNum, struct SEW* sews, int sewLength);

void addVertex(struct SEW sew);

void getfile(struct SEW** sews, int* sewLength, int* nodeNum);

LinkedList::LinkedList() {
	this->size = 0;
	this->firsthead = NULL; //initialize the constructor and destructor
}
LinkedList::~LinkedList() {
	Node* n = firsthead;
	for (size_t i = 0; i < this->size; i++)
	{
		Node* temp = n;
		n = n->next;
		delete temp;
	}
}

int LinkedList::getsize() {
	return size; //return size
}

void LinkedList::insertEdge(vertex_weight vw) {
	auto compare = [](Node* n1, Node* n2) -> bool { //compare vertex in the list, if incresing order return true else return false
		if (n2 == NULL) { return true; }
		auto a = n1->vw;
		auto b = n2->vw; //assign the vertiex weight to a and b
		
		if (a.vertex < b.vertex) return true;
		else if (a.vertex == b.vertex && a.weight < b.weight) return true;//if vertex have same number, then compare the weight ofthese 2 vertices, if incresing order return true else return false
		return false;
	};

	Node* newNode = new Node;
	newNode->vw = vw;
	newNode->next = NULL; //initialize a new node and store the vertex weight

	if (size == 0) {
		firsthead = newNode;
		size++;
		return; //add to the firsthead if linkedlist is empty
	}

	if (compare(newNode, firsthead)) {
		newNode->next = firsthead;
		firsthead = newNode; //add to the front of the head if newnode smaller than head
		size++;
		return;
	}

	Node* node = firsthead;
	for (int i = 1; i <= size; i++) {
		if (compare(newNode, node->next)) {
			auto temp = node->next;
			node->next = newNode;
			newNode->next = temp;
			break; 
		}
		node = node->next; //searching the linked list until found the first larger edge in the linked list and add it to the front of it
	}
	size++;
}

vertex_weight LinkedList::get(int index) { //get the node that allocated with index in the linked list
	Node* node = firsthead;//initialize the pointer 
	for (int i = 0;i < size;i++) {
		if (i == index) {
			return node->vw; //if found the node in linkedlist then return
		}
		node = node->next;
	}
	vertex_weight ret = {};
	return ret; //else return null
}

LinkedList::Node* LinkedList::getNode(int index) { //get the node that allocated with index in the linked list
	Node* node = firsthead;//initialize the pointer 
	for (int i = 0;i < size;i++) {
		if (i == index) {
			return node; //if found the node in linkedlist then return
		}
		node = node->next;
	}
	return node; //else return null
}