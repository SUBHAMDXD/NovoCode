#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        // Step 1: Pre-process pairs into an adjacency list where adj[r] stores l's for pairs [l, r].
        vector<vector<int>> adj(n + 1);
        for (const auto& pair : conflictingPairs) {
            int u = pair[0];
            int v = pair[1];
            if (u > v) swap(u, v); // Ensure u is the smaller value (l) and v is the larger (r)
            adj[v].push_back(u);
        }

        // Step 2: Compute m1, m2, and count_m1 arrays.
        // m1[j]: max 'l' over all pairs [l, r] with r <= j.
        // m2[j]: second max 'l' over all pairs [l, r] with r <= j.
        // count_m1[j]: number of pairs [l, r] with r <= j and l = m1[j].
        vector<long long> m1(n + 1, 0);
        vector<long long> m2(n + 1, 0);
        vector<int> count_m1(n + 1, 0);

        vector<int> max_l_at(n + 1, 0);
        vector<int> second_max_l_at(n + 1, 0);
        vector<int> num_max_l_at(n + 1, 0);

        // Precompute max, second max, and count of max 'l' for each right endpoint 'j'.
        for (int j = 1; j <= n; ++j) {
            if (adj[j].empty()) continue;
            sort(adj[j].rbegin(), adj[j].rend()); // Sort 'l's in descending order
            max_l_at[j] = adj[j][0];
            int count = 0;
            for (int l : adj[j]) {
                if (l == max_l_at[j]) {
                    count++;
                } else {
                    second_max_l_at[j] = l;
                    break;
                }
            }
            num_max_l_at[j] = count;
        }

        // Iteratively compute m1, m2, and count_m1 for each j from 1 to n.
        for (int j = 1; j <= n; ++j) {
            vector<long long> candidates = {m1[j - 1], m2[j - 1], (long long)max_l_at[j], (long long)second_max_l_at[j]};
            sort(candidates.rbegin(), candidates.rend());
            
            m1[j] = candidates[0];
            m2[j] = 0;
            for(long long val : candidates) {
                if (val < m1[j]) {
                    m2[j] = val;
                    break;
                }
            }

            if (m1[j] > m1[j - 1]) {
                count_m1[j] = num_max_l_at[j];
            } else { // m1[j] == m1[j-1]
                count_m1[j] = count_m1[j-1];
                if (max_l_at[j] == m1[j]) {
                    count_m1[j] += num_max_l_at[j];
                }
            }
        }

        // Step 3: Compute base_count, the number of valid subarrays with all conflicting pairs.
        long long base_count = 0;
        for (int j = 1; j <= n; ++j) {
            base_count += j - m1[j];
        }

        // Step 4: Compute the maximum possible gain by removing one pair.
        // A gain occurs for a subarray if it was invalid ONLY due to the removed pair.
        vector<long long> delta_prime(n + 1, 0);
        for (int j = 1; j <= n; ++j) {
            // A gain is possible only if m1[j] was determined by a single unique pair.
            if (count_m1[j] == 1) {
                delta_prime[j] = m1[j] - m2[j];
            }
        }
        
        vector<long long> gain_for_l(n + 1, 0);
        long long max_gain = 0;

        // Iterate backwards from n to 1 to calculate gains using a suffix-sum-like approach.
        for (int j = n; j >= 1; --j) {
            long long l_to_update = m1[j];
            long long d_p = delta_prime[j];
            if (d_p > 0) {
                gain_for_l[l_to_update] += d_p;
            }
            
            // For any pair [l_k, j] ending at j, its total gain is the currently accumulated gain_for_l[l_k].
            for (int l_k : adj[j]) {
                max_gain = max(max_gain, gain_for_l[l_k]);
            }
        }
        
        // Step 5: The result is the base count plus the maximum gain found.
        return base_count + max_gain;
    }
};