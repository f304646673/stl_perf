#ifndef TEST_INSERT_BEGIN_MID_END_H
#define TEST_INSERT_BEGIN_MID_END_H
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <functional> 

#include "perftool.h"

template<class T>
void insert_map_begin(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = count; i > 0; i--) {
        container.insert({ i, i });
        perftool.record();
    }
}

template<class T>
void insert_map_mid(size_t count, PerfTool& perftool) {
    T container;
    container.insert({ 0, 0 });
    container.insert({ 2 * count, 2 * count }); 
    for (size_t i = 1; i < count + 1; i++) {
        container.insert({ i, i });
        perftool.record();
    }
}

template<class T>
void insert_map_end(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert({ i, i });
        perftool.record();
    }
}

void insert_forward_list_end(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    container.push_front(0);
    auto it = container.begin();
    for (size_t i = 1; i < count; i++) {
        it = container.insert_after(it, i);
        perftool.record();
    }
}

void insert_forward_list_begin(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.push_front(i);;
        perftool.record();
    }
}

void insert_forward_list_mid(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    container.push_front(0);
    for (size_t i = 1; i < count; i++) {
        container.insert_after(container.begin(), i);
        perftool.record();
    }
}

template<class T>
void insert_begin(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
        perftool.record();
    }
}

template<class T>
void insert_mid(size_t count, PerfTool& perftool) {
    T container;
    container.insert(container.end(), 0x0);
    container.insert(container.end(), 0x7FFFFFFF);
    container.insert(container.end(), 0xFFFFFFFF);
    auto it = container.begin();
    it++;
    for (size_t i = 1; i < count + 1; i++) {
        it = container.insert(it, i);
        perftool.record();
    }
}

template<class T>
void insert_end(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.end(), i);
        perftool.record();
    }
}

template<class T>
void test_insert(T fn, size_t count, const std::string& type_name) {
    std::string name(__FUNCTION__);
    name.append("_");
    name.append(type_name);
    name.append(".tstl");

    PerfTool perftool;
    perftool.init(count);
    fn(count, perftool);
    perftool.save(name.c_str());
}

void test_insert_begin() {
    const size_t count = 1024 * 16;
    
    auto fn_begin_vector = std::bind(insert_begin<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_vector)>(fn_begin_vector, count, "begin_vector");

    auto fn_begin_list = std::bind(insert_begin<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_list)>(fn_begin_list, count, "begin_list");

    auto fn_begin_forward_list = std::bind(insert_forward_list_begin, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_forward_list)>(fn_begin_forward_list, count, "begin_forwardlist");

    auto fn_begin_deque = std::bind(insert_begin<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_deque)>(fn_begin_deque, count, "begin_deque");

    // set
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_begin_set = std::bind(insert_begin<std::set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_set)>(fn_begin_set, count, "begin_set");

    auto fn_begin_multiset = std::bind(insert_begin<std::multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_multiset)>(fn_begin_multiset, count, "begin_multiset");

    auto fn_begin_unordered_set = std::bind(insert_begin<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_unordered_set)>(fn_begin_deque, count, "begin_unorderedset");

    auto fn_begin_unordered_multiset = std::bind(insert_begin<std::unordered_multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_unordered_multiset)>(fn_begin_unordered_multiset, count, "begin_unorderedmultiset");
    
    // map
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_begin_map = std::bind(insert_map_begin<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_map)>(fn_begin_map, count, "begin_map");

    auto fn_begin_multimap = std::bind(insert_map_begin<std::multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_multimap)>(fn_begin_multimap, count, "begin_multimap");

    auto fn_begin_unordered_map = std::bind(insert_map_begin<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_unordered_map)>(fn_begin_unordered_map, count, "begin_unorderedmap");

    auto fn_begin_unordered_multimap = std::bind(insert_map_begin<std::unordered_multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_unordered_multimap)>(fn_begin_unordered_multimap, count, "begin_unorderedmultimap");
}

void test_insert_mid() {
    const size_t count = 1024 * 16;

    auto fn_mid_vector = std::bind(insert_mid<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_vector)>(fn_mid_vector, count, "mid_vector");

    auto fn_mid_list = std::bind(insert_mid<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_list)>(fn_mid_list, count, "mid_list");

    auto fn_mid_forward_list = std::bind(insert_forward_list_mid, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_forward_list)>(fn_mid_forward_list, count, "mid_forwardlist");

    auto fn_mid_deque = std::bind(insert_mid<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_deque)>(fn_mid_deque, count, "mid_deque");

    // set
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_mid_set = std::bind(insert_mid<std::set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_set)>(fn_mid_set, count, "mid_set");

    auto fn_mid_multiset = std::bind(insert_mid<std::multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_multiset)>(fn_mid_multiset, count, "mid_multiset");

    auto fn_mid_unordered_set = std::bind(insert_mid<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_unordered_set)>(fn_mid_unordered_set, count, "mid_unorderedset");

    auto fn_mid_unordered_multiset = std::bind(insert_mid<std::unordered_multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_unordered_multiset)>(fn_mid_unordered_multiset, count, "mid_unorderedmultiset");

    // map
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_mid_map = std::bind(insert_map_mid<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_map)>(fn_mid_map, count, "mid_map");

    auto fn_mid_multimap = std::bind(insert_map_mid<std::multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_multimap)>(fn_mid_map, count, "mid_multimap");

    auto fn_mid_unordered_map = std::bind(insert_map_mid<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_unordered_map)>(fn_mid_unordered_map, count, "mid_unorderedmap");

    auto fn_mid_unordered_multimap = std::bind(insert_map_mid<std::unordered_multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_unordered_multimap)>(fn_mid_unordered_multimap, count, "mid_unorderedmultimap");
}

void test_insert_end() {
    const size_t count = 1024 * 16;

    auto fn_end_vector = std::bind(insert_end<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_vector)>(fn_end_vector, count, "end_vector");
    
    auto fn_end_list = std::bind(insert_end<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_list)>(fn_end_list, count, "end_list");

    auto fn_end_forward_list = std::bind(insert_forward_list_end, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_forward_list)>(fn_end_forward_list, count, "end_forwardlist");

    auto fn_end_deque = std::bind(insert_end<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_deque)>(fn_end_deque, count, "end_deque");

    // set
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_end_set = std::bind(insert_end<std::set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_set)>(fn_end_set, count, "end_set");

    auto fn_end_multiset = std::bind(insert_end<std::multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_multiset)>(fn_end_multiset, count, "end_multiset");

    auto fn_end_unordered_set = std::bind(insert_end<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_unordered_set)>(fn_end_unordered_set, count, "end_unorderedset");

    auto fn_end_unordered_multiset = std::bind(insert_end<std::unordered_multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_unordered_multiset)>(fn_end_unordered_multiset, count, "end_unorderedmultiset");

    // map
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_end_map = std::bind(insert_map_end<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_map)>(fn_end_map, count, "end_map");

    auto fn_end_multimap = std::bind(insert_map_end<std::multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_multimap)>(fn_end_multimap, count, "end_multimap");

    auto fn_end_unordered_map = std::bind(insert_map_end<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_unordered_map)>(fn_end_unordered_map, count, "end_unorderedmap");

    auto fn_end_unordered_multimap = std::bind(insert_map_end<std::unordered_multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_unordered_multimap)>(fn_end_unordered_multimap, count, "end_unorderedmultimap");
}

#endif