class Solution {
    public int numSub(String s) {
        long MOD = 1000000007L;
        long count = 0;   // current run of consecutive '1's
        long ans = 0;

        for (char c : s.toCharArray()) {
            if (c == '1') {
                count++;
                ans = (ans + count) % MOD;
            } else {
                count = 0;
            }
        }
        return (int) ans;
    }
}
