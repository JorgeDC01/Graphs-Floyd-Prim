# Graphs-Floyd-Prim---ADA-Project

## Summary
This repository contains a C++ implementation of Prim's and Floyd's algorithms applied to graphs for calculating paths and costs associated with the Eduroam network connections at the University of Extremadura. The goal is to analyze connections made by university staff and students to the Eduroam WiFi network nodes.

## Problem Statement
The University of Extremadura wants to develop a study on the connections made to the Eduroam network. The program reads a series of connection records to each Eduroam UEx node, along with the cost of these connections.

The input file `conexiones.in` follows this format:
1. The first line contains an integer **n** (between 2 and 6) indicating the number of Eduroam UEx nodes under study.
2. The next **n** lines list the identifiers of the Eduroam UEx nodes, with a maximum of 8 characters.
3. An integer **u** (between 2 and 14) follows, indicating the number of users connected to the nodes.
4. The next **u** lines list the identifiers of the user devices, also with a maximum of 8 characters.
5. An integer **d** (between 1 and (n+u)²) follows, indicating the number of recorded connections.
6. Each of the next **d** lines contains three data points: `identifier1 identifier2 cost`, where `identifier1` and `identifier2` are the identifiers of user devices and Eduroam nodes, and `cost` is a positive real number indicating the data transmission time for that connection.
7. The file then contains an integer **p** (between 1 and (n+u)²) indicating **p** queries about the lowest connection cost between different devices and nodes.
8. Each of the next **p** lines contains the names of two devices (Eduroam nodes or user devices) separated by whitespace.

### Output File
The output file named `datos.out` will contain the following information:
- **P** lines, one for each query from the input file. Each line shows the path (in the graph) that connects two devices, listing the names of the devices or nodes traversed, separated by spaces, along with the total cost of that connection.
- Additionally, the program will determine which connections should be improved with fiber optics to minimize costs and ensure all nodes are connected.

## Implementation Details
- The algorithms are implemented in C++ without using graph libraries.
- The code is documented to explain the main decisions taken during implementation and to provide a complexity analysis of the algorithms developed.

## Important Script Parameters
- Modify the path of the input CSV file in the variable **PATH_TRANSLATION_CSV**.
- The number of translations per API call can be adjusted in the global variable **BATCH_ELEMENTS_PARAM**. The default value is 50.
- The number of groups of literals to translate can be changed in the global variable **N_GROUPS_PROCESSED**.

## Execution
To run the program, ensure you have a C++ compiler installed. You can compile and run the program using the following commands:

```bash
g++ -o graph_algorithm graph_algorithm.cpp
./graph_algorithm
```

## Conclusion
This implementation provides a comprehensive approach to analyzing Eduroam network connections using graph algorithms. By leveraging Prim's and Floyd's algorithms, the program efficiently calculates paths and costs, allowing for better management of network connections at the University of Extremadura.
