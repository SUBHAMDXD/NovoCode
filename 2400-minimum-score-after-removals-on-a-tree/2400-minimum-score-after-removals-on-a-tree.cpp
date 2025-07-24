#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>

class Solution {
public:
    /**
     * @brief Calculates the minimum possible score after removing two edges from a tree.
     * * @param nums A vector of integers representing the value of each node.
     * @param edges A 2D vector representing the edges of the tree.
     * @return The minimum possible score.
     */
    int minimumScore(std::vector<int>& nums, std::vector<std::vector<int>>& edges) {
        int n = nums.size();
        // Adjacency list to represent the tree
        adj.assign(n, std::vector<int>());
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Vectors to store DFS results
        xor_values.assign(n, 0);
        start_time.assign(n, 0);
        end_time.assign(n, 0);
        timer = 0;

        // Perform DFS from root 0 to pre-calculate subtree XORs and timings for ancestry checks.
        dfs(0, -1, nums);

        long long min_score = LLONG_MAX;
        // The total XOR sum of all nodes in the tree is the XOR sum of the root's subtree.
        int total_xor = xor_values[0];

        // Iterate through all unique pairs of nodes (i, j) other than the root.
        // Cutting the edge to node i and node j creates the two removals.
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int xor_i = xor_values[i];
                int xor_j = xor_values[j];
                
                int comp1, comp2, comp3;

                // Determine the three component XOR sums based on the relationship
                // between node i and node j's subtrees.
                if (is_ancestor(i, j)) { // Node j is in the subtree of node i
                    comp1 = xor_j;
                    comp2 = xor_i ^ xor_j;
                    comp3 = total_xor ^ xor_i;
                } else if (is_ancestor(j, i)) { // Node i is in the subtree of node j
                    comp1 = xor_i;
                    comp2 = xor_j ^ xor_i;
                    comp3 = total_xor ^ xor_j;
                } else { // Subtrees of i and j are disjoint
                    comp1 = xor_i;
                    comp2 = xor_j;
                    comp3 = total_xor ^ xor_i ^ xor_j;
                }
                
                // Calculate the score for this pair of removals.
                long long current_score = (long long)std::max({comp1, comp2, comp3}) - std::min({comp1, comp2, comp3});
                min_score = std::min(min_score, current_score);
            }
        }
        return static_cast<int>(min_score);
    }

private:
    std::vector<std::vector<int>> adj;
    std::vector<int> xor_values;
    std::vector<int> start_time;
    std::vector<int> end_time;
    int timer;

    /**
     * @brief Performs DFS to calculate subtree XOR sums and traversal times.
     * * @param u The current node.
     * @param p The parent of the current node.
     * @param nums The values of the nodes.
     * @return The XOR sum of the subtree rooted at u.
     */
    int dfs(int u, int p, const std::vector<int>& nums) {
        start_time[u] = timer++;
        int current_xor_sum = nums[u];
        for (int v : adj[u]) {
            if (v != p) {
                current_xor_sum ^= dfs(v, u, nums);
            }
        }
        xor_values[u] = current_xor_sum;
        end_time[u] = timer++;
        return current_xor_sum;
    }

    /**
     * @brief Checks if node u is an ancestor of node v.
     * * @param u Potential ancestor node.
     * @param v Potential descendant node.
     * @return True if u is an ancestor of v, false otherwise.
     */
    bool is_ancestor(int u, int v) {
        return start_time[u] < start_time[v] && end_time[u] > end_time[v];
    }
};
