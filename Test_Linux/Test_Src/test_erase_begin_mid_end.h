#ifndef TEST_ERASE_BEGIN_MID_END_H
#define TEST_ERASE_BEGIN_MID_END_H

#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include <functional> 

#include "perftool.h"

template<class T>
void erase_map_end(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container[i] = i;
    }
    for (size_t i = 0; i < count; i++) {
        container.erase(count - i - 1);
        perftool.record();
    }
}

template<class T>
void erase_map_begin(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container[i] = i;
    }
    for (size_t i = 0; i < count; i++) {
        container.erase(container.begin());
        perftool.record();
    }
}

template<class T>
void erase_map_mid(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container[i] = i;
    }

    auto it = container.begin();
    it++;
    for (size_t i = 0; i < count - 128; i++) {
        it = container.erase(it);
        perftool.record();
    }
}

void erase_unordered_set_end(size_t count, PerfTool& perftool) {
    std::unordered_set<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.insert(i);
    }
    for (size_t i = 0; i < count; i++) {
        container.erase(count - i - 1);
        perftool.record();
    }
}

void erase_set_end(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
    }
    for (size_t i = 0; i < count; i++) {
        container.erase(count - i- 1);
        perftool.record();
    }
}

void erase_set_begin(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
    }
    for (size_t i = 0; i < count; i++) {
        container.erase(container.begin());
        perftool.record();
    }
}

void erase_set_mid(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
    }

    auto it = container.begin();
    it++;
    for (size_t i = 0; i < count - 128; i++) {
        it = container.erase(it);
        perftool.record();
    }
}

void erase_forward_list_end(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.push_front(i);
    }
    for (size_t i = 0; i < count; i++) {
        container.remove(count - i - 1);
        perftool.record();
    }
}

void erase_forward_list_begin(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.push_front(i);
    }
    for (size_t i = 0; i < count; i++) {
        container.pop_front();
        perftool.record();
    }
}

void erase_forward_list_mid(size_t count, PerfTool& perftool) {
    std::forward_list<size_t> container;
    for (size_t i = 0; i < count; i++) {
        container.push_front(i);
    }

    for (size_t i = 0; i < count - 128; i++) {
        container.erase_after(container.begin());
        perftool.record();
    }
}

template<class T>
void erase_end(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.end(), i);
    }
    for (size_t i = 0; i < count; i++) {
        container.pop_back();
        perftool.record();
    }
}

template<class T>
void erase_begin(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.end(), i);
    }
    auto it = container.begin();
    for (size_t i = 0; i < count; i++) {
        it = container.erase(it);
        perftool.record();
    }
}

template<class T>
void erase_mid(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.end(), i);
    }

    auto it = container.begin();
    it++;
    for (size_t i = 0; i < count - 128; i++) {
        it = container.erase(it);
        perftool.record();
    }
}

template<class T>
void test_erase(T fn, size_t count, const std::string& type_name) {
    std::string name(__FUNCTION__);
    name.append("_");
    name.append(type_name);
    name.append(".tstl");

    PerfTool perftool;
    perftool.init(count);
    fn(count, perftool);
    perftool.save(name.c_str());
}

void test_erase_begin() {
    const size_t count = 1024 * 16;

    auto fn_begin_vector = std::bind(erase_begin<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_vector)>(fn_begin_vector, count, "begin_vector");

    auto fn_mid_list = std::bind(erase_begin<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_list)>(fn_mid_list, count, "begin_list");

    auto fn_begin_deque = std::bind(erase_begin<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_deque)>(fn_begin_deque, count, "begin_deque");

    auto fn_begin_forward_list = std::bind(erase_forward_list_begin, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_forward_list)>(fn_begin_forward_list, count, "begin_forwardlist");

    auto fn_begin_set = std::bind(erase_set_begin, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_set)>(fn_begin_set, count, "begin_set");

    auto fn_begin_map = std::bind(erase_map_begin<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_map)>(fn_begin_map, count, "begin_map");

    auto fn_begin_unordered_map = std::bind(erase_map_begin<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_unordered_map)>(fn_begin_unordered_map, count, "begin_unorderedmap");

    auto fn_begin_unordered_set = std::bind(erase_begin<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_begin_unordered_set)>(fn_begin_unordered_set, count, "begin_unorderedset");
}

void test_erase_end() {
    const size_t count = 1024 * 16;
    auto fn_end_vector = std::bind(erase_end<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_vector)>(fn_end_vector, count, "end_vector");
    
    auto fn_mid_list = std::bind(erase_end<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_list)>(fn_mid_list, count, "end_list");

    auto fn_end_deque = std::bind(erase_end<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_deque)>(fn_end_deque, count, "end_deque");

    auto fn_end_forward_list = std::bind(erase_forward_list_end, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_forward_list)>(fn_end_forward_list, count, "end_forwardlist");

    auto fn_end_set = std::bind(erase_set_end, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_set)>(fn_end_set, count, "end_set");

    auto fn_end_map = std::bind(erase_map_end<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_map)>(fn_end_map, count, "end_map");

    auto fn_end_unordered_map = std::bind(erase_map_end<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_unordered_map)>(fn_end_unordered_map, count, "end_unorderedmap");

    auto fn_end_unordered_set = std::bind(erase_unordered_set_end, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_end_unordered_set)>(fn_end_unordered_set, count, "end_unorderedset");
}

void test_erase_mid() {
    const size_t count = 1024 * 16;
    auto fn_mid_vector = std::bind(erase_mid<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_vector)>(fn_mid_vector, count, "mid_vector");

    auto fn_mid_list = std::bind(erase_mid<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_list)>(fn_mid_list, count, "mid_list");

    auto fn_mid_deque = std::bind(erase_mid<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_deque)>(fn_mid_deque, count, "mid_deque");

    auto fn_mid_forward_list = std::bind(erase_forward_list_mid, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_forward_list)>(fn_mid_forward_list, count, "mid_forwardlist");

    auto fn_mid_set = std::bind(erase_set_mid, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_set)>(fn_mid_set, count, "mid_set");

    auto fn_mid_map = std::bind(erase_map_mid<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_map)>(fn_mid_map, count, "mid_map");

    auto fn_mid_unordered_map = std::bind(erase_map_mid<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_unordered_map)>(fn_mid_unordered_map, count, "mid_unorderedmap");

    auto fn_mid_unordered_set = std::bind(erase_mid<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_erase<decltype(fn_mid_unordered_set)>(fn_mid_unordered_set, count, "mid_unorderedset");
}

#endif