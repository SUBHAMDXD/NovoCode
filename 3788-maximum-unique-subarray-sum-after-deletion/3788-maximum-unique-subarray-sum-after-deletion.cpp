#include <vector>
#include <numeric>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Calculates the maximum sum of a unique-element subarray after deletions.
     * @param nums The input integer array.
     * @return The maximum possible sum.
     */
    int maxSum(std::vector<int>& nums) {
        // Find all unique numbers in the input array.
        std::unordered_set<int> unique_nums(nums.begin(), nums.end());

        int current_max_sum = 0;
        bool has_positive = false;

        // Sum all the unique numbers that are positive.
        for (int num : unique_nums) {
            if (num > 0) {
                current_max_sum += num;
                has_positive = true;
            }
        }
        
        // Handle the edge case where no positive unique numbers exist.
        // Since the array cannot be empty, we must pick the single largest
        // unique number (which will be <= 0).
        if (!has_positive) {
            return *std::max_element(unique_nums.begin(), unique_nums.end());
        }

        return current_max_sum;
    }
};