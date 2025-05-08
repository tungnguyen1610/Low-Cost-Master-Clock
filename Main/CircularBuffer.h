#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

class CircularBuffer {
public:
    CircularBuffer(size_t size);
    void add(long value);
    void changeSize (size_t new_size);
    void reinitialize();
    size_t getSize();
    bool allValuesSame() const;
    void printBuffer() const;
    double calculateAvg() const;
private:
    std::vector<long> buffer;
    size_t max_size;
    size_t head;
    size_t count;
};

#ifdef __cplusplus
}
#endif

#endif // BUFFER_H
