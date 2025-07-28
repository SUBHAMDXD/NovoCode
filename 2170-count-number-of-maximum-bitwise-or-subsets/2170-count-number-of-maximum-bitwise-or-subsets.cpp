#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int max_or_val;
    int count;
    std::vector<int> nums_arr;
    int n;

    void dfs(int index, int current_or) {
        // Base case: If we have processed all elements
        if (index == n) {
            // Check if this subset's OR matches the maximum OR
            // We only count non-empty subsets implicitly by how we start the DFS or manage current_or.
            // A more robust way: if current_or is not 0 (meaning something was included) and it matches max_or.
            // However, the problem implies we are always looking for a subset whose OR is max_or.
            // The initial call will handle the empty set implicitly by not adding it to count.
            if (current_or == max_or_val) {
                count++;
            }
            return;
        }

        // Option 1: Include nums[index] in the current subset
        dfs(index + 1, current_or | nums_arr[index]);

        // Option 2: Exclude nums[index] from the current subset
        dfs(index + 1, current_or);
    }

    int countMaxOrSubsets(std::vector<int>& nums) {
        nums_arr = nums;
        n = nums.size();
        max_or_val = 0;
        count = 0;

        // Step 1: Find the maximum possible bitwise OR
        for (int num : nums) {
            max_or_val |= num;
        }

        // Step 2: Use DFS to count subsets.
        // We start with index 0 and initial_or 0.
        // The DFS will explore all 2^N subsets.
        dfs(0, 0);

        // The DFS counts all subsets including the empty set if max_or_val is 0.
        // However, max_or_val >= 1 since nums[i] >= 1.
        // If the empty set was somehow counted (it would have OR of 0),
        // and max_or_val was 0, it would be included.
        // Since max_or_val will always be >= 1 (as nums[i] >= 1), the empty set (OR = 0)
        // will never match max_or_val. So, the count will correctly reflect non-empty subsets.
        return count;
    }
};