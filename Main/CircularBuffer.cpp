#include "CircularBuffer.h"
#include <iostream>

// Constructor
CircularBuffer::CircularBuffer(size_t size) : buffer(size), max_size(size), head(0), count(0) {}

// Add a new value to the buffer
void CircularBuffer::add(long value) {
    buffer[head] = value;
    head = (head + 1) % max_size;
    if (count < max_size) {
        ++count;
    }
}
// Dynamic size for Circular Buffer
void CircularBuffer::changeSize(size_t new_size){
    buffer.resize(new_size);
    max_size=new_size;
}
// Reinitialize the buffer
   void CircularBuffer::reinitialize() {
        buffer.assign(max_size, 0); // Reset all elements to 0 (or any default value)
        head = 0;
        count = 0;
    }
size_t CircularBuffer::getSize(){
    return buffer.size();
}
// Check if all values in the buffer are the same
bool CircularBuffer::allValuesSame() const {
    if (count < 2) return false;

    int first_value = buffer[0];
    for (size_t i = 1; i < count; ++i) {
        if (buffer[i] != first_value) {
            return false;
        }
    }
    return true;
}

// Print the buffer contents
void CircularBuffer::printBuffer() const {
    for (size_t i = 0; i < count; ++i) {
        std::cout << buffer[(head + max_size - count + i) % max_size] << " ";
    }
    std::cout << std::endl;
}

double CircularBuffer::calculateAvg() const {
    if (count == 0) {
        return 0.0; // Return 0 if the buffer is empty to avoid division by zero
    }

    int sum = 0;
    for (size_t i = 0; i < count; ++i) {
        sum += buffer[(head + max_size - count + i) % max_size];
    }
    return static_cast<double>(sum)/count;
}
