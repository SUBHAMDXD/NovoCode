#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    long long maximumGain(string s, int x, int y) {
        long long total_points = 0;
        vector<char> stack1;
        vector<char> stack2;

        if (x >= y) {
            for (char c : s) {
                if (c == 'b' && !stack1.empty() && stack1.back() == 'a') {
                    total_points += x;
                    stack1.pop_back();
                } else {
                    stack1.push_back(c);
                }
            }
            for (char c : stack1) {
                if (c == 'a' && !stack2.empty() && stack2.back() == 'b') {
                    total_points += y;
                    stack2.pop_back();
                } else {
                    stack2.push_back(c);
                }
            }
        } else {
            for (char c : s) {
                if (c == 'a' && !stack1.empty() && stack1.back() == 'b') {
                    total_points += y;
                    stack1.pop_back();
                } else {
                    stack1.push_back(c);
                }
            }
            for (char c : stack1) {
                if (c == 'b' && !stack2.empty() && stack2.back() == 'a') {
                    total_points += x;
                    stack2.pop_back();
                } else {
                    stack2.push_back(c);
                }
            }
        }

        return total_points;
    }
};