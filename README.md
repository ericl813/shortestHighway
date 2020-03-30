Coded by: Daniel Xiong, Eric Luong

1. A description of the data set.

We used the CITIES dataset provided by FSU. The specific dataset we used is a set of 128 cities
in the United States with intercity distances. The distances are provided in a city-to-city distance
matrix.

2. A description of the problem you solved and the algorithms and data structures
you used. 

The problem we aim to solve is deciding how to build the shortest highway system that connects
a certain number of cities. We decided to use Kruskal’s algorithm to build a minimum spanning
tree which would represent the final highway. We used the built-in priority queue to sort all the
edges and a disjoint set that we implemented ourselves to store the vertices. We implemented the
disjoint set as a struct as part of the Graph object. We also used the built in data structure of the
unordered_map to store our vertices.

3. Your Results - Describe and show in your report how your program solves the
problem you set out to explore. 

Our goal is to construct the shortest highway system that connects all the cities, using only
straight paths from one city to another. We ignore the possibility that two roads could cross. We
require 3 command line arguments; the first two are input files and the last one is the output file.
The first two input files should be a list of the names of the cities and a 2x2 matrix representing
the inter-city distance. The first file should be a file with the names of each city with one name
on each line. The second file should represent the intercity distances as a 2x2 matrix; this should
be in the same order as the first file. This means that the first city in the names file should
correspond to the first row of the distances file. The third file is the file to which we will write
our output. Our output represents the highways that we should build in order to construct the
shortest highway system. The output file will have the names of two cities and the distance
between them following on each line.

Examples of Tests:
Run “./build/part3 names.txt dist.txt testOut” in terminal after building

Content of names.txt
Aberystwyth
Brighton
Edinburgh
Exeter
Glasgow
Inverness
Liverpool
London
Newcastle
Nottingham
Oxford
Stratford

Content of dist.txt
 0.0 27.0 12.1 17.7 11.0 29.2 22.4
 27.0 0.0 16.8 11.2 29.2 11.0 31.8
 12.1 16.8 0.0 6.0 12.5 17.1 27.9
 17.7 11.2 6.0 0.0 18.0 11.7 30.0
 11.0 29.2 12.5 18.0 0.0 27.0 33.2
 29.2 11.0 17.1 11.7 27.0 0.0 40.2
 22.4 31.8 27.9 30.0 33.2 40.2 0.0
 
Content of testOut (after program is ran)
47 Aberystwyth Nottingham
67 Newcastle Liverpool
88 Edinburgh Glasgow
108 Stratford London
117 Oxford Liverpool
122 Inverness London
130 Glasgow Nottingham
133 Oxford Glasgow
138 Liverpool Brighton
139 Glasgow Exeter
155 London Nottingham
