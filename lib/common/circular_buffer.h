#pragma once

#include <array>
#include <algorithm>
#include <cstddef>

namespace sm
{
  template <typename T, size_t N>
  class CircularBuffer
  {
  private:
    size_t index;
    std::array<T, N> buffer;

  public:
    CircularBuffer() = default;

    CircularBuffer(const T initial_value)
    {
      index = 0;
      for (unsigned int i = 0; i < N; i++)
      {
        buffer[i] = initial_value;
      }
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
      for (unsigned int i = 0; i < N; i++)
      {
        buffer[i] = element;
      }
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
}