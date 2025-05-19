#include "Banker.hpp"
#include <algorithm>
#include <iostream>

BankerAlgorithm::BankerAlgorithm(int num_processes, int num_resources,
                                 const std::vector<int>& available,
                                 const std::vector<std::vector<int>>& alloc,
                                 const std::vector<std::vector<int>>& need)
    : num_processes_(num_processes), num_resources_(num_resources),
      available_(available), alloc_(alloc), need_(need) {}

bool BankerAlgorithm::is_request_valid(int pid, const std::vector<int>& request) const {
    // 检查请求是否超过进程需求
    for (int i = 0; i < num_resources_; ++i) {
        if (request[i] > need_[pid][i]) {
            return false;
        }
    }
    // 检查请求是否超过可用资源
    for (int i = 0; i < num_resources_; ++i) {
        if (request[i] > available_[i]) {
            return false;
        }
    }
    return true;
}

bool BankerAlgorithm::request_resources(int pid, const std::vector<int>& request) {
    if (!is_request_valid(pid, request)) {
        std::cerr << "非法请求: 进程 P" << pid << " 请求超过需求或可用资源\n";
        return false;
    }

    // 试探性分配
    std::vector<int> old_available = available_;
    std::vector<std::vector<int>> old_alloc = alloc_;
    std::vector<std::vector<int>> old_need = need_;

    for (int i = 0; i < num_resources_; ++i) {
        available_[i] -= request[i];
        alloc_[pid][i] += request[i];
        need_[pid][i] -= request[i];
    }

    if (!is_safe_state()) {
        // 恢复原状态
        available_ = old_available;
        alloc_ = old_alloc;
        need_ = old_need;
        std::cerr << "请求导致系统不安全，已回滚\n";
        return false;
    }

    std::cout << "资源分配成功，系统仍处于安全状态\n";
    return true;
}

bool BankerAlgorithm::is_safe_state() const {
    std::vector<int> work = available_;
    std::vector<bool> finish(num_processes_, false);
    std::vector<int> safe_sequence;

    for (int count = 0; count < num_processes_; ++count) {
        bool found = false;
        for (int i = 0; i < num_processes_; ++i) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < num_resources_; ++j) {
                    if (need_[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < num_resources_; ++j) {
                        work[j] += alloc_[i][j];
                    }
                    finish[i] = true;
                    safe_sequence.push_back(i);
                    found = true;
                    break;
                }
            }
        }
        if (!found) break;
    }

    // 输出安全序列（调试用）
    if (safe_sequence.size() == static_cast<size_t>(num_processes_)) {
        std::cout << "安全序列: ";
        for (int pid : safe_sequence) std::cout << "P" << pid << " ";
        std::cout << "\n";
        return true;
    } else {
        return false;
    }
}

void BankerAlgorithm::print_state() const {
    std::cout << "可用资源: ";
    for (int res : available_) std::cout << res << " ";
    std::cout << "\n分配矩阵:\n";
    for (const auto& row : alloc_) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
    std::cout << "需求矩阵:\n";
    for (const auto& row : need_) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
}
