#include <vector>
#include <numeric> // For std::accumulate (not directly used here but good to include)
#include <algorithm> // For std::max (not directly used here but good to include)

// Using a class structure as required by LeetCode
class Solution {
private:
    int max_or_val;       // Stores the maximum possible bitwise OR
    int count;            // Stores the number of subsets with max_or_val
    std::vector<int> nums_arr; // Stores the input array for easy access in DFS
    int n;                // Stores the size of the input array

    // Recursive DFS function to explore subsets
    // index: current position in nums_arr being considered
    // current_or: bitwise OR of elements chosen so far in the current subset
    void dfs(int index, int current_or) {
        // Optimization: If the current_or already matches the maximum possible OR,
        // then any combination of the remaining elements (from 'index' to 'n-1')
        // will also result in 'max_or_val' when OR-ed with 'current_or'.
        // There are 2^(n - index) such combinations.
        if (current_or == max_or_val) {
            count += (1 << (n - index)); // Add 2^(number of remaining elements)
            return; // Prune this branch, no need to explore further
        }

        // Base Case: If we have processed all elements
        if (index == n) {
            // If current_or did not match max_or_val, this branch doesn't contribute.
            return;
        }

        // Recursive Step 1: Include nums_arr[index] in the current subset
        // Explore the next element with the updated bitwise OR
        dfs(index + 1, current_or | nums_arr[index]);

        // Recursive Step 2: Exclude nums_arr[index] from the current subset
        // Explore the next element with the current bitwise OR unchanged
        dfs(index + 1, current_or);
    }

public:
    int countMaxOrSubsets(std::vector<int>& nums) {
        // Initialize member variables
        nums_arr = nums; // Copy the input vector
        n = nums.size();
        max_or_val = 0;
        count = 0;

        // Step 1: Calculate the maximum possible bitwise OR.
        // This is simply the OR of all elements in the array.
        // Any subset's OR cannot exceed this value.
        for (int num : nums_arr) {
            max_or_val |= num;
        }

        // Step 2: Start the Depth-First Search (DFS) from the first element (index 0)
        // with an initial bitwise OR of 0 (representing an empty subset initially).
        dfs(0, 0);

        // The DFS logic correctly accounts for non-empty subsets.
        // An empty subset has an OR of 0. Since nums[i] >= 1, max_or_val will always be >= 1.
        // Therefore, the empty set will never be counted as its OR (0) will not match max_or_val.
        return count;
    }
};