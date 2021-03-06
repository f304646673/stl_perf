// Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "test_insert_begin_mid_end.h"
#include "test_erase_begin_mid_end.h"
#include "test_traversal_begin_end.h"
#include "test_find.h"

int main(int argc, const char* argv[]) {
    test_insert_begin();
    test_insert_end();
    test_insert_mid();
    
    test_erase_begin();
    test_erase_mid();
    test_erase_end();
    test_traversal_begin();
    test_traversal_end();

    test_set_map_find();
    return 0;
}
