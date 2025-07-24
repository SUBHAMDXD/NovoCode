#include <vector>

class Solution {
public:
    int numOfSubarrays(std::vector<int>& arr) {
        int odd_count = 0;
        int even_count = 1; // Starts at 1 for the empty prefix sum (0 is even)
        long long result = 0;
        int current_sum = 0;
        int MOD = 1e9 + 7;

        for (int num : arr) {
            current_sum += num;
            if (current_sum % 2 != 0) { // Current prefix sum is odd
                result = (result + even_count) % MOD;
                odd_count++;
            } else { // Current prefix sum is even
                result = (result + odd_count) % MOD;
                even_count++;
            }
        }
        return result;
    }
};