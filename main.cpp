// CS260 - Final Project - Graph - Eduarda (Duda) Reolon
// Description: implement a graph class with at least:
// - a function to add a new vertex to the graph;
// a function to add a new edge between two vertices of the graph;
// a function for a shortest path algorithm;
// a function for a minimum spanning tree algorithm.

// include files that are used during code
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

// unordered_map stores a hash table-based associative container that stores elements formed by the combination of a key and a mapped value
// I will use the features of this file to store the weight in between two vertices
#include <unordered_map>


// shortcuts
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
using std::pair;


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

// Class that will define what the Graph class and its functions are
class Graph{
public:
    // I will be storing all the vertices and the edges in the graph on two vectors
    vector<Vertex> vertices; // On later functions when I want to analyze the graph I will be able to iterate through the vertices in the vector
    vector<Edge> edges;    

    // how I will store the weight
    unordered_map<string, unordered_map<string, int>> neighbors_list; // vertex{neighbors, respective weights}
    // one string key which is the source vertex and two values, one is a string which are the neighbors/destination and the other is a list of all integer weights
    // for each vertex in the graph, we store a mapping of its neighbors to the weights of the edges connecting them

    
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

        neighbors_list[name] = {}; // add a slot in the neighbors_list for the new vertex

    }

    // Function to add a new weighted edge between two vertices of the graph
    void addEdge(Vertex* source, Vertex* destination, int weight){ //it takes in two vertices and the integer weight 

        // Create a new edge object
        Edge newEdge;
        newEdge.weight = weight;
        newEdge.destination = destination; // No need for & since destination and source are already pointers
        newEdge.source = source; // No need for & since destination and source are already pointers

        // Insert the new edge at the end of the edges storage vector
        edges.push_back(newEdge);

        // Need to add the destination vertex as one of the neighbors of the source vertex
        source->neighbors.push_back(destination); // Use -> to access members of pointers
        destination->neighbors.push_back(source); // Use -> to access members of pointers

        // Assuming undirected graph, update adjacency list
        neighbors_list[source->name][destination->name] = weight;
        neighbors_list[destination->name][source->name] = weight;
    }

    // this function finds the shortest path between the input source and the input destination
    vector<string> shortest_path(const string& source, const string& destination) {

        // creates two new unordered maps, one that stores if a node has been visited and the other stores the parent of the node
        unordered_map<string, bool> visited;
        unordered_map<string, string> parent;

        visited[source] = true; // marks the input source as true to already being visited
        parent[source] = ""; // we don't have a parents to the input source so set it as empty

        // we will need to iterate through the entire graph and only stop the iteration when the graph is over the destination is found
        // boolean will be turned to true when destination is found which indicates we can break out of the iteration
        bool destination_found = false; 

        // a vector that contains strings called level is being initialized with the source vertex as its only element
        // this is necessary because we are doing a breadth-first search (BFS)
        // In BFS, we explore the graph level by level, starting from the source vertex and moving outward to its neighbors, then to their neighbors, and so on
        vector<string> level = {source};

        // In the BFS type of search it will explore all the vertices until it finds the destination as you can see on the while loop below
        // Just the while loop does not find the shortest path
        // iteration will have until we have found the destination or the level is empty which means it is the end of the graph
        while (!destination_found && !level.empty()) {

            // initialize another vector to store the next level
            vector<string> next_level;
            
            // iterates i through all levels in the level vector 
            // auto& just sets the variable current_level to whatever data structure it needs to be automatically
            for (auto& current_level : level) {

                // iterated through all neighbors in the neighbor list of the current level we are looking at
                for (auto& neighbor : neighbors_list[current_level]) {

                    // neighbors_list elements have two information, the name of the neighbor and the weight on the edge between the neighbor and the source
                    // by saying neighbor.first we want to extract the name of the current neighbor element we are looking at, if it was .second we would take the weight of it
                    const string& neighbor_name = neighbor.first; // Extract neighbor vertex name

                    // check if the neighbor vertex was already visited 
                    if (!visited[neighbor_name]) {
                        // if not, then visit it, and set it as visited
                        visited[neighbor_name] = true;
                        // store the level we are at as the parent of the vertex we are visiting
                        // this will be important when we have to deconstruct the path and go back on what we have done
                        parent[neighbor_name] = current_level;

                        // then the current vertex we are looking at gets in the list to be the next level we will analyze
                        next_level.push_back(neighbor_name);

                        // check if what we are visiting is the destination
                        if (neighbor_name == destination) {
                            destination_found = true; // if it is then break out of for loop
                            break;
                        }
                    }
                }

                // If the destination is found, break out of the outer loop as well
                if (destination_found==true) {
                    break;
                }
            }

             // Move to the next level of traversal by assigning the contents of next_level to level which will repeat the entire while loop again
            level = move(next_level);
        }

        // On BFS this is the part that will define the shortest path, by putting all the parents together
        // In this situation the destination vertex might have more than one parent, but our code only has the information of the parent that will lead to the shortest path

        // reconstruct the path from the destination vertex back to the source vertex using the parent information stored during the graph traversal
        vector<string> path; // create a vector called path whose elements are strings
        string current = destination; // start from the destination
        while (current != "") { // and continue to move up on the graph until reach an empty slot
                                // we defined "" (empty) to be the parent of the source, so when we reach this parent means we have reached the source
            path.push_back(current);  // Add the current vertex to the path
            current = parent[current]; // Move to the parent vertex of the current vertex
        }

        // Currently our path vector is backwards so we need to reverse it
        vector<string> reversed_path(path.rbegin(), path.rend());

        // return the correct and reversed path
        return reversed_path;
    }

    string find_parent(unordered_map<string, string>& parent, const string& vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find_parent(parent, parent[vertex]);
        }
        return parent[vertex];
    }

    // This function attempts to apply the Kruskal's algorithm to find the minimum spanning tree
    // it takes no input but it will output a vector that each element is a pair of two strings
    // these two strings will represent a pair of connected vertices that are still present in the MST 
    vector<pair<string, string>> kruskal_min_span_tree() {

        // Initialize minimum spanning tree edges
        vector<pair<string, string>> min_span_tree_edges;


        // returns the result
        return min_span_tree_edges;
    }


};

int main() {
    Graph graph;

    // Add vertices
    graph.addVertex("A");
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    // Adding edges
    // can't just input a constant/string because my function only accepts Vertex inputs for the source and destination
    graph.addEdge(&graph.vertices[0], &graph.vertices[1], 5);
    graph.addEdge(&graph.vertices[0], &graph.vertices[2], 3);
    graph.addEdge(&graph.vertices[1], &graph.vertices[2], 2);
    graph.addEdge(&graph.vertices[1], &graph.vertices[2], 2);
    graph.addEdge(&graph.vertices[1], &graph.vertices[3], 4);
    graph.addEdge(&graph.vertices[2], &graph.vertices[3], 1);
    graph.addEdge(&graph.vertices[2], &graph.vertices[4], 6);
    graph.addEdge(&graph.vertices[3], &graph.vertices[4], 7);

    // Finding shortest path
    cout << "Shortest Path from A to E: ";
    vector<string> shortest_path = graph.shortest_path("A", "E");
    for (const auto& vertex : shortest_path) {
        cout << vertex << " ";
    }
    cout << endl;

    // test to add an edge for a vertex that does not exist
    // graph.addEdge(graph.vertices[1], graph.vertices[22], 3); // it gives bad_alloc error 

    // Finding minimum spanning tree using Kruskal's algorithm
    cout << "Minimum Spanning Tree: ";
    vector<pair<string, string>> min_span_tree = graph.kruskal_min_span_tree();
    for (const auto& edge : min_span_tree) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    return 0;
}