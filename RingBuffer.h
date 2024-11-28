#pragma once

#include <cstddef>

template <typename T, size_t BufferSize>
class RingBuffer {
  private:
    T buffer[BufferSize];
    size_t head = 0;
    size_t count = 0;

  public:
    void add(T value) {
        buffer[head] = value;
        head = (head + 1) % BufferSize;
        if (count < BufferSize) count++;
    }

    size_t size() const {
        return count;
    }

    T get(size_t index) const {
        if (index >= count) return T();
        size_t pos = (head + BufferSize - count + index) % BufferSize;
        return buffer[pos];
    }
};