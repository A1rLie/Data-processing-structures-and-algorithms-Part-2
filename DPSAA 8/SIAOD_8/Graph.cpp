#include "Graph.h"

Graph::Graph()
{
    list<Node> temp;
    cities.push_back(temp);
}

void Graph::optimize()
{
    for (int currentCity = 0; currentCity < cities.size(); currentCity++)
    {
        if (cities[currentCity].size() == 1) continue;
        for (auto connectedCity = cities[currentCity].begin(); connectedCity != cities[currentCity].end(); connectedCity++)
        {
            bool ignoreCity = false;
            for (auto city = cities[(*connectedCity).cityNumber].begin(); city != cities[(*connectedCity).cityNumber].end(); city++)
            {
                if ((*connectedCity).roadWeight > (*city).roadWeight)
                {
                    ignoreCity = true;
                    break;
                }
            }
            if (!ignoreCity && cities[(*connectedCity).cityNumber].size() > 1)
            {
                int deletedCity = (*connectedCity).cityNumber;
                connectedCity = cities[currentCity].erase(connectedCity);
                auto j = cities[deletedCity].begin();
                for (; j != cities[deletedCity].end(); j++)
                {
                    if ((*j).cityNumber == currentCity) break;
                }
                cities[deletedCity].erase(j);
            }
        }
    }
}

bool Graph::add(int where, int what, int weight)
{
    if ((where >= cities.size() + 1 || what > cities.size() + 2) && cities.size() != 0) return false;
    else
    {
        where--;
        what--;
        Node node;
        node.cityNumber = what;
        node.roadWeight = weight;
        cities[where].push_back(node);
        if (what < cities.size())
        {
            node.cityNumber = where;
            cities[what].push_back(node);
        }
        else
        {
            list<Node> temp;
            cities.push_back(temp);
            node.cityNumber = where;
            cities[cities.size() - 1].push_back(node);
        }
    }
    for (auto i = cities[what].begin(); i != cities[what].end(); i++)
    {
        for (auto j = i; j != cities[what].end(); j++)
        {
            if ((*j).roadWeight < (*i).roadWeight)
            {
                swap((*j).cityNumber, (*i).cityNumber);
                swap((*j).roadWeight, (*i).roadWeight);
            }
        }
    }

    for (auto i = cities[where].begin(); i != cities[where].end(); i++)
    {
        for (auto j = i; j != cities[where].end(); j++)
        {
            if ((*j).roadWeight < (*i).roadWeight)
            {
                swap((*j).cityNumber, (*i).cityNumber);
                swap((*j).roadWeight, (*i).roadWeight);
            }
        }
    }
    return true;
}


void Graph::print()
{
    for (int i = 0; i < cities.size(); i++)
    {
        cout << "[" << i + 1 << "]: ";
        for (auto iter = cities[i].begin(); iter != cities[i].end(); iter++)
        {
            cout << "<" << (*iter).cityNumber + 1 << ", " << (*iter).roadWeight << ">, ";
        }
        cout << endl;
    }
}
