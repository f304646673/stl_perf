#pragma once
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>

#include <functional> 

#include "perftool.h"

void insert_set_end(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = 1; i < count; i++) {
        container.insert(i);
        perftool.record();
    }
}

void insert_set_begin(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    for (size_t i = count; i > 0; i--) {
        container.insert(i);;
        perftool.record();
    }
}

void insert_set_mid(size_t count, PerfTool& perftool) {
    std::set<size_t> container;
    container.insert(0);
    container.insert(count + count);
    auto it = container.begin();
    for (size_t i = 1; i < count + 1; i++) {
        container.insert(i);
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
    auto it = container.begin();
    for (size_t i = 1; i < count; i++) {
        container.insert_after(container.begin(), i);
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
    container.insert(container.end(), 0xFFFFFFFF);
    container.insert(container.end(), 0xFFFFFFFF);
    auto it = container.end();
    it--;
    for (size_t i = 0; i < count; i++) {
        it = container.insert(it, i);
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

    auto fn_begin_deque = std::bind(insert_begin<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_deque)>(fn_begin_deque, count, "begin_deque");

    auto fn_begin_forward_list = std::bind(insert_forward_list_begin, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_forward_list)>(fn_begin_forward_list, count, "begin_forwardlist");

    auto fn_begin_set = std::bind(insert_set_begin, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_set)>(fn_begin_set, count, "begin_set");

    auto fn_begin_unordered_set = std::bind(insert_begin<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_begin_unordered_set)>(fn_begin_deque, count, "begin_unorderedset");
}

void test_insert_end() {
    const size_t count = 1024 * 16;

    auto fn_end_vector = std::bind(insert_end<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_vector)>(fn_end_vector, count, "end_vector");
    
    auto fn_end_list = std::bind(insert_end<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_list)>(fn_end_list, count, "end_list");

    auto fn_end_deque = std::bind(insert_end<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_deque)>(fn_end_deque, count, "end_deque");

    auto fn_end_forward_list = std::bind(insert_forward_list_end, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_forward_list)>(fn_end_forward_list, count, "end_forwardlist");

    auto fn_end_set = std::bind(insert_set_end, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_set)>(fn_end_set, count, "end_set");

    auto fn_end_unordered_set = std::bind(insert_end<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_end_unordered_set)>(fn_end_deque, count, "end_unorderedset");
}

void test_insert_mid() {
    const size_t count = 1024 * 16;

    auto fn_mid_vector = std::bind(insert_mid<std::vector<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_vector)>(fn_mid_vector, count, "mid_vector");

    auto fn_mid_list = std::bind(insert_mid<std::list<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_list)>(fn_mid_list, count, "mid_list");

    auto fn_mid_deque = std::bind(insert_mid<std::deque<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_deque)>(fn_mid_deque, count, "mid_deque");

    auto fn_mid_forward_list = std::bind(insert_forward_list_mid, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_forward_list)>(fn_mid_forward_list, count, "mid_forwardlist");

    auto fn_mid_set = std::bind(insert_set_mid, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_set)>(fn_mid_set, count, "mid_set");

    auto fn_mid_unordered_set = std::bind(insert_mid<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_insert<decltype(fn_mid_unordered_set)>(fn_mid_deque, count, "mid_unorderedset");
}