#ifndef RIDE_DISPATCH_SIMULATOR_INCLUDE_STOP_H_
#define RIDE_DISPATCH_SIMULATOR_INCLUDE_STOP_H_

#include <string>

/**
 * @brief Enumerates the possible types of stops in a ride.
 *
 * Distinguishes between points where passengers are picked up and points where
 * they are dropped off.
 */
enum class StopType {
  kPickup, /**< A stop where a passenger boards the vehicle. */
  kDropoff /**< A stop where a passenger alights from the vehicle. */
};

/**
 * @brief Represents a specific location and action within a ride's route.
 *
 * A Stop encapsulates the essential details of a visit to a location: the
 * spatial coordinates, the nature of the action (pickup or drop-off), and the
 * identifier of the passenger associated with this action.
 *
 * This class serves as a node in the route graph, defining the sequence of
 * operations a vehicle must perform.
 */
class Stop {
private:
  std::string coordinate_; // The location identifier or coordinate.
  StopType type_;          // The type of operation at this stop.
  std::string passenger_id_;

public:
  /**
   * @brief Default constructor.
   *
   * Initializes a Stop with empty coordinate/passenger ID and default type.
   */
  Stop();

  /**
   * @brief Parameterized constructor.
   *
   * Creates a fully initialized Stop.
   *
   * @param coord The string representation of the coordinate.
   * @param t The type of the stop (kPickup or kDropoff).
   * @param pid The unique identifier of the passenger.
   */
  Stop(std::string coord, StopType t, std::string pid);

  /**
   * @brief Destructor.
   */
  ~Stop();

  /**
   * @brief Gets the coordinate of the stop.
   * @return The coordinate string.
   */
  std::string GetCoordinate() const;

  /**
   * @brief Gets the type of the stop.
   * @return The StopType enum value.
   */
  StopType GetType() const;

  /**
   * @brief Gets the ID of the passenger associated with this stop.
   * @return The passenger ID string.
   */
  std::string GetPassengerId() const;

  /**
   * @brief Sets the coordinate of the stop.
   * @param coord The new coordinate string.
   */
  void SetCoordinate(std::string coord);

  /**
   * @brief Sets the type of the stop.
   * @param t The new StopType enum value.
   */
  void SetType(StopType t);

  /**
   * @brief Sets the passenger ID for this stop.
   * @param pid The new passenger ID string.
   */
  void SetPassengerId(std::string pid);
};

#endif
