#include <string>
#include <vector>
#include <stack>

class Solution {
public:
    /**
     * @brief Removes the minimum number of parentheses to make the string valid.
     * @param s The input string with '(', ')', and lowercase letters.
     * @return A valid parentheses string.
     */
    std::string minRemoveToMakeValid(std::string s) {
        // Stack to store indices of open parentheses.
        std::stack<int> open_indices;
        // Vector to mark characters for removal.
        std::vector<bool> to_remove(s.length(), false);

        // Step 1: Identify invalid ')' and track open parentheses.
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                open_indices.push(i);
            } else if (s[i] == ')') {
                if (open_indices.empty()) {
                    // This ')' has no matching '('. Mark for removal.
                    to_remove[i] = true;
                } else {
                    // Matched with an open parenthesis.
                    open_indices.pop();
                }
            }
        }

        // Step 2: Any remaining indices in the stack are unclosed '('. Mark them.
        while (!open_indices.empty()) {
            to_remove[open_indices.top()] = true;
            open_indices.pop();
        }

        // Step 3: Build the final result string.
        std::string result = "";
        for (int i = 0; i < s.length(); ++i) {
            if (!to_remove[i]) {
                result += s[i];
            }
        }

        return result;
    }
};