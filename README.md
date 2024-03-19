# CS260_Final_Project
Eduarda Reolon - Graph

Description: This program implements a graph class with at least:

 - a function to add a new vertex to the graph (perhaps add_vertex(vertex_name)),
 - a function to add a new edge between two vertices of the graph (perhaps add_edge(source, destination) or source.add_edge(destination)),
 - a function for a shortest path algorithm (perhaps shortest_path(source, destination)),
 - a function for a minimum spanning tree algorithm (example min_span_tree()).

---------------------------------------------------------------------------------------------------

Design: 

The first step of designing this program is to understand what is a graph. In computer science a graph is an abstract data type and, according to Layman's definition, a graph is a network that defines the relationship between components in our system. See below:

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/2bce32be-74fc-4d6e-acad-01996b893042)

Figure 1

The circles are refered to vertex(singular)/vertices(plural) or nodes and they are the components that form the graph.

The arrows define the relationship betweent the components and are referred to as edges.

Mathematically speaking, a graph G = (V,E) is a set of vertices V and edges E where each edge (u,v) is a connection between vertices.

Other important definitions:

- Neighbor: two vertices are neighbors if an edge (u,v) connected them. For example, we can see in Figure 1 that 13 and 25 are neighbors. Another example is that all neighbors of 4 are 3 and 2.

- Degree: is the number of edges connected to a vertex. For example, from Figure 1 we can see that the degree of 4 is 2, because it has 2 neighbors.

- Path: is the sequence of vertices connected by edges you have to take to leave an origin and get to a destinition. For example, in Figure 1, one path from 1 to 9 is 1->5->3->9.

- Path lenght: number of edges in a path. On the previous example, the path had lenght 3.

- Cycle: a path that starts and ends at the same vertex. All cycles are paths, but not all paths are cycles.

---------------------------------------------------------------------------------------------------

Tests: (at least 2 per function)

---------------------------------------------------------------------------------------------------

Complexity Analyzis:

---------------------------------------------------------------------------------------------------

The parts of the code where I meet each one of the requirements are the following:
