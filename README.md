# Lab 43: Graph Edge List

This lab helps you get to know the graph ADT. It includes a graph class that implements the edge list structure as described in the textbook.

The class is a template so that the vertex and edge elements can be of any type. For example, for a graph with integer elements for the vertices and character elements for the edges, declare the graph as:

	Graph<int,char> graph;

## Exercises

Complete the following steps using the provided graph ADT:

1. Create a graph that is identical to the one in Figure 13.3 of the textbook.
2. Print "Vertices:" then print all vertex elements in the graph.
3. Print "Edges:" then print all edge elements in the graph.
4. Print "u vertices:" then print all vertices adjacent to `u`.
5. Print "w edges:" then print all edges incident on `w`.
6. Erase vertex `z`, print "w edges without z:", then print all edges incident on `w`.
