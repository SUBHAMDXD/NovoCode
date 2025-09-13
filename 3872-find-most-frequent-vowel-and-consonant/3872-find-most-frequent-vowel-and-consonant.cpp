#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxFreqSum(std::string s) {
        // Array to store frequency of each character ('a' through 'z').
        std::vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        int maxVowelFreq = 0;
        int maxConsonantFreq = 0;

        // Iterate through all 26 lowercase letters.
        for (int i = 0; i < 26; ++i) {
            char currentChar = 'a' + i;
            
            // Check if the character is a vowel.
            if (currentChar == 'a' || currentChar == 'e' || currentChar == 'i' || currentChar == 'o' || currentChar == 'u') {
                maxVowelFreq = std::max(maxVowelFreq, freq[i]);
            } else { // Otherwise, it's a consonant.
                maxConsonantFreq = std::max(maxConsonantFreq, freq[i]);
            }
        }

        return maxVowelFreq + maxConsonantFreq;
    }
};