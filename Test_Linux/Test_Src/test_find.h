#ifndef TEST_FIND_H
#define TEST_FIND_H

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <functional> 

#include "perftool.h"

template<class T>
void map_find(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert({ i,i });
    }
    for (size_t i = 0; i < count; i++) {
        container.find(i);
        perftool.record();
    }
}

template<class T>
void set_find(size_t count, PerfTool& perftool) {
    T container;
    for (size_t i = 0; i < count; i++) {
        container.insert(container.begin(), i);
    }
    for (size_t i = 0; i < count; i++) {
        container.find(i);
        perftool.record();
    }
}

template<class T>
void test_find(T fn, size_t count, const std::string& type_name) {
    std::string name(__FUNCTION__);
    name.append("_");
    name.append(type_name);
    name.append(".tstl");

    PerfTool perftool;
    perftool.init(count);
    fn(count, perftool);
    perftool.save(name.c_str());
}

void test_set_map_find() {
    const size_t count = 1024 * 16;
    // set
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_find_set = std::bind(set_find<std::set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_set)>(fn_find_set, count, "set");

    auto fn_find_multiset = std::bind(set_find<std::multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_multiset)>(fn_find_multiset, count, "multiset");

    auto fn_find_unordered_set = std::bind(set_find<std::unordered_set<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_unordered_set)>(fn_find_unordered_set, count, "unorderedset");

    auto fn_find_unordered_multiset = std::bind(set_find<std::unordered_multiset<size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_unordered_multiset)>(fn_find_unordered_multiset, count, "unorderedmultiset");

    // map
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto fn_find_map = std::bind(map_find<std::map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_map)>(fn_find_map, count, "map");

    auto fn_find_multimap = std::bind(map_find<std::multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_multimap)>(fn_find_multimap, count, "multimap");

    auto fn_find_unordered_map = std::bind(map_find<std::unordered_map<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_unordered_map)>(fn_find_unordered_map, count, "unorderedmap");

    auto fn_find_unordered_multimap = std::bind(map_find<std::unordered_multimap<size_t, size_t>>, std::placeholders::_1, std::placeholders::_2);
    test_find<decltype(fn_find_unordered_multimap)>(fn_find_unordered_multimap, count, "unorderedmultimap");
}

#endif