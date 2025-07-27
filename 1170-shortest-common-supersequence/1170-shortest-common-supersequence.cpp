#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Finds the shortest string that has both str1 and str2 as subsequences.
     * @param str1 The first string.
     * @param str2 The second string.
     * @return The shortest common supersequence.
     */
    std::string shortestCommonSupersequence(std::string str1, std::string str2) {
        int m = str1.length();
        int n = str2.length();

        // Step 1: Build the DP table to find the length of the LCS.
        // dp[i][j] will store the length of the LCS of str1[0..i-1] and str2[0..j-1].
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

        // Step 2: Backtrack through the DP table to construct the SCS string.
        std::string scs = "";
        int i = m, j = n;
        while (i > 0 && j > 0) {
            // If the characters match, they are part of the LCS.
            // Add this character once to the result and move diagonally.
            if (str1[i - 1] == str2[j - 1]) {
                scs.push_back(str1[i - 1]);
                i--;
                j--;
            }
            // If characters don't match, move towards the larger DP value,
            // adding the character from the other string.
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                scs.push_back(str1[i - 1]);
                i--;
            } else {
                scs.push_back(str2[j - 1]);
                j--;
            }
        }

        // Step 3: Append any remaining characters from str1 or str2.
        while (i > 0) {
            scs.push_back(str1[i - 1]);
            i--;
        }
        while (j > 0) {
            scs.push_back(str2[j - 1]);
            j--;
        }

        // Step 4: The string was built backwards, so reverse it for the final answer.
        std::reverse(scs.begin(), scs.end());
        return scs;
    }
};