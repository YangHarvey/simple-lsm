#include <gtest/gtest.h>
#include <unordered_map>
#include <random>
#include <ctime>
#include "SkipList.h"

// 测试套件类
class SkipListTest : public ::testing::Test {
protected:
    // 在每个测试用例之前执行的操作
    void SetUp() override {
        // 添加设置代码，如果有的话
    }

    // 在每个测试用例之后执行的操作
    void TearDown() override {
        // 添加清理代码，如果有的话
    }

    std::string generateRandomString(int length) {
        std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string randomString;

        // 设置种子以获取不同的随机序列
        std::srand(std::time(0));

        for (int i = 0; i < length; ++i) {
            randomString += chars[std::rand() % chars.length()];
        }

        return randomString;
    }
};

// 编写测试用例
TEST_F(SkipListTest, BasicTest1) {
    auto skiplist_ = new SkipList();
    // 1. before insert data
    ASSERT_EQ(skiplist_->num_bytes(), 0);
    ASSERT_EQ(skiplist_->num_entries(), 0);
    ASSERT_EQ(skiplist_->get_all().size(), 0);
    ASSERT_EQ(skiplist_->get_min_key(), "");
    ASSERT_EQ(skiplist_->get_max_key(), "");
    ASSERT_EQ(skiplist_->is_empty(), true);

    // 2. test insert
    {
        std::string key = "key", value = "value";
        skiplist_->put(key, value);
        auto result = skiplist_->get(key);
        ASSERT_EQ(true, result.first);
        ASSERT_EQ(value, result.second);

        ASSERT_EQ(skiplist_->num_entries(), 1);
        ASSERT_EQ(skiplist_->num_bytes(), key.size() + value.size());
        ASSERT_EQ(skiplist_->get_min_key(), key);
        ASSERT_EQ(skiplist_->get_max_key(), key);
        ASSERT_EQ(skiplist_->is_empty(), false);
        
        auto kvpairs = skiplist_->get_all();
        ASSERT_EQ(kvpairs.size(), 1);
    }

    {
        std::string key = "false_key";
        auto result = skiplist_->get(key);
        ASSERT_EQ(false, result.first);
        ASSERT_EQ(std::string(""), result.second);
    } 

    {
        std::string key = "key";
        auto result = skiplist_->del(key);
        ASSERT_EQ(result, true);

        ASSERT_EQ(skiplist_->num_entries(), 0);
        ASSERT_EQ(skiplist_->num_bytes(), 0);
        ASSERT_EQ(skiplist_->get_min_key(), "");
        ASSERT_EQ(skiplist_->get_max_key(), "");
        ASSERT_EQ(skiplist_->is_empty(), true);
        
        auto kvpairs = skiplist_->get_all();
        ASSERT_EQ(kvpairs.size(), 0);
    }
   
    delete skiplist_;
}

TEST_F(SkipListTest, BasicTest2) {
    // std::unordered_map<std::string, std::string> map;
    // size_t num_items = 10000;
    // size_t num_bytes = 0;
    // std::string max_key;
    // std::string min_key;
    // for(size_t i = 0; i < num_items; i++) {
    //     std::srand(std::time(0));
    //     int key_length = std::rand() % 100;
    //     int value_length = std::rand() % 100;
    //     std::string key = generateRandomString(key_length);
    //     std::string value = generateRandomString(value_length);
    //     map.emplace(key, value);
    //     skiplist_->put(key, value);

    //     num_bytes = num_bytes + key_length + value_length;

    //     if(i == 0) {
    //         min_key = key;
    //         max_key = key;
    //     }else {
    //         if(key > max_key) {
    //             max_key = key;
    //         }
    //         if(key < min_key) {
    //             min_key = key;
    //         }
    //     }
    // }
    // // test basic api
    // ASSERT_EQ(skiplist_->is_empty(), false);
    // ASSERT_EQ(skiplist_->num_entries(), map.size());
    // ASSERT_EQ(skiplist_->num_bytes(), num_bytes);
    // ASSERT_EQ(skiplist_->get_min_key(), min_key);
    // ASSERT_EQ(skiplist_->get_min_key(), min_key);

    // // test get_all
    // auto kvpairs = skiplist_->get_all();
    // ASSERT_EQ(kvpairs.size(), num_items);
    // for(size_t i = 0; i < kvpairs.size(); i++) {
    //     ASSERT_EQ(kvpairs[i].second, map[kvpairs[i].first]);
    // }

    // // test get
    // for(const auto& pair : map) {
    //     const std::string &key = pair.first;
    //     const std::string &value = pair.second;
    //     ASSERT_EQ(skiplist_->get(key), std::make_pair(true, value));
    // }
}


TEST_F(SkipListTest, TestCase2) {
    // 编写测试逻辑和断言
    EXPECT_EQ(2, 1 + 1);
}

// 定义主函数以运行测试
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
