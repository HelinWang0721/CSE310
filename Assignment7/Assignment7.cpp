#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <array>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "Graph.h"

using namespace std;
int main(){
	struct SEW* SEWs;
	int sewLength = 0;
	int nodeNum;
	getfile(&SEWs, &sewLength,&nodeNum);
	createLinkList(nodeNum, SEWs, sewLength);
	printGraph();
	DFS();
	return 0;
}

#define MAX_FILE_LENGTH 1000//marco value of file length

void getfile(SEW** sews, int* sewLength, int* nodeNum) {
	int nodes,edges,s,e,w;
	std::ifstream file1("graph.txt");
	
	file1 >> nodes >> edges; //fetch out the node and edges
	struct SEW newsew; //create a struecture ready to store S E W 

	struct SEW sewBuffer[MAX_FILE_LENGTH]; //initialize the structure for buffer
	int sewBufferLength = 0;//initialize the buffer length

	while (file1 >> newsew.s >> newsew.e >> newsew.w) {
		sewBuffer[sewBufferLength] = newsew;
		sewBufferLength++;
	}//open file and store the nunber of nodes and eges into the vector SEW, nodes and egdes
	file1.close();

	SEW* SEWs = new SEW[sewBufferLength]; //make the linkedlist and write all S E W from buffer into it
	for (int i = 0; i < sewBufferLength; i++) {
		SEWs[i] = sewBuffer[i]; 
	}

	*sews = SEWs; //assign the value to the allocated memory address
	*nodeNum = nodes;
	*sewLength = sewBufferLength;
}

void createLinkList(int nodeNum, SEW* SEWs, int sewLength) {
	heads = new head[nodeNum + 1];
	lengthOfHeads = nodeNum + 1;

	for (size_t i = 0; i <= nodeNum; i++)
	{
		heads[i].vertex = i; //initialize the linked list of each header of vertex
		heads[i].degree = 0;
		heads[i].color = white;
	}
	for (size_t i = 0; i < sewLength; i++) {
		addVertex(SEWs[i]); //add the vertices into each linked list 
	}
	delete[] SEWs;
}

void addVertex(struct SEW sew) {
	int s = sew.s;
	int e = sew.e;
	int w = sew.w; //initialize the vertices and weight

	auto addNode = [](head &h, int s, int w) -> void {
		vertex_weight newVW; //create a structure and store the vertex and it's weight between 2 nodes
		newVW.vertex = s;
		newVW.weight = w;
		newVW.used = false;
		h.vwList.insertEdge(newVW); // add to the end of the list
	};

	addNode(heads[s], e, w);
	addNode(heads[e], s, w); // add the vertex for both direction 
	heads[s].degree++;
	heads[e].degree++; //add the number of degree of "FROM" node
}

