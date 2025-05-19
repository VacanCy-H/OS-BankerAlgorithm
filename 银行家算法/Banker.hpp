#pragma once
#include <vector>
#include <string>

class BankerAlgorithm {
public:
    BankerAlgorithm(int num_processes, int num_resources,
                    const std::vector<int>& available,
                    const std::vector<std::vector<int>>& alloc,
                    const std::vector<std::vector<int>>& need);

    // 处理资源请求
    bool request_resources(int pid, const std::vector<int>& request);

    // 打印当前系统状态
    void print_state() const;

private:
    int num_processes_;
    int num_resources_;
    std::vector<int> available_;
    std::vector<std::vector<int>> alloc_;
    std::vector<std::vector<int>> need_;

    // 检查请求是否合法（request <= need[pid] 且 request <= available）
    bool is_request_valid(int pid, const std::vector<int>& request) const;

    // 安全性检查算法
    bool is_safe_state() const;
};
