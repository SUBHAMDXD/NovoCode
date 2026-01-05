class Solution {
    public long maxMatrixSum(int[][] matrix) {
        long sum = 0;
        int negativeCount = 0;
        int minAbs = Integer.MAX_VALUE;

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                int val = matrix[i][j];

                if (val < 0) {
                    negativeCount++;
                }

                int absVal = Math.abs(val);
                sum += absVal;
                minAbs = Math.min(minAbs, absVal);
            }
        }

        // If negatives are odd, one smallest absolute value must stay negative
        if (negativeCount % 2 == 1) {
            sum -= 2L * minAbs;
        }

        return sum;
    }
}
