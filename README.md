# Ride Dispatch Simulator

A discrete event simulation (DES) system for a ride-sharing application ("CabeAí"). This project implements a dispatch algorithm that groups passenger requests into shared rides to optimize efficiency and reduce costs, adhering to strict memory management constraints.

## Overview

This simulator processes a stream of passenger requests (origin, destination, and time) and assigns them to vehicles. It utilizes a **greedy heuristic** to combine compatible requests into a single ride (ride-sharing) based on vehicle capacity, route efficiency, and maximum passenger delay. Once grouped, the system simulates the vehicle routes using a Discrete Event logic to calculate total distance and duration.

## Technical Highlights

This project was developed for a Data Structures course (UFMG) with a specific constraint: **The usage of C++ Standard Template Library (STL) containers (e.g., `std::vector`, `std::map`) was prohibited.**

Consequently, this repository includes robust custom implementations of:
* **`Vector<T>`**: A dynamic array with automatic resizing and memory management.
* **`MinHeap<T>`**: A binary heap priority queue used for the event scheduler.

## Features

* **Ride-Sharing Logic**: Groups multiple requests into a single vehicle if they satisfy spatial (max distance) and temporal (max delay) constraints.
* **Efficiency Metrics**: Calculates route efficiency based on the ratio of direct distance vs. shared route distance.
* **Event Scheduler**: Uses a Min-Heap to process simulation events (pickups, drop-offs, displacements) in chronological order.
* **Memory Management**: Full manual memory management (RAII principles) without smart pointers.

## Project Structure

The project follows a standard directory structure:

```text
├── Makefile          # Build configuration
├── src/              # Source files (.cc)
├── include/          # Header files (.h)
├── bin/              # Output executables
└── obj/              # Compiled object files
```

## How to Run

### Compilation

To compile the project, navigate to the root directory and run the make command. This will invoke g++ with the C++11 standard and generate the executable in the `bin/` folder.

    make all

To clean up object files and executables:

    make clean

### Execution

The simulator reads input parameters and requests from standard input (stdin). The recommended way to run the simulation is by redirecting an input file to the executable.
Bash

    ./bin/tp2.out < input_file.txt

### Input Format

The input must follow this specific order:

    Configuration Line: Space-separated simulation parameters.

        <capacity> (int): Max passengers per vehicle.

        <speed> (double): Vehicle speed (km/h or units/time).

        <max_wait_time> (double): Max time a passenger waits for pickup.

        <max_delay> (double): Max delay allowed relative to direct trip.

        <max_distance> (double): Max distance between combined origins/destinations.

        <min_efficiency> (double): Minimum efficiency threshold (0.0 - 1.0).

    Request Count: An integer N representing the total number of requests.

    Request Lines (N lines):

        <id> (string): Unique request identifier.

        <time> (long): Request timestamp.

        <origin_x> <origin_y> (doubles): Coordinates of the pickup location.

        <dest_x> <dest_y> (doubles): Coordinates of the drop-off location.

### Output Format

The program outputs one line per completed ride containing:

    Finish Time: The simulation time when the ride ended.

    Total Distance: The total distance covered by the vehicle.

    Number of Stops: The count of stops (including start and end).

    Route Coordinates: A sequence of X Y pairs representing the path taken.
