#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <limits.h>
#include <cstdint>
#include <string>

using namespace std;

class Node {
 protected:
  //MAYBE ADD CLASS DATA STRUCTURE(S) HERE
 public:
    int id;
    int index;

    vector<int>adj;

    // weighted adj list for part 3
    vector<int> distances;
    string city;

    int dist;
    Node * prev;
    
    Node(int id) {
        prev = nullptr;
        dist = INT_MAX;
        this->id = id;
        degree = -1;
        done = false;
    }

    Node( string str ) {
        prev = nullptr;
        dist = INT_MAX;
        city = str;
        done = false;
    }

    int degree;
    bool done;

    ~Node(void) {}

    bool operator<( const Node &other) {
        if (degree != other.degree) {
            //cout << "< returns " << endl;
            return degree > other.degree;
        }
        //give higher priority to the HCNode with the smaller id
        //cout << "degrees are equal, checking id" << endl;
        return id > other.id;
    }

};

#endif  // NODE_HPP
