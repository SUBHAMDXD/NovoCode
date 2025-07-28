#include <vector>
#include <numeric> // For std::accumulate (optional, can do manually)
#include <algorithm> // For std::max

class Solution {
public:
    int countMaxOrSubsets(std::vector<int>& nums) {
        int n = nums.size();
        int max_or = 0;

        // Step 1: Find the maximum possible bitwise OR
        // The maximum OR will be the bitwise OR of all elements in nums.
        for (int num : nums) {
            max_or |= num;
        }

        int count = 0;

        // Step 2: Iterate through all possible non-empty subsets
        // A bitmask 'i' represents a subset. If the j-th bit of 'i' is set,
        // then nums[j] is included in the current subset.
        // We iterate from 1 to (1 << n) - 1 to cover all non-empty subsets.
        for (int i = 1; i < (1 << n); ++i) {
            int current_or = 0;
            // Calculate the bitwise OR for the current subset
            for (int j = 0; j < n; ++j) {
                // Check if the j-th bit is set in the current mask 'i'
                if ((i >> j) & 1) {
                    current_or |= nums[j];
                }
            }

            // If the current subset's OR equals the maximum OR, increment count
            if (current_or == max_or) {
                count++;
            }
        }

        return count;
    }
};