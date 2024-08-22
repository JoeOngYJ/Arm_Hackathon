#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <ostream>

int main(int argc, const char** argv) {
    if (argc != 2) return 1;

    int file_count = 0;
    int max_depth = -1;
    std::string max_depth_path;
    int depth_sum = 0;

    std::string path = "";
    int depth = 0;

    std::ifstream input_file(argv[1], std::ios::in | std::ios::binary);
    std::string line;
    while (getline(input_file, line)) {
        if (line[2] == 'l' || line[2] == 'r') continue;
        if (line[2] == 'c') {
            if (line[5] == '.') {
                path = path.substr(0, path.find_last_of('/'));
                --depth;
            } else if (line[5] == '/') {
                path = "";
                depth = 0;
            } else {
                path = path + "/" + line.substr(5);
                ++depth;
            }
        } else {
            depth_sum += depth;
            if (depth > max_depth) {
                max_depth = depth;
                max_depth_path = path;
            }
            ++file_count;
        }
    }

    std::cout << file_count << ",\"/" << max_depth_path << "\"," << (float)depth_sum / file_count << std::endl;
    
    return 0;
}