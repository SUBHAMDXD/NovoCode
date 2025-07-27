#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Maximizes the longest continuous free time by rescheduling at most k meetings.
     * @param eventTime The total duration of the event.
     * @param k The maximum number of meetings that can be rescheduled.
     * @param startTime A vector of meeting start times.
     * @param endTime A vector of meeting end times.
     * @return The maximum possible continuous free time.
     */
    long long maxFreeTime(int eventTime, int k, std::vector<int>& startTime, std::vector<int>& endTime) {
        int n = startTime.size();

        // Step 1: Calculate all initial free time slots (gaps).
        // There are n meetings, resulting in n+1 potential gaps.
        std::vector<long long> gaps;
        gaps.reserve(n + 1);

        // Gap before the first meeting: [0, startTime[0]]
        gaps.push_back(startTime[0]);

        // Gaps between consecutive meetings: [endTime[i-1], startTime[i]]
        for (int i = 1; i < n; ++i) {
            gaps.push_back(static_cast<long long>(startTime[i]) - endTime[i - 1]);
        }

        // Gap after the last meeting: [endTime[n-1], eventTime]
        gaps.push_back(static_cast<long long>(eventTime) - endTime[n - 1]);

        // Step 2: Use a sliding window to find the max sum of k+1 consecutive gaps.
        // Moving 'k' meetings allows us to merge k+1 adjacent gaps.
        int windowSize = k + 1;
        long long currentSum = 0;

        // Initialize the sum for the first window of size k+1
        for (int i = 0; i < windowSize; ++i) {
            currentSum += gaps[i];
        }

        long long maxSum = currentSum;

        // Slide the window across the rest of the array
        for (int i = windowSize; i < gaps.size(); ++i) {
            // Update the window sum efficiently
            currentSum += gaps[i] - gaps[i - windowSize];
            maxSum = std::max(maxSum, currentSum);
        }

        return maxSum;
    }
};