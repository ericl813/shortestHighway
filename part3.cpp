#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include <algorithm>

using namespace std;

void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
        << " city_names_file distance_matrix_file output_file"
        << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {

    // incorrect number of user-input args
    if (argc != 4) {
        usage(argv[0]);
    }

    // arg 0 is executable, 1 is graph file, 2 is k, 3 is output file
    char* names_filename = argv[1];
    char* matrix_filename = argv[2];
    char* output_filename = argv[3];

    Graph g;
    // build the graph
    g.loadCities(names_filename, matrix_filename);

    ifstream infile(names_filename);

    vector<Edge> results;
    
    // call kruskals algorith passing vector by reference
    g.kruskals( results );

    ofstream ofs;
    ofs.open( output_filename, ios::binary );

    // go through the edges and print the data
    for( Edge e : results ) {
       ofs << e.first << " " << e.second.first->city << " " << e.second.second->city << endl;
    }

    ofs.close();
}

