#ifndef PERFTOOL_H
#define PERFTOOL_H

#ifdef __linux__
#include <sys/time.h> 
#define TimeStruct timeval
#else
#include <windows.h>
#define TimeStruct LARGE_INTEGER
#endif

#include <fstream>

class PerfTool {
public:
    PerfTool() : _records(nullptr), _index(0) {};
    ~PerfTool() {};
public:
    void init(size_t count) {
        _records = new TimeStruct[count];
    }

    void record() {
        TimeStruct& PerformanceCount = _records[_index++];
#ifdef __linux__
        gettimeofday(&PerformanceCount, NULL);
#else
        QueryPerformanceCounter(&PerformanceCount);
#endif
    }

    void save(const char* path) {
        std::ofstream fd(path);
#ifdef __linux__
        TimeStruct base = _records[0];
#else
        LONGLONG base = _records[0].QuadPart;
#endif
        for (size_t i = 0; i < _index; i++) {
#ifdef __linux__
            fd << (_records[i].tv_sec - base.tv_sec) * 1000 * 1000 + (_records[i].tv_usec - base.tv_usec) << std::endl;
#else
            fd << _records[i].QuadPart - base << std::endl;
#endif
        }
        fd.close();
    }
private:
    TimeStruct *_records;
    size_t _index;
};

#endif