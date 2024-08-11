#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

// Maximum 32 bit value
#define MAX_UINT32 4294967295

// Cell used for pathfinding
struct Cell {
    int idx;
    int x;
    int y;
    uint_fast8_t flag = 0; // 0 = none, 1 = open, 2 = closed

    uint_fast32_t gCost = MAX_UINT32;
    uint_fast32_t hCost = 0;
    uint_fast32_t fCost = MAX_UINT32;
};

// Helper for getting index from x and y
inline int getIdx(int x, int y, int width) {
    return x + y * width;
}

// Distance on a grid using only cardinal directions
uint_fast32_t manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int main(int argc, const char** argv) {
    if (argc != 2) return 1; // Require file to be passed

    int width = 0;
    int height = 0;

    // Stores the length or 'cost' of each room
    auto costs = std::vector<uint_fast32_t>();

    // Parse Input
    std::ifstream input_file(argv[1]);
    std::string line;
    // Loop through file
    while (getline(input_file, line)) {
        for (const char c : line) {
            costs.push_back(c - '0');
        }
        width = line.length();
        ++height;
    }

    // Initialization
    auto cells = std::make_unique<Cell[]>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int idx = getIdx(x, y, width);
            cells[idx].idx = idx;
            cells[idx].x = x;
            cells[idx].y = y;
        }
    }

    int target_idx = width * height - 1;

    auto compare = [&cells](int &a, int &b) { return cells[a].fCost > cells[b].fCost; };
    std::priority_queue<int, std::vector<int>, decltype(compare)> open(compare);

    // Pathfinding
    cells[0].gCost = costs[0];
    cells[0].fCost = cells[0].gCost + cells[0].hCost;
    open.push(0);
    cells[0].flag = 1;

    while (!open.empty()) {
        const Cell curr = cells[open.top()];

        if (curr.idx == target_idx) break;

        open.pop();

        cells[0].flag = 2;

        const int right_idx = curr.idx + 1;
        const int left_idx = curr.idx - 1;
        const int up_idx = curr.idx - width;
        const int down_idx = curr.idx + width;

        if (curr.x > 0 && cells[left_idx].flag != 2) {
            uint_fast32_t newGCost = curr.gCost + costs[left_idx];
            if (newGCost < cells[left_idx].gCost) {
                cells[left_idx].gCost = newGCost;
                cells[left_idx].hCost = manhattanDistance(curr.x - 1, curr.y, width - 1, height - 1);
                cells[left_idx].fCost = cells[left_idx].gCost + cells[left_idx].hCost;

                if (cells[left_idx].flag != 1) {
                    open.push(left_idx);
                    cells[left_idx].flag = 1;
                }
            }
        }
        if (curr.x < width - 1 && cells[right_idx].flag != 2) {
            uint_fast32_t newGCost = curr.gCost + costs[right_idx];
            if (newGCost < cells[right_idx].gCost) {
                cells[right_idx].gCost = newGCost;
                cells[right_idx].hCost = manhattanDistance(curr.x + 1, curr.y, width - 1, height - 1);
                cells[right_idx].fCost = cells[right_idx].gCost + cells[right_idx].hCost;

                if (cells[right_idx].flag != 1) {
                    open.push(right_idx);
                    cells[right_idx].flag |= 1;
                }
            }
        }
        if (curr.y > 0 && cells[up_idx].flag != 2) {
            uint_fast32_t newGCost = curr.gCost + costs[up_idx];
            if (newGCost < cells[up_idx].gCost) {
                cells[up_idx].gCost = newGCost;
                cells[up_idx].hCost = manhattanDistance(curr.x, curr.y - 1, width - 1, height - 1);
                cells[up_idx].fCost = cells[up_idx].gCost + cells[up_idx].hCost;

                if (cells[up_idx].flag != 1) {
                    open.push(up_idx);
                    cells[up_idx].flag = 1;
                }
            }
        }
        if (curr.y < height - 1 && cells[down_idx].flag != 2) {
            uint_fast32_t newGCost = curr.gCost + costs[down_idx];
            if (newGCost < cells[down_idx].gCost) {
                cells[down_idx].gCost = newGCost;
                cells[down_idx].hCost = manhattanDistance(curr.x, curr.y + 1, width - 1, height - 1);
                cells[down_idx].fCost = cells[down_idx].gCost + cells[down_idx].hCost;

                if (cells[down_idx].flag != 1) {
                    open.push(down_idx);
                    cells[down_idx].flag = 1;
                }
            }
        }
    }

    std::cout << cells[target_idx].fCost << std::endl;

    return 0;
}