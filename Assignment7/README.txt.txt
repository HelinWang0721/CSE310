Assignment7 description:
	This assignment is to implement a graph data structure using an adjacency list and also to find a circuit (a sequence of edges starting from one node/vertex and ending to itself) using every edge of the graph.
	Also implement an adjacency list that is an array of linked lists. First, create a LinkedList struct/class whose each node containing an adjacency vertex, its weight, and also a variable “notUsed” that will be used in the later step of the assignment. insertEdge( ) function in the LinkedList in order to add each edge information and add them  in increasing order. If more than one edge between two nodes, and in that case, add them in the increasing order of their weights. 
	After creating the Linked List data structure, create Graph.h and create an adjacency list that is an array of linked lists in it. The size of the array is the number of nodes/vertices, and each slot should correspond to each vertex in their increasing order. Compute and record the degree (the number of out-going edges) for each vertex. After populating the adjacency list, and the printGraph( ) function to print out its content.
	Finally, compute its circuit (a sequence of edges to go through every edge of the graph, starting from one node/vertex and ending to itself). First, the Stack data structure by creating a struct/class of Edge containing two vertices and its weight and making an array of edges or a linked list of edges (either of them can represent a stack as long as we use LIFO, Last-In-First-Out order).  The push( ) function to push an edge and the pop( ) function to pop the last edge. Create two variables “circuit” and “tempStack” of this Stack data structure, initially being empty.
	Then DFS (Depth First Search) and DFS_VISIT in the Graph.h to compute its circuit. First, start the search from the vertex 1. The DFS and DFS_VISIT that we saw in class was calling DFS_VISIT for the vertices with white color, but here we call it for the vertices with white or gray color. The aim is to explore every edge that is incident with each vertex. Once explore an edge by visiting an adjacent vertex, mark the edge as “used” and push the edge onto the “tempStack”. Mark such edge as “used” in the adjacency list so that program not explore it again later on.  Each edge is stored twice in the adjacency list because it is an undirected edge. If a vertex does not have any more edge that is incident with it, then pop the last edge from the “tempStack”, say (u, v), then switch the order of its vertices to (v, u) and push/append it to the “circuit”. At this point, the search will need to back-track to the vertex u.

Assignment7.cpp:
Assignment7.cpp file (a driver program) needs to be created to process the information from the file named “graph.txt”. The file “graph.txt” will have some information on an undirected graph, and its first line has the format of:
n m

where n is the number of nodes/vertices and m is the number of edges in the graph. Then the nodes/vertices of this graph are named as 1, 2, … n.  A real example for this can be:

12 35

In this case, there will be 12 nodes/vertices and 35 edges. After this line, there will be m lines containing the information of edges in the format of:

s e w

where s and e are two nodes/vertices of the edge and w is the weight of the edge. Each node can have a weight. A real example for this can be:

1 2 5

In this case, there is an edge between the vertex 1 and the vertex 2, with its weight of 5.