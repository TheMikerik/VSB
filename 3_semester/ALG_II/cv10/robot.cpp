#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > board = {
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 1}
};




int maxCoins(vector<vector<int>> &board) {
    int n = board.size();
    int m = board[0].size();

    vector<vector<int>> tmp_board;
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < m; ++j) {
            row.push_back(0);
        }
        tmp_board.push_back(row);
    }

    for (int i = 1; i < n; i++) {
        tmp_board[i][0] = tmp_board[i - 1][0] + board[i][0];
    }

    for (int j = 1; j < m; j++) {
        tmp_board[0][j] = tmp_board[0][j - 1] + board[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            tmp_board[i][j] = max(tmp_board[i - 1][j], tmp_board[i][j - 1]) + board[i][j];
        }
    }

    return tmp_board[n - 1][m - 1];
}

int main() {
    int result = maxCoins(board);

    cout << "On the best path robot can collect " << result << " coins";

    return 0;
}
