#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_map<int,int> pos;
        long windowSum = 0, maxSum = 0;
        int left = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            int v = nums[right];
            if (pos.count(v) && pos[v] >= left) {
                int dupIdx = pos[v];
                while (left <= dupIdx) {
                    windowSum -= nums[left];
                    ++left;
                }
            }
            windowSum += v;
            pos[v] = right;
            maxSum = max(maxSum, windowSum);
        }
        return static_cast<int>(maxSum);
    }
};
