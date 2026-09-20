#include <iostream>

#include "../src/graph/Graph.h"
#include "../src/traverse/dfs.h"

using namespace std;

int main()
{
    /*
        构造图：

            1
          /   \
         2     3
         |
         4
          \
           5

    */

    Graph g(5);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 5);

    cout << "DFS from 1:" << endl;

    vector<int> result = DFS(g, 1);

    for (int x : result)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}