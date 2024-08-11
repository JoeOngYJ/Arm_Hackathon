#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

#define MAX_UINT32 4294967295

struct Cell {
    int idx;
    int x;
    int y;

    uint32_t gCost = MAX_UINT32;
    uint32_t hCost = 0;
    uint32_t fCost = MAX_UINT32;
};

inline int getIdx(int x, int y, int width) {
    return x + y * width;
}

inline int getX(int idx, int width) {
    return idx % width;
}

inline int getY(int idx, int width) {
    return idx / width;
}

inline uint32_t manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int main(int argc, const char** argv) {

    int width = 0;
    int height = 0;
    auto costs = std::vector<uint32_t>();
    // Parse Input
    std::ifstream input_file(argv[1]);
    std::string line;
    while (getline(input_file, line)) {
        for (const char c : line) {
            costs.push_back(c - '0');
        }
        width = line.length();
        ++height;
    }

    // Initialization
    auto cells = std::vector<Cell>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int idx = getIdx(x, y, width);
            cells[idx].idx = idx;
            cells[idx].x = x;
            cells[idx].y = y;
        }
    }

    int target_idx = width * height - 1;

    auto compare = [&cells](int &a, int &b) {
        return cells[a].fCost < cells[b].fCost;
    };
    std::priority_queue<int, std::vector<int>, decltype(compare)> open(compare);
    auto open_set = std::unordered_set<int>();
    auto closed = std::unordered_set<int>();

    // Pathfinding
    cells[0].gCost = costs[0];
    cells[0].fCost = cells[0].gCost + cells[0].hCost;
    open.push(0);
    open_set.insert(0);

    while (!open.empty()) {
        const Cell curr = cells[open.top()];

        if (curr.idx == target_idx) break;

        open.pop();
        open_set.erase(curr.idx);

        closed.insert(curr.idx);

        const int right_idx = curr.idx + 1;
        const int left_idx = curr.idx - 1;
        const int up_idx = curr.idx - width;
        const int down_idx = curr.idx + width;

        if (curr.x > 0 && !closed.contains(left_idx)) {
            uint32_t newGCost = curr.gCost + costs[left_idx];
            if (newGCost < cells[left_idx].gCost) {
                cells[left_idx].gCost = newGCost;
                cells[left_idx].hCost = manhattanDistance(curr.x - 1, curr.y, width - 1, height - 1);
                cells[left_idx].fCost = cells[left_idx].gCost + cells[left_idx].hCost;

                if (!open_set.contains(left_idx)) {
                    open.push(left_idx);
                    open_set.insert(left_idx);
                }
            }
        }
        if (curr.x < width - 1 && !closed.contains(right_idx)) {

            uint32_t newGCost = curr.gCost + costs[right_idx];
            if (newGCost < cells[right_idx].gCost) {
                cells[right_idx].gCost = newGCost;
                cells[right_idx].hCost = manhattanDistance(curr.x + 1, curr.y, width - 1, height - 1);
                cells[right_idx].fCost = cells[right_idx].gCost + cells[right_idx].hCost;

                if (!open_set.contains(right_idx)) {
                    open.push(right_idx);
                    open_set.insert(right_idx);
                }
            }
        }
        if (curr.y > 0 && !closed.contains(up_idx)) {
            uint32_t newGCost = curr.gCost + costs[up_idx];
            if (newGCost < cells[up_idx].gCost) {
                cells[up_idx].gCost = newGCost;
                cells[up_idx].hCost = manhattanDistance(curr.x, curr.y - 1, width - 1, height - 1);
                cells[up_idx].fCost = cells[up_idx].gCost + cells[up_idx].hCost;

                if (!open_set.contains(up_idx)) {
                    open.push(up_idx);
                    open_set.insert(up_idx);
                }
            }
        }
        if (curr.y < height - 1 && !closed.contains(down_idx)) {

            uint32_t newGCost = curr.gCost + costs[down_idx];
            if (newGCost < cells[down_idx].gCost) {
                cells[down_idx].gCost = newGCost;
                cells[down_idx].hCost = manhattanDistance(curr.x, curr.y + 1, width - 1, height - 1);
                cells[down_idx].fCost = cells[down_idx].gCost + cells[down_idx].hCost;

                if (!open_set.contains(down_idx)) {
                    open.push(down_idx);
                    open_set.insert(down_idx);
                }
            }
        }
    }

    std::cout << cells[target_idx].fCost << std::endl;

    return 0;
}