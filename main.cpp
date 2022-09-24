#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct Cell {
    int x, y, distance;
    Cell(int x, int y, int distance) {
        this->x = x;
        this->y = y;
        this->distance = distance;
    }
};
class Maze {
public:
    const vector<pair<int, int>> DIR = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int shortest_path(vector<vector<int>> matrix, pair<int, int> start, pair<int, int> end) {
        if (matrix[start.first][start.second] == 0 || matrix[end.first][end.second] == 0) {
            return -1;
        }
        int r = matrix.size();
        int c = matrix[0].size();
        queue<Cell> q;
        q.emplace(Cell(start.first, start.second, 0));

        while (!q.empty()) {
            Cell curr = q.front();
            if (curr.x == end.first && curr.y == end.second) {
                return curr.distance;
            }
            q.pop();
            matrix[curr.x][curr.y] = 0;
            for (auto& x: DIR) {
                int nr = curr.x + x.first;
                int nc = curr.y + x.second;
                if (nr >= 0 && nr < r && nc >= 0 && nc < c && matrix[nr][nc] != 0) {
                    matrix[nr][nc] = 0;
                    q.emplace(Cell(nr, nc, curr.distance + 1));
                }
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}
