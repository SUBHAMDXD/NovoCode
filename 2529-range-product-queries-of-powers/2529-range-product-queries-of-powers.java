import java.util.ArrayList;
import java.util.List;

class Solution {
    private final int MOD = 1_000_000_007;

    /**
     * Calculates (base^exp) % MOD efficiently.
     */
    private long power(long base, long exp) {
        long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    public int[] productQueries(int n, int[][] queries) {
        // Step 1: Find the exponents from the binary representation of n.
        List<Integer> exponents = new ArrayList<>();
        for (int i = 0; i < 31; ++i) {
            if (((n >> i) & 1) == 1) {
                exponents.add(i);
            }
        }

        // Step 2: Create a prefix sum array of the exponents.
        int m = exponents.size();
        long[] prefixSum = new long[m + 1];
        for (int i = 0; i < m; ++i) {
            prefixSum[i + 1] = prefixSum[i] + exponents.get(i);
        }

        // Step 3: Process each query.
        int[] answers = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int left = queries[i][0];
            int right = queries[i][1];

            // Find the sum of exponents in the range [left, right]
            long exponentSum = prefixSum[right + 1] - prefixSum[left];
            
            // The result is 2^exponentSum % MOD
            answers[i] = (int) power(2, exponentSum);
        }

        return answers;
    }
}