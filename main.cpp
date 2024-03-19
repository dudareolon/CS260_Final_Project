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
    vector<Vertex*> neighbors;
    
};

// Struct to represent each edge in the graph
struct Edge {
    // each edge will have a source and a destination vertex as well as a weight 
    Vertex* source;
    Vertex* destination;
    int weight;
};

class Graph{

};

int main() {
    Graph graph;

    return 0;
}