#include "Grapgh.h"

Grapgh::Grapgh()
{
    list<Node> temp;
    graph.push_back(temp);
}

bool Grapgh::add(int where, int what, int distance)
{
    if ((where >= graph.size() + 1 || what > graph.size() + 2) && graph.size() != 0) return false;
    else
    {
        where--;
        what--;
        Node node;
        node.value = what;
        node.distance = distance;
        graph[where].push_back(node);
        if (what < graph.size())
        {
            node.value = where;
            graph[what].push_back(node);
        }
        else
        {
            list<Node> temp;
            graph.push_back(temp);
            node.value = where;
            graph[graph.size() - 1].push_back(node);
        }
    }
    return true;
}


void Grapgh::print()
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << "[" << i + 1 << "] ";
        for (auto iter = graph[i].begin(); iter != graph[i].end(); iter++)
        {
            cout << (*iter).value + 1 << " ";
        }
        cout << endl;
    }
}

int Grapgh::getBellmanFord(int start, int finish)
{
    if (start > graph.size() || finish > graph.size()) return -1;
    int* result = Bellman_Ford(start - 1);
    int res = result[finish - 1];
    delete[] result;
    return res;
}

int Grapgh::findEccentricity(int top)
{
    if (top > graph.size() || graph.size() <= 0) return -1;

    int* distance = Bellman_Ford(top - 1);
    int max = distance[0];
    for (int i = 1; i < graph.size(); i++)
    {
        if (max < distance[i]) max = distance[i];
    }
    return max;
}

int* Grapgh::Bellman_Ford(int start)
{
    int* buffer = new int[graph.size()];
    reset(buffer, graph.size(), start);

    int* result = new int[graph.size()];
    reset(result, graph.size(), start);

    for (int level = 1; level < graph.size() + 1; level++)
    {
        for (int top = 0; top < graph.size(); top++)
        {
            //Скипаем если дистанция равна -беск
            if (result[top] == INT_MAX) continue;

            //Пробегаемся по всем связям вершины
            for (auto iter = graph[top].begin(); iter != graph[top].end(); iter++)
            {
                //Если расстояние в буффере меньше чем новое возможное расстояние, то записываем новое расстояние
                if (buffer[(*iter).value] > result[top] + (*iter).distance && result[top] + (*iter).distance > 0)
                {
                    buffer[(*iter).value] = (*iter).distance + result[top];
                }
            }
        }
        for (int top = 0; top < graph.size(); top++)
        {
            result[top] = buffer[top];
        }
        reset(buffer, graph.size(), start);

    }
    delete[] buffer;
    return result;
}

void Grapgh::reset(int* buffer, int size, int ignorTop)
{
    for (int i = 0; i < size; i++)
    {
        if (i == ignorTop) buffer[i] = 0;
        else buffer[i] = INT_MAX;
    }
}
