// CS260 - Final Project - Graph - Eduarda (Duda) Reolon
// Description: implement a graph class with at least:
// - a function to add a new vertex to the graph;
// - a function to add a new edge between two vertices of the graph;
// - a function for a shortest path algorithm;
// - a function for a minimum spanning tree algorithm.
// to be able to get the last function working I had to use a lot of ChatGPTs help

// include files that are used during code
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

        // Assuming undirected graph, update neighbor list
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

                    // neighbors_list elements have 3 information, the name of the source, the name of the neighbor and the weight on the edge between the neighbor and the source
                    // by saying neighbor.first we want to extract the name of the current vertex we are looking at
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

    // Helper function to find the parent of a vertex
    string find_parent(unordered_map<string, string>& parent, const string& vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find_parent(parent, parent[vertex]);
        }
        return parent[vertex];
    }

    // This function attempts to apply the Kruskal's algorithm to find the minimum spanning tree
    // Kruskal's algorithm follows these steps:
    // 1- Sort all the edges in non-decreasing order of their weight. 
    // 2- Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If the cycle is not formed, include this edge. Else, discard it. 
    // 3- Repeat step#2 until there are (V-1) edges in the spanning tree.
    //
    // it takes no input but it will output a vector that each element is a pair of two strings
    // these two strings will represent a pair of connected vertices that are still present in the MST 
    vector<pair<string, string>> kruskal_min_span_tree() {

        // Initialize minimum spanning tree edges
        vector<pair<string, string>> min_span_tree_edges;

        // The same way as we did on the shortest_path function, we need to find a way to store the parent of the vertices we'll be iterating through
        unordered_map<string, string> parent;


        // In Kruskal's algorithm, we need to keep track of the parent of each vertex. Initially, each vertex is considered as its own parent.
        for (auto& vertex_pair : neighbors_list) { // for each vertex pair in the neighbor_list unsorted map
            const string& vertex = vertex_pair.first; // .first extracts the name of the source vertex
            parent[vertex] = vertex; //set it as its own parent
        }


        //  1- Sort all the edges in non-decreasing order of their weight. 
        
        //declare a vector to store edges with integer weights and pairs of strings representing source and destination vertices.
        vector<pair<int, pair<string, string>>> edges; // edge = (weight, {source, destination})

        for (auto& vertex_pair : neighbors_list) { // for each vertex pair in the neighbor_list unsorted map

            const string& source = vertex_pair.first; // each iteration the source will be updated to being the source of the following neighbor_list element

            for (auto& neighbor : vertex_pair.second) { // iterate through each neighbor in the neighbor list 
                const string& destination = neighbor.first;  // get their destination
                int weight = neighbor.second; // and their weight
                edges.push_back({weight, {source, destination}}); // add this new structure to the end of edges vector
            }
        }

        sort(edges.begin(), edges.end()); // sort the edges vector in ascending order based on the weight of the edges.


        // 2- Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If the cycle is not formed, include this edge. Else, discard it. 
        // 3- Repeat step#2 until there are (V-1) edges in the spanning tree.
        
        for (auto& edge : edges) { // Iterate through each edge in the sorted list of edges

            // Set the source and destination vertices from the edge to their respective variable
            const string& source = edge.second.first;
            const string& destination = edge.second.second;
            // do the same with the weight 
            int weight = edge.first;

            // Find the parent of the source and destination vertices
            string parent_source = find_parent(parent, source);
            string parent_destination = find_parent(parent, destination);

            // Check if adding this edge forms a cycle in the minimum spanning tree
            if (parent_source != parent_destination) {
                // If no cycle is formed, add the edge to the minimum spanning tree
                min_span_tree_edges.push_back({source, destination});
                // Union the sets of source and destination vertices by updating their parents
                parent[parent_destination] = parent_source;
            }
        }

        // returns the result
        return min_span_tree_edges;
    }


};

int main() {
    Graph graph;

    // TESTING SECTION - for addVertex
    // TEST 1
    // Verify if several components can be added to the graph
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    // ran smoothly with no error messages

    // TEST 2
    // Verify if several components can be added to the graph
    graph.addVertex("A");
    // correctly displayed the error message


    // TESTING SECTION - for addEdge
    // TEST 1
    // Try to add several edges
    // can't just input a constant/string because my function only accepts Vertex inputs for the source and destination
    graph.addEdge(&graph.vertices[0], &graph.vertices[1], 5); // (A,B,5)
    graph.addEdge(&graph.vertices[0], &graph.vertices[2], 3); // (A,C,3)
    graph.addEdge(&graph.vertices[1], &graph.vertices[2], 2); // (B,C,2)
    graph.addEdge(&graph.vertices[1], &graph.vertices[3], 4); // (B,D,4)
    graph.addEdge(&graph.vertices[2], &graph.vertices[3], 7); // (C,D,7)
    graph.addEdge(&graph.vertices[2], &graph.vertices[4], 6); // (C,E,6)
    graph.addEdge(&graph.vertices[3], &graph.vertices[4], 1); // (D,E,1)
    // ran smoothly with no error messages

    // TEST 2
    // add an edge for a vertex that does not exist
    // graph.addEdge(graph.vertices[1], graph.vertices[22], 3); 
    // it gives bad_alloc error and stops the program


    // TESTING SECTION - for shortest_path
    // TEST 1
    // Check if it successfully finds the shortest path between two vertices
    cout << "Shortest Path from A to E: ";
    vector<string> shortest_path = graph.shortest_path("A", "E");
    for (auto& vertex : shortest_path) {
        cout << vertex << " ";
    }
    cout << endl;
    // Displayed correct message "Shortest Path from A to E: A C E "

    // TEST 2 
    // Check what it does when two paths between the vertices are the same length
    // create another 2 edges path fro A to E
    graph.addVertex("F");    
    graph.addEdge(&graph.vertices[0], &graph.vertices[5], 1); // (A,F,1)
    graph.addEdge(&graph.vertices[5], &graph.vertices[4], 1); // (F,E,1)
    // call function again
    cout << "Shortest Path from A to E: ";
    vector<string> shortest_path1 = graph.shortest_path("A", "E");
    for (auto& vertex : shortest_path1) {
        cout << vertex << " ";
    }
    cout << endl;
    // Displayed correct message "Shortest Path from A to E: A F E "


    // Same test with other variables
    // A to D can be achieved by going through the path A B D or A C D in our graph
    cout << "Shortest Path from A to D: ";
    vector<string> shortest_path2 = graph.shortest_path("A", "D");
    for (auto& vertex : shortest_path2) {
        cout << vertex << " ";
    }
    cout << endl;
    // Displayed correct message "Shortest Path from A to D: A C D "

    // From the results we can say that when there are two paths of the same length from one vertex to the other, my program displays the path that has less weight 


    // TESTING SECTION - for MST
    // TEST 1
    // check if it successfully finds the MST of a graph
    cout << "Minimum Spanning Tree: ";
    vector<pair<string, string>> min_span_tree = graph.kruskal_min_span_tree();
    for (auto& edge : min_span_tree) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    // TEST 2
    // check what it does when there are two or more edges of the same weight and one of them needs to be removed 
    // create a new graph
    Graph graph2;
    graph2.addVertex("A"); 
    graph2.addVertex("B"); 
    graph2.addVertex("C");    
    graph2.addEdge(&graph2.vertices[0], &graph2.vertices[1], 1); // (A,B,1)
    graph2.addEdge(&graph2.vertices[1], &graph2.vertices[2], 5); // (B,C,5)   
    graph2.addEdge(&graph2.vertices[0], &graph2.vertices[2], 5); // (A,C,5)
    cout << "Minimum Spanning Tree: ";
    vector<pair<string, string>> min_span_tree2 = graph2.kruskal_min_span_tree();
    for (auto& edge : min_span_tree2) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;
    // it chooses to keep the edges that included the first added vertex (A)

    return 0;
}
