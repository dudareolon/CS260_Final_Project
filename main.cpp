#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Struct to represent each vertex/node in the graph
struct Vertex {
    // each vertex will store a name and a vector that contains the address of their neighboring vertices
    string name;
    vector<Vertex> neighbors;
    
};

// Struct to represent each edge in the graph
struct Edge {
    // each edge will have a source and a destination vertex as well as a weight 
    Vertex* source;
    Vertex* destination;
    int weight;
};

// Class that will define what the Graph class and its functions are
class Graph{
public:
    // I will be storing all the vertices and the edges in the graph on two vectors
    vector<Vertex> vertices; // On later functions when I want to analyze the graph I will be able to iterate through the vectors
    vector<Edge> edges;      

    // This function adds a vertex to the graph, but does not connect it yet
    void addVertex(string name) {
        
        // check if the vertex is already a part of the graph
        // initializes a loop variable iteration of type Vertex, which will iterate over each element in the vertices vector
        for (const Vertex& iteration : vertices) {
            if (iteration.name == name) { // if iteration name is equal to name trying to be input, then display error message
            cout << "Vertex " << name << " is already in the graph" << endl; // error message
            return; // exits the function without adding the newVertex
    }
}

        // Create a new Vertex object
        Vertex newVertex;
        newVertex.name = name;

        // Insert the new vertex at the end of the vertices storage vector
        vertices.insert(vertices.end(), newVertex);
    }

    // Function to add a new weighted edge between two vertices of the graph
    void addEdge(Vertex source, Vertex destination, int weight){ //it takes in two vertices and the integer weight 

        // Create a new edge object
        Edge newEdge;
        newEdge.weight = weight;
        newEdge.destination = &destination; // & takes the address of the variable after it
        newEdge.source = &source; // assign the address to the destination and source pointers

        // Insert the new edge at the end of the edges storage vector
        edges.insert(edges.end(), newEdge);

        // need to add the destination vertex as one of the neighbors of the source vertex
        source.neighbors.insert(source.neighbors.end(), destination);
    }
};

int main() {
    Graph graph;

    // Add vertices
    graph.addVertex("A");
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");


    // Adding edges
    // can't just input a constant/string because my function only accepts Vertex inputs for the source and destination
    graph.addEdge(graph.vertices[0], graph.vertices[1], 5);
    graph.addEdge(graph.vertices[1], graph.vertices[2], 3);


    return 0;
}