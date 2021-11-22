#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <array>

#define datasize 1024

class Edge {
public:
	int vertex1;
	int vertex2;
	int weight;

	Edge(int v1, int v2, int w) {
		vertex1 = v1;
		vertex2 = v2;
		weight = w;
	}
	Edge(){}
};

class Stack {
public:
	Edge dataarray[datasize];
	int size = 0;
	Edge pop();
	void push(Edge index);
};

Edge Stack::pop() {
	if (size != 0) {
		Edge ret = dataarray[size - 1];
		dataarray[size - 1] = Edge();
		size--;
		return ret;
	}
	return Edge();
}

void Stack::push(Edge vertex){
	dataarray[size] = vertex;
	size++;
}