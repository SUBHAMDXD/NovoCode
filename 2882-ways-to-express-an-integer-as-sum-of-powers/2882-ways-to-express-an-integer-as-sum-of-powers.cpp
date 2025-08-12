#include <vector>

class Solution {
public:
    int numberOfWays(int n, int x) {
        // Define the modulus
        const int MOD = 1e9 + 7;

        // dp[i] will store the number of ways to get sum i
        std::vector<int> dp(n + 1, 0);
        
        // Base case: there is one way to get sum 0 (by choosing no numbers)
        dp[0] = 1;

        // Iterate through each number from 1 upwards
        for (int num = 1; ; ++num) {
            // Calculate num^x
            long long power = 1;
            for (int i = 0; i < x; ++i) {
                power *= num;
            }

            // If num^x exceeds n, this number and any larger ones cannot be used
            if (power > n) {
                break;
            }

            // Update the dp table using a 0/1 knapsack approach.
            // Iterate backwards to ensure each number is used at most once.
            for (int j = n; j >= power; --j) {
                dp[j] = (dp[j] + dp[j - power]) % MOD;
            }
        }

        return dp[n];
    }
};