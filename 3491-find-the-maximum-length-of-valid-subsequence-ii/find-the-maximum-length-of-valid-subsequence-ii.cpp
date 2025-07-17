#include <vector>
#include <numeric>
#include <algorithm>


class Solution {
public:
    /**
     * @brief Finds the length of the longest subsequence where the sum of any two adjacent elements modulo k is constant.
     * * @param nums The input vector of integers.
     * @param k The modulus.
     * @return The maximum length of such a subsequence.
     */
    int maximumLength(std::vector<int>& nums, int k) {
        int max_len = 0;
        // We iterate through every possible target sum `t` for (a + b) % k.
        for (int t = 0; t < k; ++t) {
            // dp[r] will store the length of the longest subsequence with target sum `t`
            // that ends in a number with remainder `r`.
            std::vector<int> dp(k, 0);
            for (int num : nums) {
                int current_rem = num % k;
                // To extend a subsequence, the previous element must have a remainder `prev_rem`
                // such that (prev_rem + current_rem) % k == t.
                // So, prev_rem = (t - current_rem + k) % k.
                int prev_rem = (t - current_rem + k) % k;
                
                // The new length is 1 + the length of the subsequence ending in prev_rem.
                dp[current_rem] = dp[prev_rem] + 1;
            }
            // After checking all numbers for a given target `t`, find the max length achieved.
            for (int len : dp) {
                max_len = std::max(max_len, len);
            }
        }
        return max_len;
    }
};