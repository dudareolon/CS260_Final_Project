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

- Edge Weight: this is a characteristic of the edges, normally described with numbers, that classifies the edges on how efficient they are. The efficiency weight can be define the money spent, power consumed, time wasted, or etc. 

A requirement of this program is also to have a function that uses a minimum spanning tree (MST) algorithm. Before designing the program it is important to understand what a MST is.

According to Layman's definition, an MST is a redefinition of a graph with all its vertices but one edge less, being that it has the minimum possible weight among the edges, in other words, the heaviest edge is removed. MSTs are important in order to create a more efficient program. Here is an MST visual example:

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/e5a8a28a-e1b1-4e1c-9793-57adc257bdd1)

Figure 2

The properties of a Spanning Tree are:
 - There are the same number of vertices in the graph and in the spanning tree
 - There are an amount of vertices-1 edges
 - The tree should be connected
 - The spanning tree should be acyclic, which means you should not be able to find a cycle in the tree


Now for the actual design of my program, I will have:

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/4b9ed2e3-b59a-4064-8d1b-6e0f50658142)

Figure 3

---------------------------------------------------------------------------------------------------

Tests: (at least 2 per function)

In order to be able to run these tests I will need to code another function that will display the graph so I can verify the status of my graph after each operation 
Before I start coding, I konw I my program will have to pass the following tests:

*for add_vertex*
- Verify if several components can be added to the graph

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/51699bd8-478e-4850-90f7-6dd34b3cbe61)

  This is the current program status:

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/2354d06f-d59e-4369-8cc8-b4d984b81732)


- Try to add a component that is already in the graph

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/af3ab774-d819-4539-814c-496cae9892e0)

  Displayed: "Vertex A is already in the graph"


*for add_edge*
- Try to add several edges

 ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/c9f7d2e1-9b79-4f98-851d-66089d45c69c)

 Now, this is the status of the program:
 
 ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/10cc33ba-2d3e-405c-a6bd-41d67c21f235)

  
- add an edge for a vertex that does not exist

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/a59e5949-eb19-44dc-baf1-7d67b35a3f1e)


*for shortest_path*
- Check if it successfuly finds the shortest path between two vertices
 
![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/67e7d64e-8f33-4e40-8286-2e59f3eb9aab)

 Displayed correct message "Shortest Path from A to E: A C E "

 The shortest path from A to E is highlighted on the picture below:

 ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/c699b03f-556c-48ec-a640-21b969160dc9)



- Check what it does when two paths between the vertices are the same length 

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/3b3fa35b-8237-477c-a319-1e3c837ce53e)

The shortest path from A to E is highlighted on the picture below:

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/339d190a-718a-415c-88e0-cbdd7f0b257f)

 Displayed correct message "Shortest Path from A to E: A F E "

 From what it seems the program chooses the path with less weight if there is a length conflict. But let's test it again to make sure. 

![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/92331b2b-059e-47f4-a867-452197525606)

 Displayed correct message "Shortest Path from A to D: A C D "

The two possibilities of shortest path from A to D are displayed below:

 ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/1e2252da-32de-42c0-a555-a9eb67407ea7)

 Both the green and the yellow path have a length of 2 edges to get from A to D. The yellow path has a weight of 10, while the green path has a weight of 9. From our previous theory, we thought when two lenghts were the same that the program would choose the path with less weight to display. I am glad I retested this situation, because my previous theory was wrong, the program displayed the path with more weight, the yellow (A C D). 

*for MST*
- check if it successfuly finds the MST of a graph

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/26c65a2d-3ab6-4444-9b78-d79fab1ced20)

  Displayed correct message "Minimum Spanning Tree: (A, F) (D, E) (E, F) (B, C) (A, C)"

  As we can see from the figure below, the displayed result is correct:

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/ee708c1b-4d43-4b6e-ab41-aff2fbfa4ea7)

  This MST shows the version of the graph where all vertices are still acceptable, in a way that the weight is minimum while not having any cycles on its structure.

  
- check what it does when there are two or more edges of the same weight and one of them needs to be removed 

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/0191b048-b587-443f-8fc9-e2fc67cfd363)

  Displayed correct message "Minimum Spanning Tree: (A, B) (A, C)". You can see the visual representation of this program on the picture below:

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/02bab7e4-e589-4ad1-a235-490074d4dd66)
  
  it chooses to keep the edges that included the first added vertex (A)

---------------------------------------------------------------------------------------------------

Complexity Analyzis:

---------------------------------------------------------------------------------------------------

The parts of the code where I meet each one of the requirements are the following:

- a function to add a new vertex to the graph:
  
  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/eaed3191-b974-4723-9dcf-8dad4a969334)


- a function to add a new edge between two vertices of the graph:

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/9e0a3c75-2c9a-461a-886f-49bc0148eef2)

  
- a function for a shortest path algorithm:

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/153ee4d9-62cf-49fc-bb28-d7e696d2e505)

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/b9ea6cab-c42b-49f5-bd14-5b54d4c6895c)

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/0dbeaaba-7bbd-4ee1-a0c6-61b3030f9431)


  
- a function for a minimum spanning tree algorithm:

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/bff79a47-6e50-481a-902a-690cf79f77e1)

  ![image](https://github.com/dudareolon/CS260_Final_Project/assets/102680672/0687785d-1640-40f1-86a8-ea118632358a)


