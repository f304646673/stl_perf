#pragma once
#include <windows.h>
#include <fstream>

class PerfTool {
public:
    PerfTool() : _records(nullptr), _index(0) {};
    ~PerfTool() {};
public:
    void init(size_t count) {
        _records = new LARGE_INTEGER[count];
    }

    void record() {
        LARGE_INTEGER& PerformanceCount = _records[_index++];
        QueryPerformanceCounter(&PerformanceCount);
    }

    void save(const char* path) {
        std::ofstream fd(path);
        LONGLONG base = _records[0].QuadPart;
        for (size_t i = 0; i < _index; i++) {
            fd << _records[i].QuadPart - base << std::endl;
        }
        fd.close();
    }
private:
    LARGE_INTEGER *_records;
    size_t _index;
};
