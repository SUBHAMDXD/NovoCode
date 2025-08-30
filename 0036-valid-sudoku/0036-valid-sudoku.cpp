#include <vector>

class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        bool rows[9][9] = {false};
        bool cols[9][9] = {false};
        bool boxes[9][9] = {false};

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }

                int num_index = board[i][j] - '1';
                int box_index = (i / 3) * 3 + (j / 3);

                if (rows[i][num_index] || cols[j][num_index] || boxes[box_index][num_index]) {
                    return false;
                }

                rows[i][num_index] = true;
                cols[j][num_index] = true;
                boxes[box_index][num_index] = true;
            }
        }

        return true;
    }
};