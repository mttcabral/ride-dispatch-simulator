#ifndef RIDE_DISPATCH_SIMULATOR_INCLUDE_REQUEST_H_
#define RIDE_DISPATCH_SIMULATOR_INCLUDE_REQUEST_H_

#include <string>

class Ride;

/**
 * @brief Represents the lifecycle states of a ride request.
 */
enum RequestState {
  kRequested,  /**< Initial state when request is created. */
  kIndividual, /**< Assigned to an individual ride. */
  kCombined,   /**< Assigned to a shared/combined ride. */
  kCompleted   /**< Ride has been completed. */
};

/**
 * @brief Represents a passenger's request for a ride.
 *
 * Encapsulates all details regarding a ride request, including origin,
 * destination, timestamp, and its current processing state within the dispatch
 * system. It acts as the primary data unit for the scheduling algorithm.
 */
class Request {
private:
  std::string id_;          // Unique identifier for the request.
  long request_time_;       // Timestamp of when the request was placed.
  std::string origin_;      // Starting coordinates.
  std::string destination_; // Ending coordinates.
  RequestState state_;      // Current status of the request.
  Ride *associated_ride_;   // Pointer to the ride fulfilling this request.

public:
  /**
   * @brief Default constructor.
   *
   * Initializes a request with default values and state set to kRequested.
   */
  Request();

  /**
   * @brief Parameterized constructor.
   *
   * @param id Unique identifier for the request.
   * @param time Timestamp of the request.
   * @param origin Origin coordinates as a string.
   * @param dest Destination coordinates as a string.
   */
  Request(std::string id, long time, std::string origin, std::string dest);

  /**
   * @brief Destructor.
   */
  ~Request();

  /**
   * @brief Gets the unique identifier of the request.
   * @return The request ID.
   */
  std::string GetId() const;

  /**
   * @brief Gets the timestamp when the request was made.
   * @return The request time.
   */
  long GetRequestTime() const;

  /**
   * @brief Gets the origin coordinates.
   * @return The origin string.
   */
  std::string GetOrigin() const;

  /**
   * @brief Gets the destination coordinates.
   * @return The destination string.
   */
  std::string GetDestination() const;

  /**
   * @brief Gets the current state of the request.
   * @return The current RequestState.
   */
  RequestState GetState() const;

  /**
   * @brief Gets the ride currently associated with this request.
   * @return Pointer to the associated Ride, or nullptr if none.
   */
  Ride *GetAssociatedRide() const;

  /**
   * @brief Sets the unique identifier for the request.
   * @param id The new ID.
   */
  void SetId(std::string id);

  /**
   * @brief Sets the request timestamp.
   * @param time The new timestamp.
   */
  void SetRequestTime(long time);

  /**
   * @brief Sets the origin coordinates.
   * @param origin The new origin string.
   */
  void SetOrigin(std::string origin);

  /**
   * @brief Sets the destination coordinates.
   * @param dest The new destination string.
   */
  void SetDestination(std::string dest);

  /**
   * @brief Associates a ride with this request.
   * @param ride Pointer to the Ride object.
   */
  void SetAssociatedRide(Ride *ride);

  /**
   * @brief Updates the processing state of the request.
   * @param new_state The new state to transition to.
   */
  void UpdateState(RequestState new_state);
};

#endif
