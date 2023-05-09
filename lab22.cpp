#include "Heap.hpp"
#include <chrono> 



std::vector<std::vector<Pair>> graphGenerator(int n, double p, int maxL)
{
    std::vector<std::vector<Pair>> graph(n);
    int r = int(double(n * (n - 1) / 2) * p) - n + 1;

    for (int i = 1; i < n; i++)
    {
        int l = rand() % maxL;
        graph[0].push_back(Pair(i, l));
        graph[i].push_back(Pair(0, l));
    }

    for (int i = 0; i < r; i++)
    {
        int v = rand() % (n - 1) + 1;
        int u = rand() % (n - 1) + 1;

        if (v == u)
        {
            i--;
            continue;
        }

        bool isExist = false;
        for (int j = 0; j < graph[v].size(); j++)
            if (graph[v][j].v == u)
            {
                isExist = true;
                break;
            }
        if (isExist)
        {
            i--;
            continue;
        }

        int l = rand() % maxL;
        graph[v].push_back(Pair(u, l));
        graph[u].push_back(Pair(v, l));
    }

    return graph;
}

int main()
{
    int n = 10;
    double p = 0.9;
    int maxL = 100;

    std::vector<std::vector<Pair>> graph = graphGenerator(n, p, maxL);
    int s = rand() % (n - 1) + 1;

    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << i + 1 << ": ";
    //     for (int j = 0; j < graph[i].size(); j++)
    //         std::cout << "{" << graph[i][j].v + 1 << ", " << graph[i][j].l << "} ";
    //     std::cout << '\n';
    // }

    // std::cout << "s = " << s + 1 << '\n';

    Heap h;
    h.Insert(new Node(Pair(s, 0)));

    std::vector<int> res(n, INT32_MAX);
    res[s] = 0;

    std::vector<bool> isUsed(n, false);
    isUsed[s] = true;

    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < n; i++)
    {
        Pair e = h.Extract_Min()->n;
        int v = e.v;

        isUsed[v] = true;

        for (int j = 0; j < graph[v].size(); j++)
        {
            int u = graph[v][j].v;
            if (!isUsed[u])
            {
                res[u] = std::min(res[u], res[v] + graph[v][j].l);
                h.Insert(new Node(Pair(u, res[u])));
            }
        }
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration <float> duration = (start - end) / 1000;

    for (int i = 0; i < n; i++)
        std::cout << i + 1 << ' ' << res[i] << '\n';



    std::cout << duration.count() << "s" << std::endl;
}













