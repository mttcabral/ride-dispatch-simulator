#ifndef RIDE_DISPATCH_SIMULATOR_INCLUDE_MIN_HEAP_H_
#define RIDE_DISPATCH_SIMULATOR_INCLUDE_MIN_HEAP_H_

#include <stdexcept>

#include "vector.h"

/**
 * @brief A priority queue implementation using a binary min-heap.
 *
 * This class provides a priority queue data structure where the element with
 * the smallest value is always at the top. It is implemented using a dynamic
 * array (Vector) to store the heap elements, ensuring efficient memory usage
 * and performance.
 *
 * The MinHeap is essential for the discrete event simulation, specifically for
 * the event scheduler (Escalonador), where events need to be processed in
 * chronological order.
 *
 * @tparam T The type of elements stored in the heap. Must support the `<`
 * operator for comparison.
 */
template <typename T> class MinHeap {
private:
  /**
   * @brief The underlying container for storing heap elements.
   *
   * We use a Vector to maintain the complete binary tree structure of the heap.
   * For a node at index `i`:
   * - The left child is at index `2*i + 1`.
   * - The right child is at index `2*i + 2`.
   * - The parent is at index `(i - 1) / 2`.
   */
  Vector<T> heap_;

  /**
   * @brief Restores the min-heap property by moving an element up the tree.
   *
   * This operation, compares the element at the given index
   * with its parent. If the element is smaller than its parent,
   * they are swapped. This process is repeated until the element is
   * in the correct position or reaches the root.
   *
   * Time Complexity: O(log n), where n is the number of elements in the heap.
   *
   * @param index The index of the element to move up.
   */
  void HeapifyUp(size_t index) {
    if (index == 0)
      return;
    size_t parent_index = (index - 1) / 2;
    if (heap_[index] < heap_[parent_index]) {
      T temp = heap_[index];
      heap_[index] = heap_[parent_index];
      heap_[parent_index] = temp;
      HeapifyUp(parent_index);
    }
  }

  /**
   * @brief Restores the min-heap property by moving an element down the tree.
   *
   * This operation, compares the element at the given index with its children.
   * If the element is larger than either of its children, it is swapped with
   * the smallest child. This process is repeated until the element is in the
   * correct position or becomes a leaf.
   *
   * Time Complexity: O(log n), where n is the number of elements in the heap.
   *
   * @param index The index of the element to move down.
   */
  void HeapifyDown(size_t index) {
    size_t left_child = 2 * index + 1;
    size_t right_child = 2 * index + 2;
    size_t smallest = index;

    if (left_child < heap_.size() && heap_[left_child] < heap_[smallest]) {
      smallest = left_child;
    }

    if (right_child < heap_.size() && heap_[right_child] < heap_[smallest]) {
      smallest = right_child;
    }

    if (smallest != index) {
      T temp = heap_[index];
      heap_[index] = heap_[smallest];
      heap_[smallest] = temp;
      HeapifyDown(smallest);
    }
  }

public:
  /**
   * @brief Default constructor.
   *
   * Initializes an empty MinHeap.
   */
  MinHeap() {}

  /**
   * @brief Inserts a new element into the priority queue.
   *
   * The element is added to the end of the heap and then moved up to its
   * correct position to maintain the min-heap property.
   *
   * Time Complexity: O(log n).
   *
   * @param value The value to be inserted.
   */
  void push(const T &value) {
    heap_.push_back(value);
    HeapifyUp(heap_.size() - 1);
  }

  /**
   * @brief Removes the element with the smallest value (the top) from the
   * priority queue.
   *
   * The last element in the heap is moved to the root, and then moved down to
   * its correct position to maintain the min-heap property. If the heap is
   * empty, this operation does nothing.
   *
   * Time Complexity: O(log n).
   */
  void pop() {
    if (heap_.empty())
      return;
    heap_[0] = heap_[heap_.size() - 1];
    heap_.pop_back();
    if (!heap_.empty()) {
      HeapifyDown(0);
    }
  }

  /**
   * @brief Accesses the element with the smallest value (the top) of the
   * priority queue.
   *
   * Time Complexity: O(1).
   *
   * @return A constant reference to the smallest element.
   * @throws std::out_of_range If the heap is empty.
   */
  T top() const {
    if (heap_.empty())
      throw std::out_of_range("Heap is empty");
    return heap_[0];
  }

  /**
   * @brief Checks if the priority queue is empty.
   *
   * Time Complexity: O(1).
   *
   * @return true if the heap contains no elements, false otherwise.
   */
  bool empty() const { return heap_.empty(); }

  /**
   * @brief Returns the number of elements in the priority queue.
   *
   * Time Complexity: O(1).
   *
   * @return The number of elements in the heap.
   */
  size_t size() const { return heap_.size(); }
};

#endif