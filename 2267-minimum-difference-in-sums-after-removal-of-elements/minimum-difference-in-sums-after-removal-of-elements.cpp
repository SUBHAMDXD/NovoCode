#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

class Solution {
public:
    long long minimumDifference(std::vector<int>& nums) {
        // The total number of elements is 3 * n.
        int total_size = nums.size();
        int n = total_size / 3;

        /*
         * The core idea is to iterate through all possible split points.
         * For a split between index `i` and `i+1`:
         * - The first part of the final array is formed by the n smallest elements from `nums[0...i]`.
         * - The second part is formed by the n largest elements from `nums[i+1...3n-1]`.
         * We pre-calculate these sums for all possible prefixes and suffixes to find the minimum difference efficiently.
         */

        // Step 1: Calculate prefix minimum sums
        // prefix_min_sum[i] stores the sum of the n smallest elements in nums[0...i].
        std::vector<long long> prefix_min_sum(total_size);
        std::priority_queue<int> max_heap; // Max-heap to efficiently find the n smallest elements.
        long long current_sum = 0;

        for (int i = 0; i < total_size; ++i) {
            current_sum += nums[i];
            max_heap.push(nums[i]);

            // If the heap has more than n elements, remove the largest to maintain the n smallest.
            if (max_heap.size() > n) {
                current_sum -= max_heap.top();
                max_heap.pop();
            }

            // Store the sum once we have exactly n elements.
            if (max_heap.size() == n) {
                prefix_min_sum[i] = current_sum;
            }
        }

        // Step 2: Calculate suffix maximum sums
        // suffix_max_sum[i] stores the sum of the n largest elements in nums[i...3n-1].
        std::vector<long long> suffix_max_sum(total_size);
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap; // Min-heap to efficiently find the n largest elements.
        current_sum = 0;

        for (int i = total_size - 1; i >= 0; --i) {
            current_sum += nums[i];
            min_heap.push(nums[i]);

            // If the heap has more than n elements, remove the smallest to maintain the n largest.
            if (min_heap.size() > n) {
                current_sum -= min_heap.top();
                min_heap.pop();
            }
            
            // Store the sum once we have exactly n elements.
            if (min_heap.size() == n) {
                suffix_max_sum[i] = current_sum;
            }
        }

        // Step 3: Find the minimum difference across all valid split points
        long long min_difference = LLONG_MAX;

        // A valid split point `i` must be in the range [n-1, 2n-1].
        for (int i = n - 1; i < 2 * n; ++i) {
             long long first_part_sum = prefix_min_sum[i];
             long long second_part_sum = suffix_max_sum[i + 1];
             min_difference = std::min(min_difference, first_part_sum - second_part_sum);
        }

        return min_difference;
    }
};