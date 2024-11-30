#pragma once

#include <array>
#include <algorithm>
#include <cstddef>

template <typename T, size_t N>
class CircularBuffer
{
private:
  size_t index;
  std::array<T, N> buffer;

public:
  CircularBuffer() = default;

  CircularBuffer(T initial_value)
  {
    index = 0;
    std::fill_n(buffer.data, N, initial_value);
  }

  const std::array<T, N> GetArray() const
  {
    return buffer;
  }

  void AddToArray(const T element)
  {
    buffer[index] = element;
    index = (index + 1) % N;
  }

  void FillBuffer(const T element)
  {
    std::fill_n(buffer.data, N, element);
  }

  T GetBufferAverage()
  {
    T running_average;
    for (size_t i = 0; i < this->Size(); i++)
    {
      running_average = (running_average * (i / (i + 1.0f))) + (buffer[i] * (1.0f / (i + 1.0f)));
    }
    return running_average;
  }

  constexpr size_t Size() const
  {
    return N;
  }
};