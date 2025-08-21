#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<int> h(n, 0);  // histogram heights
        int res = 0;

        for (int i = 0; i < m; i++) {
            // Build histogram row by row
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) h[j] = 0;
                else h[j] += 1;
            }

            // Use stack to count rectangles with row i as bottom
            stack<int> st;
            vector<int> sum(n, 0);

            for (int j = 0; j < n; j++) {
                while (!st.empty() && h[st.top()] >= h[j]) {
                    st.pop();
                }

                if (!st.empty()) {
                    int prev = st.top();
                    sum[j] = sum[prev] + h[j] * (j - prev);
                } else {
                    sum[j] = h[j] * (j + 1);
                }

                res += sum[j];
                st.push(j);
            }
        }

        return res;
    }
};
