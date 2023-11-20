// #include <bits/stdc++.h>
// using namespace std;
// const int N = 4;
// int final_path[N + 1];
// bool visited[N + 1];
// int final_res = INT_MAX;
// void copyToFinal(vector<int> &curr_path)
// {
//     for (int i = 0; i < N; i++)
//     {
//         final_path[i] = curr_path[i];
//     }
//     final_path[N] = curr_path[0];
// }
// int firstMin(vector<vector<int>> &adj, int i)
// {
//     vector<int>v;
//     for (int k = 0; k < N; k++)
//     {
//         v.push_back(adj[i][k]);
//     }
//     return *min_element(v.begin(), v.end());
// }
// int secondMin(vector<vector<int>> &adj, int i)
// {
//     vector<int>v;
//     for (int k = 0; k < N; k++)
//     {
//         v.push_back(adj[i][k]);
//     }
//     sort(v.begin(), v.end());
//     return v[1];
// }
// void TSPRec(vector<vector<int>> &adj, int curr_bound, int curr_weight, int level, vector<int> &curr_path)
// {
//     if (level == N)
//     {
//         if (adj[curr_path[level - 1]][curr_path[0]] != 0)
//         {
//             int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
//             if (curr_res < final_res)
//             {
//                 copyToFinal(curr_path);
//                 final_res = curr_res;
//             }
//         }
//         return;
//     }
//     for (int i = 0; i < N; i++)
//     {
//         if (adj[curr_path[level - 1]][i] != 0 && visited[i] == false)
//         {
//             int temp = curr_bound;
//             curr_weight += adj[curr_path[level - 1]][i];
//             if (level == 1)
//             {
//                 curr_bound -= ((firstMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
//             }
//             else
//             {
//                 curr_bound -= ((secondMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
//             }
//             if (curr_bound + curr_weight < final_res)
//             {
//                 curr_path[level] = i;
//                 visited[i] = true;
//                 TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
//             }
//             curr_weight -= adj[curr_path[level - 1]][i];
//             curr_bound = temp;
//             memset(visited, false, sizeof(visited));
//             for (int j = 0; j <= level - 1; j++)
//             {
//                 visited[curr_path[j]] = true;
//             }
//         }
//     }
// }
// void TSP(vector<vector<int>> &adj)
// {
//     vector<int> curr_path(N + 1);
//     int curr_bound = 0;
//     for (int i = 0; i < curr_path.size(); i++)
//     {
//         curr_path[i] = -1;
//     }
//     for (int i = 0; i < curr_path.size(); i++)
//     {
//         visited[i] = 0;
//     }
//     for (int i = 0; i < N; i++)
//     {
//         curr_bound += (firstMin(adj, i) + secondMin(adj, i));
//     }
//     curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;
//     //cout<<curr_bound<<endl;
//     visited[0] = true;
//     curr_path[0] = 0;
//     TSPRec(adj, curr_bound, 0, 1, curr_path);
// }
// int main()
// {
//     vector<vector<int>> adj(N, vector<int>(N));
//     // cout << "Enter The Value OF Weights In Matrix" << endl;
//     // for (int i = 0; i < N; i++)
//     // {
//     //     for (int j = 0; j < N; j++)
//     //     {
//     //         if(i!=j&&adj[i][j]==0)
//     //         {
//     //             cout << "Enter The Value of edge: " << i << " - " << j << endl;
//     //             int x;
//     //             cin >> x;
//     //             adj[i][j] = x;
//     //             adj[j][i] = x;
//     //         }
//     //     }
//     // }
//     adj = {
//         {0, 20, 10, 12},
//         {20, 0, 15, 11},
//         {10, 15, 0, 17},
//         {12, 11, 17, 0}};
//     TSP(adj);
//     cout << "Minimum cost : " << final_res << endl;
//     cout << "Path Taken : ";
//     for (int i = 0; i < N; i++)
//     {
//         cout << final_path[i] << " -> ";
//     }
//     cout << final_path[N] << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
const int n = 3;
const int MAX = 1000000;
int dist[n + 1][n + 1] = {
        {0, 20, 10, 12},
        {20, 0, 15, 11},
        {10, 15, 0, 17},
        {12, 11, 17, 0}};
int memo[n + 1][1 << (n + 1)];

int fun(int i, int mask)
{
    if (mask == ((1 << i) | 3))
        return dist[1][i];

    if (memo[i][mask] != 0)
        return memo[i][mask];

    int res = MAX; // result of this sub-problem

    for (int j = 1; j <= n; j++)
        if ((mask & (1 << j)) && j != i && j != 1)
            res = std::min(res, fun(j, mask & (~(1 << i))) + dist[j][i]);
    return memo[i][mask] = res;
}
// Driver program to test above logic
int main()
{
    int ans = MAX;
    for (int i = 1; i <= n; i++)
        ans = std::min(ans, fun(i, (1 << (n + 1)) - 1) + dist[i][1]);

    printf("The cost of most efficient tour = %d", ans);

    return 0;
}
