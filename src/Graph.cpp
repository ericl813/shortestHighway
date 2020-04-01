#include "Graph.hpp"
#include "node.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <queue>
#include <limits.h>
#include <cstdint>

using namespace std;

typedef pair <Node *, Node *> nPair;



Graph::Graph(void)
    : nodes(0) {
    }

Graph::~Graph(void) {

    for (pair<int, Node *> elt : nodes) {
        delete elt.second;
    }

    for (pair<string, Node *> elt : cityNodes) {
        delete elt.second;
    }
  
}

/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */

 
/* Read in relationships from an inputfile to create a graph */

bool Graph::loadFromFile(const char* in_filename) {
    ifstream infile(in_filename);

    while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }
    
    int idx1 = stoi(record[0]);
    int idx2 = stoi(record[1]);

    if( nodes.find( idx1 ) == nodes.end() ) {
        // if the value is not found in the graph, then make a new node and insert
        Node * n1 = new Node( idx1 );
        nodes.insert( {n1->id, n1} );
    }

    if( nodes.find( idx2 ) == nodes.end() ) {
        // if the value is not found in the graph, then make a new node and insert
        Node * n2 = new Node( idx2 );
        nodes.insert( {n2->id, n2} );
    }

    // add the other node as an edge by accessing its adjancency list
    auto it = nodes.find( idx1 );
    Node * node1 = (*it).second;
    node1->adj.push_back( idx2 );

    it = nodes.find( idx2 );
    Node * node2 = (*it).second;
    node2->adj.push_back( idx1 );

      
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

bool Graph::loadCities(const char* cities_filename, const char* matrix_filename) {

    ifstream infile(cities_filename);
    ifstream distInfile(matrix_filename);

    int idx = 0;

    // loop to get the lines of data
    while (infile) {
        string city;
        // get the city names
        if (!getline(infile, city)) {
            break;
        }
    

        Node * n1 = new Node(city);
        n1->index = idx;
        idx++;
        
        // push to city nodes and corresponding indices
        cityNodes.insert( {city, n1} );
        
        cityNames.push_back( city );
        

        // get the distance matrix data
        string s;
        if (!getline(distInfile, s)){
            break;
        }

        istringstream ss(s);
        // loop through the distances and push to a vector of all the edges
        while (ss) {
        
            int distance;
            ss >> distance;
            if(!ss) {
                break;
            }

            n1->distances.push_back(distance);
        }

        
    }
    
    return true;
}




/* Implement pathfinder*/
bool Graph::pathfinder(Node* from, Node* to) {
    // initialize the queue
    queue<Node*> q;

    // set all node dist and prev to infinity/null
    for( pair<int, Node *> elt : nodes ) {
        elt.second->dist = INT_MAX;
        elt.second->prev = nullptr;
    }

    // add from to queue and set distance to zero
    q.push( from );
    from->dist = 0;

    // loop using a BFS search
    while( !q.empty() ) {
        Node * curr = q.front();
        q.pop();

        // for each of its negihbors
        for( int i : curr->adj ) {
            // if n.dist is infinity
            Node * n = getNode(i);
            if( n->dist == INT_MAX ) {
                n->dist = curr->dist + 1;
                n->prev = curr;
                q.push( n );
            }
        }
    }

    // returns false if no path found, otherwise true
    if( to->dist == INT_MAX ) {
        return false;
    } else {
        return true;
    }
}

/* Implement social gathering*/
void Graph::socialgathering(vector<int>& invitees, const int& k) {
    // number of mutual friends
    // proority queue for vertices 
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, NodePtrComp> degrees;
       
    // add nodes to priority queue based on degree
    for (pair<int, Node *> elt : nodes) {
        elt.second->degree = elt.second->adj.size();
 
        degrees.push( {elt.second->degree, elt.second} );
    }

    // pair< int id, int core >
    vector<pair<int, int>> cores;

    // loop through the priority queue and update cores
    while (!degrees.empty()) {
        Node * curr = degrees.top().second;

        degrees.pop();
        if (!curr->done) {
            cores.push_back( {curr->id, curr->degree} );

            //go through all neighbors of curr
            for (int j : curr->adj) {
                Node * neighbor = getNode(j);
                if (neighbor->degree > curr->degree) {
                    neighbor->degree -= 1;
                    degrees.push({neighbor->degree, neighbor});
                }
            }
            curr->done = true;
        }
    }

    // for all cores >= k, the corresponding id goes to invite list
    for (unsigned int i = 0; i < cores.size(); i++) {
        if (cores[i].second >= k) {
            invitees.push_back(cores[i].first);
        }
    }
    
}

void Graph::kruskals( vector<Edge>& results ) {

    // priority queue for vertices 
    priority_queue<pair<int, nPair>, vector<pair<int, nPair>>, NodeWeightComp> edges;

    // add nodes to priority queue based on edge weight
    for (pair<string, Node*> elt : cityNodes) {

        int idx = 0;
        //iterate through distances
        for (int distance : elt.second->distances) {

            Node * otherCity = getNode( cityNames[idx] );

            nPair p = {elt.second, otherCity };
            edges.push( {distance, p} ); 
            //results.push_back( {distance, p} );
            idx++;
        }
        //weights.push( {elt.second->distances, elt.second} );
       //DisjointSets ds(elt.second); 
    }
    
    ds.parent.resize( cityNames.size()  );
    ds.rank.resize( cityNames.size() );
  
    //DisjointSets ds();
    for (pair<string, Node*> elt : cityNodes) {
        ds.make_set(elt.second);
    }

    
    int merges = 0;

    while ( merges < cityNames.size() - 1 ) {
        Node * n1 = edges.top().second.first;
        Node * n2 = edges.top().second.second;
        int weight = edges.top().first;

        if( ds.find_set( n1 ) != ds.find_set( n2 ) ) {
            ds.union_sets(n1, n2);
            merges++;
            results.push_back( {weight, {n1, n2}} );
        }

        edges.pop();
        //if edge is already in set, do nothing
        
    }
    
    for( Edge e : results ) {
        cout << "weight: " << e.first << " of nodes " << e.second.first->city
            << " and " << e.second.second->city << endl;
    }



}

Node * Graph::getNode( int id ) {
    auto it = nodes.find(id);
    if (it == nodes.end()) {
        return nullptr;
    }
    return (*it).second;
}

Node * Graph::getNode( string id ) {
    auto it = cityNodes.find(id);
    if (it == cityNodes.end()) {
        return nullptr;
    }
    return (*it).second;
}

