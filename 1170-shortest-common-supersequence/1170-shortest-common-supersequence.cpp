#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Finds the shortest common supersequence of two strings.
     * * This function uses dynamic programming to find the longest common subsequence (LCS)
     * and then backtracks through the DP table to construct the shortest common
     * supersequence (SCS).
     * * @param str1 The first string.
     * @param str2 The second string.
     * @return The shortest string that has both str1 and str2 as subsequences.
     */
    std::string shortestCommonSupersequence(std::string str1, std::string str2) {
        int m = str1.length();
        int n = str2.length();

        // Step 1: Fill DP table to find the length of the LCS.
        // dp[i][j] stores the length of the LCS of str1[0..i-1] and str2[0..j-1].
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Step 2: Backtrack through the DP table to construct the SCS.
        std::string scs = "";
        int i = m, j = n;
        while (i > 0 && j > 0) {
            // If characters are the same, they are part of the LCS.
            // Add the character once and move diagonally.
            if (str1[i - 1] == str2[j - 1]) {
                scs += str1[i - 1];
                i--;
                j--;
            } 
            // If not same, find which character is not part of the LCS path.
            // Move in the direction of the larger DP value.
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                scs += str1[i - 1]; // Add the character from str1
                i--;
            } else {
                scs += str2[j - 1]; // Add the character from str2
                j--;
            }
        }

        // Step 3: Add any remaining characters from str1 or str2.
        while (i > 0) {
            scs += str1[i - 1];
            i--;
        }
        while (j > 0) {
            scs += str2[j - 1];
            j--;
        }

        // Step 4: The string is built backwards, so reverse it.
        std::reverse(scs.begin(), scs.end());
        return scs;
    }
};