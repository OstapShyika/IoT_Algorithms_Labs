#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

class Solution {
public:
    int path_number(vector<vector<char>> grid) {
        int res;
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
        unordered_map<char, vector<pair<int, int>>> m;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                m[grid[i][j]].push_back({i, j});
            }
        }
        for (int col = grid[0].size() - 1; col >= 0; col--) {
            for (int row = 0; row < grid.size(); row++) {
                if (col == grid[0].size() - 1 && (row == 0 || row == grid.size() - 1)) {
                    dp[row][col] = 1;
                }
                else if (col == grid[0].size() - 1 && !(row == 0 || row == grid.size() - 1)) {
                    continue;
                }
                else {
                    dp[row][col] += dp[row][col + 1];
                    char val = grid[row][col];
                    for (auto x: m[val]) {
                        if (x.second > col) {
                            dp[row][col] += dp[x.first][x.second];
                        }
                    }
                }
            }
        }
        for (int r = 0; r < grid.size(); r++) {
            res += dp[r][0];
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<char>> v{
            {'a', 'b', 'a'},
            {'z', 'a', 'x'},
            {'f', 'n', 'z'}
    };
    cout << s.path_number(v) << '\n';
    string line;
    ifstream infile("input.txt");
    if (infile) {
        vector<vector<char> > v1;
        while (getline(infile, line)) {
            vector<char> row;

            for (char c : line) {
                row.push_back(c);
            }

            v1.push_back(row);
        }
        cout << s.path_number(v1);
    }
    else {
        cout << "couldn`t open";
    }
    infile.close();
    return 0;
}
