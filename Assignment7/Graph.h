#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "LinkedList.h"
#include "Stack.h"

using namespace std;

#define white 0
#define grey 1
#define black 2

Stack tempStack;
Stack circuit;

void DFS();
void DFS_VISIT(int i);
void printcircuit();
void printstack();

void printGraph() {

	cout << "The Graph contains:" << endl;
	cout << "-------------------" << endl;

	for (int i = 1;i < lengthOfHeads; i++) { 
		
		cout << "From: " << heads[i].vertex << " with its degree " << heads[i].degree << endl; //print the first "FROM" node in the array

		for (int j = 0; j < heads[i].vwList.getsize(); j++) { //print the vertex and edges weight that connected with the "FROM" node
			auto vw = heads[i].vwList.get(j);
			cout << "To: " << vw.vertex << " with weight " << vw.weight << endl;
		}

		cout << endl;
	}

}

void DFS() {
	cout << "Computing its circuit .....\n" << endl;
	for (int i = 1; i < lengthOfHeads; i++) {
		if (heads[i].color == white) {
			//tempStack.push(i);
			DFS_VISIT(heads[i].vertex);
		}
	}
	cout << "\nThe circuit is : " << endl;
	for (int i = 0; i < circuit.size; i++) {
		cout << "(" << circuit.dataarray[i].vertex1 << "," << circuit.dataarray[i].vertex2 << ")" << endl;
	}
}

void DFS_VISIT(int headindex) {

	auto markEdgeUsed = [](int from, int to, int weight) { // a lambda to find the edge and mark it as used
		for (size_t i = 0; i < heads[from].vwList.getsize(); i++)
		{
			auto tempVW = heads[from].vwList.get(i);
			if (tempVW.vertex == to && tempVW.weight == weight) { // go over each vertex connect to this vertex to find the edge
				heads[from].vwList.getNode(i)->vw.used = true; // mark the edge as used
				break;
			}
		}
	};

	auto isBlack = [](int vertex) -> bool { //  a lambda to check each edge is used for this vertex
		if (heads[vertex].color == black) {
			return true;
		}
		for (size_t i = 0; i < heads[vertex].vwList.getsize(); i++) // go over each vertex connect to this vertex
		{
			auto tempVW = heads[vertex].vwList.get(i);
			if (!tempVW.used) { // the edge not used
				return false; // some edge not used, so the vertex not black
			}
		}
		return true;
	};


	heads[headindex].color = grey; // change the color of the from vertex to grey
	for (int i = 0;i < heads[headindex].vwList.getsize();i++) {
		if (heads[headindex].vwList.get(i).used) // if the edge is used, go to next edge
			continue;

		int toVertex = heads[headindex].vwList.get(i).vertex;
		int weight = heads[headindex].vwList.get(i).weight;
		if (heads[toVertex].color == white || heads[toVertex].color == grey) { // if the edge is not black

			tempStack.push(Edge(heads[headindex].vertex, toVertex, weight)); // push the edge connect to the next vertex into the temp stack
			printcircuit();
			printstack(); // print out circuit and temp stack
			markEdgeUsed(headindex, toVertex, weight);
			markEdgeUsed(toVertex, headindex, weight); // mark both edge as used
			DFS_VISIT(toVertex); // move to next vertex

		}

		if (isBlack(toVertex)) {
			Edge popedEdge = tempStack.pop(); // pop out the last edge in the temp stack
			circuit.push(Edge(popedEdge.vertex2, popedEdge.vertex1, 0)); // push the edge and exchange its from and to vertex
			printcircuit();
			printstack();
		}
		
	}
	heads[headindex].vertex = black;
}

void printcircuit() {//print all vertices from the circuit 

	cout  << "Circuit: ";
	if (circuit.size <= 0) {
		cout << "Empty" << endl;
		return;
	}
	for (int i = 0; i < circuit.size; i++) {
		cout << "(" << circuit.dataarray[i].vertex1 << "," << circuit.dataarray[i].vertex2<< ") "; 
	}
	cout << endl;
}

void printstack() {//print all vertices from the stack 

	cout << "Stack:   ";
	if (tempStack.size == 0) {
		cout << "Empty" << endl;
		return;
	}
	for (int i = 0; i < tempStack.size; i++) {
		cout << "(" << tempStack.dataarray[i].vertex1 << "," << tempStack.dataarray[i].vertex2 << ") "; 
	}
	cout << endl << endl;
}

