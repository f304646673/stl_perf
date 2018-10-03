#ifndef TEST_TRAVERSAL_BEGIN_END_H
#define TEST_TRAVERSAL_BEGIN_END_H

#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <unordered_set>
#include <unordered_map>

#include <functional> 

#include "perftool.h"

template<class T>
void traversal_map_end(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container[i] = i;
    }
    for (auto it = container.rbegin(); it != container.rend();) {
        it++;
        perftool.record();
    }
}

template<class T>
void traversal_map_begin(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container[i] = i;
    }
    for (auto it = container.begin(); it != container.end();) {
        it++;
        perftool.record();
    }
}

void traversal_forward_list_begin(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.push_front(i);
    }
    for (auto it = container.begin(); it != container.end();) {
        it++;
        perftool.record();
    }
}

void traversal_set_begin(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
    }
    for (auto it = container.begin(); it != container.end();) {
        it++;
        perftool.record();
    }
}

void traversal_set_end(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.end(), i);
    }
    for (auto it = container.rbegin(); it != container.rend();) {
        it++;
        perftool.record();
    }
}

template<class T>
void traversal_end(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.end(), i);
    }
    for (auto it = container.rbegin(); it != container.rend();) {
        it++;
        perftool.record();
    }
}

template<class T>
void traversal_begin(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
    }
    for (auto it = container.begin(); it != container.end();) {
        it++;
        perftool.record();
    }
}

template<class T>
void test_traversal(T fn, size_t count, const std::string& type_name) {
    std::string name(__FUNCTION__);
    name.append("_");
    name.append(type_name);
    name.append(".tstl");

    PerfTool perftool;
    perftool.init(count);
    fn(count, perftool);
    perftool.save(name.c_str());
}

void test_traversal_begin() {
    const size_t count = 1024 * 16;

    auto fn_begin_vector = std::bind(traversal_begin<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_vector)>(fn_begin_vector, count, "begin_vector");

    auto fn_begin_list = std::bind(traversal_begin<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_list)>(fn_begin_list, count, "begin_list");

    auto fn_begin_deque = std::bind(traversal_begin<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_deque)>(fn_begin_deque, count, "begin_deque");

    auto fn_begin_forward_list = std::bind(traversal_forward_list_begin, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_forward_list)>(fn_begin_forward_list, count, "begin_forwardlist");

    auto fn_begin_set = std::bind(traversal_set_begin, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_set)>(fn_begin_set, count, "begin_set");

    auto fn_begin_unordered_set = std::bind(traversal_begin<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_unordered_set)>(fn_begin_unordered_set, count, "begin_unorderedset");

    auto fn_begin_map = std::bind(traversal_map_begin<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_map)>(fn_begin_map, count, "begin_map");

    auto fn_begin_unordered_map = std::bind(traversal_map_begin<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_begin_unordered_map)>(fn_begin_unordered_map, count, "begin_unorderedmap");
}

void test_traversal_end() {
    const size_t count = 1024 * 16;
    auto fn_end_vector = std::bind(traversal_end<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_end_vector)>(fn_end_vector, count, "end_vector");
    
    auto fn_end_list = std::bind(traversal_end<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_end_list)>(fn_end_list, count, "end_list");

    auto fn_end_deque = std::bind(traversal_end<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_end_deque)>(fn_end_deque, count, "end_deque");

    //auto fn_end_forward_list = std::bind(traversal_end<std::forward_list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    //test_traversal<decltype(fn_end_forward_list)>(fn_end_forward_list, count, "end_forwardlist");

    auto fn_end_set = std::bind(traversal_set_end, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_end_set)>(fn_end_set, count, "end_set");

    //auto fn_end_unordered_set = std::bind(traversal_end<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    //test_traversal<decltype(fn_end_unordered_set)>(fn_end_unordered_set, count, "end_unorderedset");

    auto fn_end_map = std::bind(traversal_map_end<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_traversal<decltype(fn_end_map)>(fn_end_map, count, "end_map");

    //auto fn_end_unordered_map = std::bind(traversal_map_end<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    //test_traversal<decltype(fn_end_unordered_map)>(fn_end_unordered_map, count, "end_unorderedmap");
}

#endif