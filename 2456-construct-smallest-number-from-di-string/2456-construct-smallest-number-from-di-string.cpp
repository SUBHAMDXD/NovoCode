class Solution {
public:
    string smallestNumber(string pattern) {
        return dfs(0, 0, 0, pattern);
    }

private:
    string dfs(int index, int last, int mask, const string& pattern) {
        int n = pattern.size();
        if (index == n + 1) {
            return "";
        }
        for (int d = 1; d <= 9; d++) {
            if (mask & (1 << d)) {
                continue;
            }
            if (index > 0) {
                if (pattern[index - 1] == 'I' && d < last) {
                    continue;
                }
                if (pattern[index - 1] == 'D' && d > last) {
                    continue;
                }
            }
            string res = dfs(index + 1, d, mask | (1 << d), pattern);
            if (res != "!") {
                return string(1, '0' + d) + res;
            }
        }
        return "!";
    }
};