#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "node.hpp"
#include <string>

using namespace std;
//represents edges
typedef pair <Node *, Node *> nPair;
typedef pair<int, nPair> Edge;

//self implemented disjoint set
struct DisjointSets {
    vector<Node *> parent;
    vector<int> rank;

    void make_set(Node* v) {
        //cout << "setting parent at index " << v->index << " to " << v->city << endl;
        parent[v->index] = v;
        rank[v->index] = 0;
    }

    Node* find_set(Node* v) {
        if (v->city == parent[v->index]->city)
            return v;
        return parent[v->index] = find_set(parent[v->index]);
    }

    void union_sets(Node* a, Node* b) {
        a = find_set(a);
        b = find_set(b);
        if ( a->city != b->city ) {
            if (rank[a->index] < rank[b->index])
                swap(a, b);
            parent[b->index] = a;
            if (rank[a->index] == rank[b->index])
                rank[a->index]++;
        }
    }

};


class NodePtrComp {
public:
    // the comparator that will substitute instead of deafult priority queue's
    bool operator()(pair<int ,Node*> &p1, pair<int, Node*> &p2) const {
        return *(p1.second) < *(p2.second);
    }
};

class NodeWeightComp {
public:
    bool operator()(pair<int ,nPair> &p1, pair<int, nPair> &p2) const {
        return p1.first > p2.first;
    }

};

class Graph {
 protected:
    //vector<Node*>nodes;
    unordered_map<int,Node*> nodes;

    unordered_map<string, Node*> cityNodes;

    vector<string> cityNames;

    DisjointSets ds;
    //MAYBE ADD CLASS DATA STRUCTURE(S) HERE

 public:
    Graph(void);

    ~Graph(void);

    //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
	
    /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

    bool loadFromFile(const char* in_filename);

    bool loadCities(const char* cities_filename, const char* matrix_filename);

    bool pathfinder(Node* from, Node* to);
    
    void socialgathering(vector<int>& invitees, const int& k);

    void kruskals( vector<Edge>& results );

    Node * getNode( int id );

    Node * getNode( string id );
    

   };

#endif  // GRAPH_HPP
