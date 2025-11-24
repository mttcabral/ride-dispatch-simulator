#ifndef RIDE_DISPATCH_SIMULATOR_INCLUDE_VECTOR_H_
#define RIDE_DISPATCH_SIMULATOR_INCLUDE_VECTOR_H_

#include <cstddef>
#include <stdexcept>

/**
 * @brief A dynamic array implementation that manages memory manually.
 *
 * This class provides a sequence container that encapsulates dynamic size
 * arrays. It is designed to mimic the behavior of std::vector, adhering to the
 * project's constraint of avoiding STL containers. It supports dynamic
 * resizing, random access, and automatic memory management.
 *
 * @tparam T The type of elements stored in the vector.
 */
template <typename T> class Vector {
private:
  T *data_; // Pointer to the dynamically allocated array.
  size_t
      capacity_; // Total number of elements that can be held without resizing.
  size_t count_; // Number of elements currently in the vector.

  /**
   * @brief Resizes the internal storage to a new capacity.
   *
   * Allocates a new array of the specified capacity, copies existing elements
   * to the new array, and deallocates the old array.
   *
   * @param new_capacity The new capacity for the vector.
   */
  void resize(size_t new_capacity) {
    T *new_data = new T[new_capacity];
    for (size_t i = 0; i < count_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }

public:
  /**
   * @brief Default constructor.
   *
   * Initializes an empty vector with zero capacity.
   */
  Vector() : data_(nullptr), capacity_(0), count_(0) {}

  /**
   * @brief Destructor.
   *
   * Deallocates the memory used by the vector.
   */
  ~Vector() { delete[] data_; }

  /**
   * @brief Copy constructor.
   *
   * Creates a deep copy of another vector.
   *
   * @param other The vector to copy from.
   */
  Vector(const Vector &other) : data_(nullptr), capacity_(0), count_(0) {
    if (other.count_ > 0) {
      resize(other.capacity_);
      for (size_t i = 0; i < other.count_; ++i) {
        data_[i] = other.data_[i];
      }
      count_ = other.count_;
    }
  }

  /**
   * @brief Copy assignment operator.
   *
   * Replaces the contents with a copy of the contents of another vector.
   * Handles self-assignment and ensures strong exception safety guarantees
   * where possible.
   *
   * @param other The vector to copy from.
   * @return Reference to this vector.
   */
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      delete[] data_;
      data_ = nullptr;
      capacity_ = 0;
      count_ = 0;
      if (other.count_ > 0) {
        resize(other.capacity_);
        for (size_t i = 0; i < other.count_; ++i) {
          data_[i] = other.data_[i];
        }
        count_ = other.count_;
      }
    }
    return *this;
  }

  /**
   * @brief Adds an element to the end of the vector.
   *
   * If the current capacity is insufficient, the vector is resized.
   * The resizing strategy doubles the capacity (or sets it to 4 if empty)
   * to ensure amortized constant time complexity O(1).
   *
   * @param value The value to be added.
   */
  void push_back(const T &value) {
    if (count_ == capacity_) {
      resize(capacity_ == 0 ? 4 : capacity_ * 2);
    }
    data_[count_++] = value;
  }

  /**
   * @brief Removes the last element of the vector.
   *
   * Does nothing if the vector is empty.
   * Time complexity: O(1).
   */
  void pop_back() {
    if (count_ > 0) {
      count_--;
    }
  }

  /**
   * @brief Accesses the element at the specified index.
   *
   * Performs bounds checking and throws std::out_of_range if the index is
   * invalid. Time complexity: O(1).
   *
   * @param index The index of the element to access.
   * @return Reference to the element at the specified index.
   * @throws std::out_of_range if index >= size().
   */
  T &operator[](size_t index) {
    if (index >= count_) {
      throw std::out_of_range("Vector index out of range");
    }
    return data_[index];
  }

  /**
   * @brief Accesses the element at the specified index (const version).
   *
   * Performs bounds checking and throws std::out_of_range if the index is
   * invalid. Time complexity: O(1).
   *
   * @param index The index of the element to access.
   * @return Const reference to the element at the specified index.
   * @throws std::out_of_range if index >= size().
   */
  const T &operator[](size_t index) const {
    if (index >= count_) {
      throw std::out_of_range("Vector index out of range");
    }
    return data_[index];
  }

  /**
   * @brief Returns the number of elements in the vector.
   *
   * @return The number of elements.
   */
  size_t size() const { return count_; }

  /**
   * @brief Checks if the vector is empty.
   *
   * @return true if the vector is empty, false otherwise.
   */
  bool empty() const { return count_ == 0; }

  /**
   * @brief Clears the contents of the vector.
   *
   * Logical clear; does not deallocate internal memory, merely resets the
   * count.
   */
  void clear() { count_ = 0; }

  /**
   * @brief Returns a pointer to the first element.
   *
   * @return Pointer to the first element.
   */
  T *begin() { return data_; }

  /**
   * @brief Returns a pointer to the element following the last element.
   *
   * @return Pointer to the element following the last element.
   */
  T *end() { return data_ + count_; }

  /**
   * @brief Returns a const pointer to the first element.
   *
   * @return Const pointer to the first element.
   */
  const T *begin() const { return data_; }

  /**
   * @brief Returns a const pointer to the element following the last element.
   *
   * @return Const pointer to the element following the last element.
   */
  const T *end() const { return data_ + count_; }
};

#endif
