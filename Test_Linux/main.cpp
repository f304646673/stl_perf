#include <cstdio>
#include "Test_Src/test_insert_begin_mid_end.h"
#include "Test_Src/test_erase_begin_mid_end.h"
#include "Test_Src/test_traversal_begin_end.h"
#include "Test_Src/test_find.h"

int main(){
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