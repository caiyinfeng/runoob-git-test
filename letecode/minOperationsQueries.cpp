/*
现有一棵由 n 个节点组成的无向树，节点按从 0 到 n - 1 编号。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ui, vi, wi] 表示树中存在一条位于节点 ui 和节点 vi 之间、权重为 wi 的边。
另给你一个长度为 m 的二维整数数组 queries ，其中 queries[i] = [ai, bi] 。对于每条查询，请你找出使从 ai 到 bi 路径上每条边的权重相等所需的 最小操作次数 。在一次操作中，你可以选择树上的任意一条边，并将其权重更改为任意值。
注意：
    查询之间 相互独立 的，这意味着每条新的查询时，树都会回到 初始状态 。
    从 ai 到 bi的路径是一个由 不同 节点组成的序列，从节点 ai 开始，到节点 bi 结束，且序列中相邻的两个节点在树中共享一条边。
返回一个长度为 m 的数组 answer ，其中 answer[i] 是第 i 条查询的答案。
输入：n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], queries = [[0,3],[3,6],[2,6],[0,6]]
输出：[0,0,1,3]
解释：第 1 条查询，从节点 0 到节点 3 的路径中的所有边的权重都是 1 。因此，答案为 0 。
第 2 条查询，从节点 3 到节点 6 的路径中的所有边的权重都是 2 。因此，答案为 0 。
第 3 条查询，将边 [2,3] 的权重变更为 2 。在这次操作之后，从节点 2 到节点 6 的路径中的所有边的权重都是 2 。因此，答案为 1 。
第 4 条查询，将边 [0,1]、[1,2]、[2,3] 的权重变更为 2 。在这次操作之后，从节点 0 到节点 6 的路径中的所有边的权重都是 2 。因此，答案为 3 。
对于每条查询 queries[i] ，可以证明 answer[i] 是使从 ai 到 bi 的路径中的所有边的权重相等的最小操作次数。

输入：n = 8, edges = [[1,2,6],[1,3,4],[2,4,6],[2,5,3],[3,6,6],[3,0,8],[7,0,2]], queries = [[4,6],[0,4],[6,5],[7,4]]
输出：[1,2,2,3]
解释：第 1 条查询，将边 [1,3] 的权重变更为 6 。在这次操作之后，从节点 4 到节点 6 的路径中的所有边的权重都是 6 。因此，答案为 1 。
第 2 条查询，将边 [0,3]、[3,1] 的权重变更为 6 。在这次操作之后，从节点 0 到节点 4 的路径中的所有边的权重都是 6 。因此，答案为 2 。
第 3 条查询，将边 [1,3]、[5,2] 的权重变更为 6 。在这次操作之后，从节点 6 到节点 5 的路径中的所有边的权重都是 6 。因此，答案为 2 。
第 4 条查询，将边 [0,7]、[0,3]、[1,3] 的权重变更为 6 。在这次操作之后，从节点 7 到节点 4 的路径中的所有边的权重都是 6 。因此，答案为 3 。
对于每条查询 queries[i] ，可以证明 answer[i] 是使从 ai 到 bi 的路径中的所有边的权重相等的最小操作次数。 
*/
#include <array>
#include <algorithm>
#include <functional>
#include "vectorPrint.h"
class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries) {
        vector<vector<pair<int, int>>> g(n);
        for (auto &e: edges) {
            int x = e[0], y = e[1], w = e[2] - 1;
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }
        int m = 32 - __builtin_clz(n); // n 的二进制长度
        vector<vector<int>> pa(n, vector<int>(m, -1));
        vector<vector<array<int, 26>>> cnt(n, vector<array<int, 26>>(m));
        vector<int> depth(n);
        function<void(int, int)> dfs = [&](int x, int fa) {
            pa[x][0] = fa;
            for (auto [y, w]: g[x]) {
                if (y != fa) {
                    cnt[y][0][w] = 1;
                    depth[y] = depth[x] + 1;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);
        vectorcoutAuto(depth);
        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                int p = pa[x][i];
                if (p != -1) {
                    int pp = pa[p][i];
                    pa[x][i + 1] = pp;
                    for (int j = 0; j < 26; ++j) {
                        cnt[x][i + 1][j] = cnt[x][i][j] + cnt[p][i][j];
                    }
                }
            }
        }
        vector<int> ans;
        for (auto &q: queries) {
            int x = q[0], y = q[1];
            int path_len = depth[x] + depth[y]; // 最后减去 depth[lca] * 2
            int cw[26]{};
            if (depth[x] > depth[y]) {
                swap(x, y);
            }
            // 让 y 和 x 在同一深度
            for (int k = depth[y] - depth[x]; k; k &= k - 1) {
                int i = __builtin_ctz(k);
                int p = pa[y][i];
                for (int j = 0; j < 26; ++j) {
                    cw[j] += cnt[y][i][j];
                }
                y = p;
            }
            if (y != x) {
                for (int i = m - 1; i >= 0; i--) {
                    int px = pa[x][i], py = pa[y][i];
                    if (px != py) {
                        for (int j = 0; j < 26; j++) {
                            cw[j] += cnt[x][i][j] + cnt[y][i][j];
                        }
                        x = px;
                        y = py; // x 和 y 同时上跳 2^i 步
                    }
                }
                for (int j = 0; j < 26; j++) {
                    cw[j] += cnt[x][0][j] + cnt[y][0][j];
                }
                x = pa[x][0];
            }
            int lca = x;
            path_len -= depth[lca] * 2;
            ans.push_back(path_len - *max_element(cw, cw + 26));
        }
        return ans;
    }
};
/*
这段C++代码实现了一个解决方案类 Solution，其中包含了一个函数 minOperationsQueries。以下是对该代码的解析：

数据结构：

g: 一个邻接表表示的图，存储了边的信息。每个节点有一个包含节点和边权值的 pair 列表。
pa: 一个二维数组，表示每个节点的祖先节点。pa[x][i] 表示节点 x 在距离为 2^i 的祖先节点。
cnt: 一个三维数组，用于记录每个节点的字符出现次数。cnt[x][i][j] 表示节点 x 到其距离为 2^i 的祖先节点路径上字符 j 的出现次数。
depth: 一个数组，记录每个节点的深度。
深度优先搜索（DFS）：

使用 DFS 构建树结构，并初始化 pa 和 cnt 数组。
构建祖先表：

通过两层循环，构建每个节点的祖先表 pa 和字符计数表 cnt。
查询处理：

对于每个查询，计算节点 x 和节点 y 的最近公共祖先（LCA）。
通过二进制升序遍历，调整节点 x 和 y 使其深度相同。
在调整过程中，更新字符计数表 cw。
在深度相同的情况下，同时升序遍历节点 x 和 y，找到它们的最近公共祖先。
计算路径长度和字符计数的差值，将结果添加到答案数组。
返回结果：

将所有查询的结果组成的数组返回。
这段代码主要解决了图的处理和最近公共祖先的计算，以及在查询中根据路径上字符的出现次数计算最终结果。
*/
int main() {
    Solution solution;
    int n = 5;
    vector<vector<int>> edges = {{0, 1, 2}, {1, 2, 3}, {1, 4, 4},{1,3,4}};
    vector<vector<int>> queries = {{0, 3}, {2, 4}, {2, 3}};

    vector<int> result = solution.minOperationsQueries(n, edges, queries);

    cout << "Result: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
