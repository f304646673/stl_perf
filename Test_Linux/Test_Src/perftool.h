#ifndef PERFTOOL_H
#define PERFTOOL_H

#ifdef __linux__
#include <sys/time.h> 
#define timespec_ timespec
#else
#include <ctime>
#define timespec_ _timespec64
#endif

#include <iomanip>
#include <fstream>

class PerfTool {
public:
    PerfTool() : _records(nullptr), _size(0) {};
    ~PerfTool() {};
public:
    void init(size_t count) {
        _records = new timespec_[count];
    }

    void record() {
        timespec_& time_spec = _records[_size++];
#ifdef __linux__
        clock_gettime(CLOCK_REALTIME, &time_spec);
#else
        _timespec64_get(&time_spec, TIME_UTC);
#endif
    }

    void save(const char* path) {
        std::ofstream fd(path);
        for (size_t i = 0; i < _size; i++) {
            fd << _records[i].tv_sec << std::setw(9) << std::setfill('0') <<_records[i].tv_nsec << std::endl;
        }
        fd.close();
    }
private:
    timespec_ *_records;
    size_t _size;
};

#endif