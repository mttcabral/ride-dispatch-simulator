# Ride Dispatch Simulator

A discrete event simulation (DES) system for a ride-sharing application ("CabeAí"). This project implements a dispatch algorithm that groups passenger requests into shared rides to optimize efficiency and reduce costs, adhering to strict memory management constraints.

## 📖 Overview

This simulator processes a stream of passenger requests (origin, destination, and time) and assigns them to vehicles. It utilizes a **greedy heuristic** to combine compatible requests into a single ride (ride-sharing) based on vehicle capacity, route efficiency, and maximum passenger delay. Once grouped, the system simulates the vehicle routes using a Discrete Event logic to calculate total distance and duration.

## 🛠 Technical Highlights

This project was developed for a Data Structures course (UFMG) with a specific constraint: **The usage of C++ Standard Template Library (STL) containers (e.g., `std::vector`, `std::map`) was prohibited.**

Consequently, this repository includes robust custom implementations of:
* **`Vector<T>`**: A dynamic array with automatic resizing and memory management.
* **`MinHeap<T>`**: A binary heap priority queue used for the event scheduler.

## 🚀 Features

* **Ride-Sharing Logic**: Groups multiple requests into a single vehicle if they satisfy spatial (max distance) and temporal (max delay) constraints.
* **Efficiency Metrics**: Calculates route efficiency based on the ratio of direct distance vs. shared route distance.
* **Event Scheduler**: Uses a Min-Heap to process simulation events (pickups, drop-offs, displacements) in chronological order.
* **Memory Management**: Full manual memory management (RAII principles) without smart pointers.

## 📂 Project Structure

The project follows a standard directory structure:

```text
├── Makefile          # Build configuration
├── src/              # Source files (.cc)
├── include/          # Header files (.h)
├── bin/              # Output executables
└── obj/              # Compiled object files
