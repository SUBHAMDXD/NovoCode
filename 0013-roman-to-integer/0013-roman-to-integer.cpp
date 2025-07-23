#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> romanValues = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        
        int total = 0;
        for (int i = 0; i < s.size(); ++i) {
            int currentValue = romanValues[s[i]];
            int nextValue = (i + 1 < s.size()) ? romanValues[s[i + 1]] : 0;
            
            if (currentValue < nextValue) {
                total -= currentValue;
            } else {
                total += currentValue;
            }
        }
        return total;
    }
};