/**
 * @file main.cc
 * @brief Entry point for the Ride Dispatch Simulator.
 *
 * This file contains the main simulation loop, which processes a stream of
 * ride requests and dispatches them to vehicles using a greedy grouping
 * strategy. It then executes a Discrete Event Simulation (DES) to simulate
 * the movement of vehicles along their routes.
 *
 * The simulation proceeds in three phases:
 * 1. Greedy Grouping: Requests are grouped into rides based on constraints.
 * 2. Scheduling: Initial events are created for each formed ride.
 * 3. Simulation: Events are processed in chronological order to track vehicle
 *    movement and calculate final metrics.
 */

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "min_heap.h"
#include "request.h"
#include "ride.h"
#include "segment.h"
#include "stop.h"
#include "vector.h"

/**
 * @brief Calculates the Euclidean distance between two points.
 *
 * @param x1 X-coordinate of the first point.
 * @param y1 Y-coordinate of the first point.
 * @param x2 X-coordinate of the second point.
 * @param y2 Y-coordinate of the second point.
 * @return The Euclidean distance between (x1, y1) and (x2, y2).
 */
double CalculateDistance(double x1, double y1, double x2, double y2) {
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

/**
 * @brief Parses a coordinate string into X and Y components.
 *
 * Expects a string containing two space-separated numbers.
 *
 * @param coord The coordinate string to parse.
 * @param[out] x Reference to store the parsed X-coordinate.
 * @param[out] y Reference to store the parsed Y-coordinate.
 */
void ParseCoord(std::string coord, double &x, double &y) {
  std::stringstream ss(coord);
  ss >> x >> y;
}

/**
 * @brief Holds the configuration parameters for the simulation.
 */
struct SimulationParams {
  int capacity;         /**< Maximum number of passengers per vehicle. */
  double speed;         /**< Vehicle speed in distance units per time unit. */
  double max_wait_time; /**< Maximum allowed wait time for a passenger. */
  double max_delay;     /**< Maximum allowed delay for a passenger. */
  double max_distance; /**< Maximum distance between combined request points. */
  double min_efficiency; /**< Minimum required efficiency for a shared ride. */
};

/**
 * @brief Represents a discrete event in the simulation.
 *
 * Used to schedule and process vehicle movements.
 */
struct Event {
  double time; /**< The time at which the event occurs. */
  int type;
  Ride *ride;     /**< Pointer to the associated ride. */
  int stop_index; /**< Index of the next stop to process (0 to segments.size()).
                   */

  /**
   * @brief Comparator for MinHeap.
   * @param other The other event to compare against.
   * @return True if this event occurs before the other event.
   */
  bool operator<(const Event &other) const { return time < other.time; }
};

/**
 * @brief Main function of the simulator.
 *
 * 1. Reads simulation parameters and requests.
 * 2. Phase 1: Groups requests into rides using a greedy heuristic.
 * 3. Phase 2: Schedules initial events for the simulation.
 * 4. Phase 3: Runs the Discrete Event Simulation loop.
 * 5. Outputs the details of each completed ride.
 *
 * @return 0 on success.
 */
int main() {
  SimulationParams params;
  int num_requests;

  // Read simulation parameters
  if (!(std::cin >> params.capacity >> params.speed >> params.max_wait_time >>
        params.max_delay >> params.max_distance >> params.min_efficiency)) {
    return 0;
  }

  std::cin >> num_requests;

  Vector<Request *> all_requests;
  MinHeap<Event> event_queue;

  // Read requests
  for (int i = 0; i < num_requests; ++i) {
    std::string id;
    long time;
    double ox, oy, dx, dy;
    std::cin >> id >> time >> ox >> oy >> dx >> dy;

    std::string origin = std::to_string(ox) + " " + std::to_string(oy);
    std::string dest = std::to_string(dx) + " " + std::to_string(dy);

    Request *req = new Request(id, time, origin, dest);
    all_requests.push_back(req);
  }

  Vector<Ride *> completed_rides;

  // Phase 1: Greedy Grouping Strategy
  // Iterates through requests and attempts to group them into rides.
  size_t i = 0;
  while (i < all_requests.size()) {
    // Start a new ride with the current request
    Ride *r = new Ride();
    r->AddRequest(all_requests[i]);
    r->UpdateRoute(params.speed);
    i++;

    // Try to add subsequent requests to this ride
    while (i < all_requests.size()) {
      Request *next_req = all_requests[i];

      // Constraint 1: Vehicle Capacity
      if (r->GetDemandCount() >= params.capacity)
        break;

      // Constraint 2: Distance Proximity
      bool dist_ok = true;
      double req_ox, req_oy, req_dx, req_dy;
      ParseCoord(next_req->GetOrigin(), req_ox, req_oy);
      ParseCoord(next_req->GetDestination(), req_dx, req_dy);

      for (int k = 0; k < r->GetDemandCount(); ++k) {
        std::string other_id = r->GetDemandId(k);
        Request *other_req = nullptr;
        // Find the request object for the ID
        for (size_t x = 0; x < all_requests.size(); ++x) {
          if (all_requests[x]->GetId() == other_id) {
            other_req = all_requests[x];
            break;
          }
        }
        double other_ox, other_oy, other_dx, other_dy;
        ParseCoord(other_req->GetOrigin(), other_ox, other_oy);
        ParseCoord(other_req->GetDestination(), other_dx, other_dy);

        if (CalculateDistance(req_ox, req_oy, other_ox, other_oy) >
                params.max_distance ||
            CalculateDistance(req_dx, req_dy, other_dx, other_dy) >
                params.max_distance) {
          dist_ok = false;
          break;
        }
      }
      if (!dist_ok)
        break;

      // Constraint 3: Efficiency
      Ride temp_ride;
      for (int k = 0; k < r->GetDemandCount(); ++k) {
        std::string other_id = r->GetDemandId(k);
        for (size_t x = 0; x < all_requests.size(); ++x) {
          if (all_requests[x]->GetId() == other_id) {
            temp_ride.AddRequest(all_requests[x]);
            break;
          }
        }
      }
      temp_ride.AddRequest(next_req);
      temp_ride.UpdateRoute(params.speed);

      if (temp_ride.GetEfficiency() < params.min_efficiency)
        break;

      // Constraint 4: Max Delay
      std::string first_id = r->GetDemandId(0);
      Request *first_req = nullptr;
      for (size_t x = 0; x < all_requests.size(); ++x) {
        if (all_requests[x]->GetId() == first_id) {
          first_req = all_requests[x];
          break;
        }
      }
      if (std::abs(next_req->GetRequestTime() - first_req->GetRequestTime()) >
          params.max_delay)
        break;

      // All constraints passed, add request to the ride
      r->AddRequest(next_req);
      r->UpdateRoute(params.speed);
      i++;
    }

    completed_rides.push_back(r);
  }

  // Phase 2: Scheduling
  // Schedule the first event for each formed ride.
  for (size_t k = 0; k < completed_rides.size(); ++k) {
    Ride *r = completed_rides[k];

    // Find the start time based on the first request's time
    std::string first_id = r->GetDemandId(0);
    Request *first_req = nullptr;
    for (size_t x = 0; x < all_requests.size(); ++x) {
      if (all_requests[x]->GetId() == first_id) {
        first_req = all_requests[x];
        break;
      }
    }

    Event e;
    e.time = (double)first_req->GetRequestTime();
    e.type = 0;
    e.ride = r;
    e.stop_index = 0; // Start at the beginning of the route
    event_queue.push(e);
  }

  // Phase 3: Simulation Loop
  double current_time = 0;
  while (!event_queue.empty()) {
    Event e = event_queue.top();
    event_queue.pop();

    current_time = e.time;
    Ride *r = e.ride;

    // If it has more segments to process
    if (e.stop_index < r->GetSegmentCount()) {
      Segment *seg = r->GetSegment(e.stop_index);

      // Calculate travel time for this segment
      double travel_time = seg->GetTime();

      // Schedule next event (arrival at next stop)
      Event next_event;
      next_event.time = current_time + travel_time;
      next_event.type = 0;
      next_event.ride = r;
      next_event.stop_index = e.stop_index + 1;
      event_queue.push(next_event);
    } else {
      // Ride Finished
      // Output Results
      double start_time = 0;
      // Re-find start time for output
      std::string first_id = r->GetDemandId(0);
      Request *first_req = nullptr;
      for (size_t x = 0; x < all_requests.size(); ++x) {
        if (all_requests[x]->GetId() == first_id) {
          first_req = all_requests[x];
          break;
        }
      }
      start_time = (double)first_req->GetRequestTime();
      double duration = r->GetTotalDuration();
      double end_time = start_time + duration;

      // Use current_time as the definitive end time from simulation

      std::cout << std::fixed << std::setprecision(2) << end_time << " "
                << r->GetTotalDistance() << " " << (r->GetSegmentCount() + 1)
                << " ";

      for (int j = 0; j < r->GetSegmentCount(); ++j) {
        Segment *s = r->GetSegment(j);
        if (j == 0) {
          double x, y;
          ParseCoord(s->GetStart()->GetCoordinate(), x, y);
          std::cout << x << " " << y;
        }
        double x, y;
        ParseCoord(s->GetEnd()->GetCoordinate(), x, y);
        std::cout << " " << x << " " << y;
      }
      std::cout << std::endl;
    }
  }

  // Cleanup
  for (size_t k = 0; k < completed_rides.size(); ++k) {
    delete completed_rides[k];
  }
  for (size_t k = 0; k < all_requests.size(); ++k) {
    delete all_requests[k];
  }

  return 0;
}