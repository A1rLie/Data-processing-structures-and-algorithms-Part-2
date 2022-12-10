#ifndef GRAPGH_H
#define GRAPGH_H

#include<vector>
#include<list>
#include<iostream>

using namespace std;

class Grapgh
{
private:
    struct Node
    {
        int value = 0;
        int distance = 0;
    };

    vector<list<Node>> graph;

    void reset(int* buffer, int size, int ignorTop);

    int* Bellman_Ford(int start);
    
public:
    Grapgh();

    bool add(int where, int what, int distance);

    void print();

    int getBellmanFord(int start, int finish);

    int findEccentricity(int top);
};

#endif
