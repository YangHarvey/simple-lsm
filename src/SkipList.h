#pragma once

#include <string>
#include <cstddef>
#include <memory>
#include <random>
#include <utility>
#include <vector>

#include "config.h"

// 并发跳表
class SkipList {
public:
    explicit SkipList(size_t max_size = SKIPLIST_MAX_SIZE, size_t max_height = SKIPLIST_MAX_HEIGHT);
    
    ~SkipList();

    // basic functions
    void put(const std::string &key, const std::string &value);
    
    std::pair<bool, std::string> get(const std::string &key) const;
    
    bool del(const std::string &key);
    
    std::vector<std::pair<std::string, std::string>> get_range(const std::string &lower_key, const std::string &upper_key) const;
    
    std::vector<std::pair<std::string, std::string>> get_all() const;

    // skiplist state
    inline bool is_empty() const { return num_entries_ == 0; }

    inline size_t num_bytes() const { return num_bytes_; }
    inline size_t num_entries() const { return num_entries_; }

    const std::string get_min_key() const;
    const std::string get_max_key() const;

private:
    // SkipList::Node
    struct Node {
        std::string key_;
        std::string value_;
        size_t height_ = 0;
        Node **nexts_;
        explicit Node(const std::string &key, const std::string &value, size_t height) 
            : key_(std::move(key)), value_(std::move(value)), height_(height){
            nexts_ = new Node * [height];
        }
        Node() = delete;
        ~Node() {
            delete [] nexts_;
        }
    };

    Node *head_, *tail_;    // head_, tail_不保存数据, key, value = "", ""

    size_t max_size_ = SKIPLIST_MAX_SIZE;
    size_t max_height_ = SKIPLIST_MAX_HEIGHT;

    // meta data
    size_t num_entries_ = 0;
    size_t num_bytes_ = 0;

    // 随机数生成
    std::default_random_engine engine_;
    std::uniform_int_distribution<int> dist_;
    // 生成随机level
    size_t random_height();

    // 找到第一个大于等于当前key的节点
    Node *findGreatorOrEqual(const std::string &key, Node **prevs) const;
};



