#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<list>
#include<iostream>

using namespace std;

class Graph
{
private:
    struct Node
    {
        int cityNumber = 0;
        int roadWeight = 0;
    };

    vector<list<Node>> cities;

public:
    Graph();

    void optimize();

    bool add(int where, int what, int distance);

    void print();
};

#endif
