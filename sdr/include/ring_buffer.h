#ifndef INCLUDE_RING_BUFFER_H
#define INCLUDE_RING_BUFFER_H

#include <vector>
#include <stdexcept>


class buffer_full_exception : public std::runtime_error {
 public:
  buffer_full_exception() :
      std::runtime_error("Buffer full!") {};
};

class buffer_empty_exception : public std::runtime_error {
 public:
  buffer_empty_exception() :
      std::runtime_error("Buffer empty!") {};
};


template <class T, int capacity>
class ring_buffer {
 private:
  std::vector<T> buffer;
  int head, offset, size;

 public:
  ring_buffer()
    : buffer (capacity, 0),
      head {0},
      offset {0},
      size {capacity} {};
  int available_write() { return size - offset; }
  int available_read() { return offset; }

  void push(T element);
  T take();

  struct block {
    T * start_index;
    int length;
  };

  block take_block() noexcept (false);
};

// TODO: how to balance reads and writes?
// Writer:
// 1: let writers overwrite
// 2: reject excessive writes
// 3: wait for free space to write to
//
// Reader:
// 1. suspend reader when no data available (cond variable)
// 2. busy wait source reader
// FOR NOW: (2, 2) - reject excessive writes (easy), busy wait source reader (should rarely happen)

#endif  /* INCLUDE_RING_BUFFER_H */
