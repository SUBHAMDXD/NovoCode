class Solution {
public:
    bool isPowerOfThree(int n) {
        // 1162261467 is 3^19, the largest power of 3 that fits in a signed 32-bit integer.
        return (n > 0) && (1162261467 % n == 0);
    }
};
