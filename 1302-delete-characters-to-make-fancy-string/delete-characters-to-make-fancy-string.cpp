class Solution {
public:
    string makeFancyString(string s) {
        if (s.length() <= 2) {
            return s;
        }
        
        string result;
        result.push_back(s[0]);  // First character is always included
        result.push_back(s[1]);  // Second character is always included
        
        // Start from the third character
        for (int i = 2; i < s.length(); i++) {
            // Check if current character would create three consecutive identical chars
            if (s[i] != result[result.length() - 1] || 
                s[i] != result[result.length() - 2]) {
                result.push_back(s[i]);
            }
            // If s[i] == result.back() == result[result.length() - 2], skip this character
        }
        
        return result;
    }
};
