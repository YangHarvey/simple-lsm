#include "SkipList.h"

// Constructor
SkipList::SkipList(size_t max_size, size_t max_height)
    : max_size_(max_size), max_height_(max_height), dist_(0, 1)
{
    // Initialize head and tail nodes
    head_ = new Node("", "", max_height_);
    tail_ = new Node("", "", max_height_);

    // Connect head and tail nodes at all levels
    for (size_t level = 0; level < max_height_; level++) {
        head_->nexts_[level] = tail_;
        tail_->nexts_[level] = nullptr;
    }

    // 初始化state
    num_bytes_ = 0;
    num_entries_ = 0;
}

// Destructor
SkipList::~SkipList()
{
    // Delete all nodes in the skip list
    Node* current = head_->nexts_[0];
    while (current != tail_) {
        Node* tmp = current;
        current = current->nexts_[0];
        delete tmp;
    }

    // Delete head and tail nodes
    delete head_;
    delete tail_;
}

// Put key-value pair into the skip list
void SkipList::put(const std::string& key, const std::string& value)
{
    // 1 取对应key的node
    Node *prevs[max_height_];
    auto node = findGreatorOrEqual(key, prevs);

    // 2.1 如果SkipList里已经存在该key，那么只需要更新value
    if(node != tail_ && node->key_ == key) {
        num_bytes_ = num_bytes_ + value.size() - node->value_.size();
        node->value_ = value;
        return ;
    }

    // 2.2 如果SkipList中不存在该key，那么需要创建一个新的Node
    size_t height = random_height();
    auto new_node = new Node(key, value, height);
    // 修改指针
    for(size_t i = 0; i < height; i++) {
        new_node->nexts_[i] = prevs[i]->nexts_[i];
        prevs[i]->nexts_[i] = new_node;
    }

    num_bytes_ = num_bytes_ + key.size() + value.size();
    num_entries_++;
    return ;
}

// Get value associated with the key from the skip list
std::pair<bool, std::string> SkipList::get(const std::string& key) const
{
    // 1 先取对应key所在的节点
    auto node = findGreatorOrEqual(key, nullptr);
    
    // 2.1 找到对应key
    if(node != tail_ && node->key_ == key) {
        return {true, node->value_};
    }

    // 2.2 没有找到对应key
    return {false, ""};
}

// Delete key-value pair from the skip list
bool SkipList::del(const std::string& key)
{
    // 1 先取对应key所在的节点
    Node* prevs[max_height_];
    auto node = findGreatorOrEqual(key, prevs);

    // 2.1 找到对应key，删除节点
    if(node != tail_ && node->key_ == key) {
        for(size_t i = 0; i < node->height_; i++) {
            prevs[i]->nexts_[i] = node->nexts_[i];
        }
        num_bytes_ = num_bytes_ - node->key_.size() - node->value_.size();
        num_entries_--;
        delete node;

        return true;
    }

    // 2.2 没有找到对应的key, return false
    return false;
}

// Get key-value pairs within the given range from the skip list
std::vector<std::pair<std::string, std::string>> SkipList::get_range(const std::string& lower_key, const std::string& upper_key) const
{
    // 0. prepare
    std::vector<std::pair<std::string, std::string>> results;
    // 1. find the first node
    auto first_node = findGreatorOrEqual(lower_key, nullptr);
    // 2. scan the skiplist
    auto current_node = first_node;
    while(current_node != tail_ && current_node->key_ <= upper_key) {
        results.push_back({current_node->key_, current_node->value_});
        current_node = current_node->nexts_[0];
    }
    return results;
}

// Get all key-value pairs from the skip list
std::vector<std::pair<std::string, std::string>> SkipList::get_all() const
{
    std::vector<std::pair<std::string, std::string>> results;

    auto current_node = head_->nexts_[0];
    while(current_node != tail_) {
        results.push_back({current_node->key_, current_node->value_});
        current_node = current_node->nexts_[0];
    }

    return results;
}

// Get the minimum key in the skip list
const std::string SkipList::get_min_key() const
{
    auto first_node = head_->nexts_[0];
    if(first_node != tail_) {
        return first_node->key_;
    }
    return "";
}

// Get the maximum key in the skip list
const std::string SkipList::get_max_key() const
{
    auto node = head_;
    auto height = max_height_ - 1;
    while(true) {
        auto next = node->nexts_[height];
        while(next != tail_) {
            node = next;
            next = node->nexts_[height];
        }
        if(height == 0) {
            return node->key_;
        }else {
            height--;
        }
    }
}

// 生成随机level
size_t SkipList::random_height() {
    size_t rh = 1;
    while(rh < max_height_ && dist_(engine_)) {
        rh++;
    }
    return rh;
}

// 找到第一个大于等于当前key的节点
SkipList::Node *SkipList::findGreatorOrEqual(const std::string &key, Node **prevs) const {
    auto node = head_;
    int height = max_height_ - 1;
    while(true) {
        // 在本层步进
        auto next = node->nexts_[height];
        while(next != tail_ && next->key_ < key) {
            node = next;
            next = node->nexts_[height];
        }
        if(prevs != nullptr) {
            prevs[height] = node;
        }

        if(height != 0) {
            height--;
        }else {
            return next;
        }
    }
}