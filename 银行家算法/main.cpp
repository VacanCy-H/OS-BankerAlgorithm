#include "Banker.hpp"
#include <vector>
#include <iostream>

int main() {
    // 初始化测试数据（题目中的示例）
    const int n = 5, m = 3;
    std::vector<int> available = {2, 3, 3};
    std::vector<std::vector<int>> alloc = {
        {2, 1, 2},  // P1
        {4, 0, 2},  // P2
        {3, 0, 5},  // P3
        {2, 0, 4},  // P4
        {3, 1, 4}   // P5
    };
    std::vector<std::vector<int>> need = {
        {3, 4, 7},  // P1
        {1, 3, 4},  // P2
        {0, 0, 3},  // P3
        {2, 2, 1},  // P4
        {1, 1, 0}   // P5
    };

    BankerAlgorithm banker(n, m, available, alloc, need);
    banker.print_state();

    // 测试请求序列
    std::vector<std::pair<int, std::vector<int>>> requests = {
        {1, {0, 3, 4}},   // 请求 a: P2 (注意索引从0开始)
        {3, {1, 0, 1}},   // 请求 b: P4
        {0, {2, 0, 1}},   // 请求 c: P1
        {2, {0, 0, 2}}    // 请求 d: P3
    };

    for (const auto& req : requests) {
        int pid = req.first;
        std::vector<int> request = req.second;
        std::cout << "\n处理请求: P" << pid << " 请求资源 (";
        for (int val : request) std::cout << val << " ";
        std::cout << ")\n";
        bool success = banker.request_resources(pid, request);
        if (success) banker.print_state();
    }

    return 0;
}
