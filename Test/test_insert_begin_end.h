#pragma once
#include <vector>
#include <list>
#include <deque>

#include "perftool.h"

template<class T>
void insert_end(size_t count) {
    T container;
    auto it = container.end();
    for (size_t i = 0; i < count; i++) {
        it = container.insert(it, i);
        PerfTool::get_instance().record();
    }
}

template<class T>
void insert_begin(size_t count) {
    T container;
    auto it = container.begin();
    for (size_t i = 0; i < count; i++) {
        it = container.insert(it, i);
        PerfTool::get_instance().record();
    }
}

void test_insert_begin() {
    const size_t count = 1024 * 128;
    PerfTool::get_instance().init(count);
    //insert_begin<std::vector<size_t>>(count);
    //PerfTool::get_instance().save("insert_begin_vec.txt");

    //insert_begin<std::list<size_t>>(count);
    //PerfTool::get_instance().save("insert_begin_list.txt");

    insert_begin<std::deque<size_t>>(count);
    PerfTool::get_instance().save("insert_begin_deque.txt");
}

void test_insert_end() {
    const size_t count = 1024 * 128;
    PerfTool::get_instance().init(count);
    //insert_end<std::vector<size_t>>(count);
    //PerfTool::get_instance().save("insert_end_vec.txt");

    //insert_end<std::list<size_t>>(count);
    //PerfTool::get_instance().save("insert_end_list.txt");

    //insert_end<std::deque<size_t>>(count);
    PerfTool::get_instance().save("insert_end_deque.txt");
}