#ifndef RIDE_DISPATCH_SIMULATOR_INCLUDE_RIDE_H_
#define RIDE_DISPATCH_SIMULATOR_INCLUDE_RIDE_H_

#include <string>

#include "segment.h"
#include "vector.h"

class Request;

/**
 * @brief Represents a ride in the dispatch system.
 *
 * A Ride is a collection of one or more requests that are served together by a
 * single vehicle. It manages the sequence of segments (route) that the vehicle
 * must traverse to fulfill these requests, including pickups and drop-offs.
 *
 * This class encapsulates the logic for aggregating requests, calculating route
 * metrics (distance, duration), and evaluating the efficiency of the ride,
 * which is a key metric for the ride-sharing algorithm.
 *
 * It utilizes a custom `Vector` implementation for dynamic array management,
 * adhering to the project's constraint of avoiding STL containers.
 */
class Ride {
private:
  Vector<Request *> requests_; // List of requests satisfied by this ride.
  Vector<Segment *> segments_; // Sequence of segments forming the route.

  double total_distance_; // Total distance of the ride in spatial units.
  double total_duration_; // Total duration of the ride in time units.
  double efficiency_;     // Efficiency score (0.0 to 1.0).

public:
  /**
   * @brief Default constructor.
   *
   * Initializes a new Ride instance with zero distance, duration, and
   * efficiency.
   */
  Ride();

  /**
   * @brief Destructor.
   *
   * Responsible for freeing the memory allocated for segments. Note that it
   * does NOT own the Request objects, so they are not deleted here.
   */
  ~Ride();

  /**
   * @brief Adds a request to the ride.
   *
   * Appends a new request to the list of requests served by this ride.
   * Note that this does not automatically update the route; `UpdateRoute` must
   * be called subsequently to regenerate the segments.
   *
   * @param request Pointer to the Request object to be added.
   */
  void AddRequest(Request *request);

  /**
   * @brief Adds a segment to the ride's route.
   *
   * Appends a segment to the current route and updates the total distance and
   * duration of the ride.
   *
   * @param segment Pointer to the Segment object to be added. The Ride takes
   * ownership of this segment.
   */
  void AddSegment(Segment *segment);

  /**
   * @brief Calculates and updates the efficiency metric of the ride.
   *
   * Efficiency is defined as the ratio of the sum of the direct distances of
   * all individual requests to the total distance of the combined ride.
   *
   * Formula: Efficiency = (Sum of direct distances) / (Total ride distance)
   */
  void CalculateEfficiency();

  /**
   * @brief Regenerates the route (segments) based on the current list of
   * requests.
   *
   * This method clears the existing segments and creates a new sequence of
   * segments that visits all pickup locations followed by all drop-off
   * locations in the order the requests were added. It also recalculates the
   * total distance, duration, and efficiency.
   *
   * @param speed The speed of the vehicle, used to calculate segment durations.
   */
  void UpdateRoute(double speed);

  /**
   * @brief Gets the number of requests currently assigned to this ride.
   * @return The count of requests.
   */
  int GetDemandCount() const;

  /**
   * @brief Gets the ID of a specific demand (request) in the ride.
   * @param index The index of the request.
   * @return The ID string of the request, or an empty string if index is
   * invalid.
   */
  std::string GetDemandId(int index) const;

  /**
   * @brief Gets the number of segments in the ride's route.
   * @return The count of segments.
   */
  int GetSegmentCount() const;

  /**
   * @brief Gets a pointer to a specific segment in the route.
   * @param index The index of the segment.
   * @return Pointer to the Segment, or nullptr if index is invalid.
   */
  Segment *GetSegment(int index) const;

  /**
   * @brief Gets the total distance of the ride.
   * @return The total distance.
   */
  double GetTotalDistance() const;

  /**
   * @brief Gets the total duration of the ride.
   * @return The total duration.
   */
  double GetTotalDuration() const;

  /**
   * @brief Gets the efficiency score of the ride.
   * @return The efficiency value.
   */
  double GetEfficiency() const;

  /**
   * @brief Sets the efficiency score of the ride manually.
   * @param eff The new efficiency value.
   */
  void SetEfficiency(double eff);
};

#endif
