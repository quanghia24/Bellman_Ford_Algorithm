#include <iostream>
#include <vector>
#include <limits>
#include <list>
#include <string>
#include <algorithm>
using namespace std;
// Function to perform one step of Bellman-Ford algorithm

void BF_full(int graph[20][20], int n, char S, int BFValue[20], int BFPrev[20])
{
  int start = S - 'A';
  if (BFValue[start] == -1)
    BFValue[start] = 0;

  // For each vertex, apply relaxation for all the edges
  for (int k = 0; k < n - 1; ++k)
  {
    int updateValue[n];
    for (int i{}; i < n; i++)
      updateValue[i] = -1;

    for (int i = 0; i < n; ++i)
    {
      if (BFValue[i] == -1)
        continue;
      // cout << i << ": \n";
      for (int j = 0; j < n; ++j)
      {
        if (j == start || graph[i][j] == 0) // having no connection
          continue;
        // cout << j << "[" << BFValue[i] << " " <<  graph[i][j] << " " << BFValue[j] << "]"<< endl;
        if (BFValue[j] == -1 || BFValue[i] + graph[i][j] < BFValue[j])
        {
          if (updateValue[j] == -1 || (updateValue[j] > BFValue[i] + graph[i][j]))
          {
            updateValue[j] = BFValue[i] + graph[i][j];
            BFPrev[j] = i;
            // cout << "yess " << updateValue[j] << endl;
          }
        }
      }
    }

    // update value
    for (int i{}; i < n; i++)
      if (updateValue[i] != -1)
        BFValue[i] = updateValue[i];
  }

  // No negative edges -> no negative cycle
}

string reconstructPath(int BFPrev[20], char start, char end)
{

  if (BFPrev[end - 'A'] == -1)
  {
    char tmp1 = start - 'A' + 'A';
    string path2 = "";
    path2 += tmp1;

    return path2;
  }

  string path = "";
  int node = end - 'A';
  while (node != start - 'A')
  {
    char temp = node + 'A';
    path = temp + path;
    path = " " + path;
    node = BFPrev[node];
  }
  path = start + path;
  return path;
}

// Bellman-Ford algorithm for finding shortest paths with character vertex labels
string BF_Path(int graph[20][20], int n, char src, char dest)
{
  int BFValue[20];
  int BFPrev[20];
  for (int i = 0; i < 20; i++)
    BFValue[i] = BFPrev[i] = -1;

  BF_full(graph, n, src, BFValue, BFPrev);

  return reconstructPath(BFPrev, src, dest); // Shortest path found
}

int main()
{
  int n = 8;
  int G[20][20] = {
      {0, 72, 89, 77, 2, 58, 13, 69},
      {77, 0, 69, 31, 57, 93, 83, 48},
      {52, 21, 0, 62, 8, 77, 32, 14},
      {33, 1, 40, 0, 72, 99, 72, 59},
      {89, 24, 1, 61, 0, 12, 78, 63},
      {36, 91, 98, 79, 20, 0, 28, 1},
      {18, 77, 49, 36, 98, 77, 0, 45},
      {75, 9, 59, 7, 77, 65, 45, 0}};

  cout << BF_Path(G, n, 'A', 'E');
  return 0;
}
