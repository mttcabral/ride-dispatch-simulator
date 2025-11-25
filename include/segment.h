#ifndef RIDE_DISPATCH_SIMULATOR_INCLUDE_SEGMENT_H_
#define RIDE_DISPATCH_SIMULATOR_INCLUDE_SEGMENT_H_

#include "stop.h"

/**
 * @brief Categorizes the nature of a segment within a ride's route.
 *
 * Segments are classified based on the type of stops at their endpoints.
 */
enum class SegmentType {
  kPickup,      /**< A segment connecting two pickup stops. */
  kDropoff,     /**< A segment connecting two drop-off stops. */
  kDisplacement /**< A segment connecting a pickup to a drop-off, or vice versa.
                 */
};

/**
 * @brief Represents a directed edge between two stops in a ride's route.
 *
 * A Segment encapsulates the spatial and temporal displacement of a vehicle
 * between two specific points (Stops). It stores references to the start and
 * end stops, the distance covered, the time taken, and the semantic type of
 * the segment (e.g., pickup, drop-off, or displacement).
 *
 * This class is a fundamental building block for constructing the route of a
 * Ride and calculating its total metrics.
 */
class Segment {
private:
  Stop *start_;      // Pointer to the starting stop of the segment.
  Stop *end_;        // Pointer to the ending stop of the segment.
  double distance_;  // Distance covered in this segment (spatial units).
  double time_;      // Time taken to traverse this segment (time units).
  SegmentType type_; // The semantic classification of the segment.

public:
  /**
   * @brief Default constructor.
   *
   * Initializes a Segment with null stops, zero distance/time, and default
   * type.
   */
  Segment();

  /**
   * @brief Parameterized constructor.
   *
   * Creates a fully initialized Segment.
   *
   * @param s Pointer to the starting Stop.
   * @param e Pointer to the ending Stop.
   * @param dist The distance between the stops.
   * @param t The time required to travel between the stops.
   * @param seg_type The type classification of the segment.
   */
  Segment(Stop *s, Stop *e, double dist, double t, SegmentType seg_type);

  /**
   * @brief Destructor.
   *
   * Note: The Segment does NOT own the Stop objects pointed to by start_ and
   * end_. Therefore, this destructor does not delete them.
   */
  ~Segment();

  /**
   * @brief Gets the starting stop of the segment.
   * @return Pointer to the start Stop.
   */
  Stop *GetStart() const;

  /**
   * @brief Gets the ending stop of the segment.
   * @return Pointer to the end Stop.
   */
  Stop *GetEnd() const;

  /**
   * @brief Gets the distance covered by the segment.
   * @return The distance value.
   */
  double GetDistance() const;

  /**
   * @brief Gets the time duration of the segment.
   * @return The time value.
   */
  double GetTime() const;

  /**
   * @brief Gets the type of the segment.
   * @return The SegmentType enum value.
   */
  SegmentType GetType() const;

  /**
   * @brief Sets the starting stop of the segment.
   * @param s Pointer to the new start Stop.
   */
  void SetStart(Stop *s);

  /**
   * @brief Sets the ending stop of the segment.
   * @param e Pointer to the new end Stop.
   */
  void SetEnd(Stop *e);

  /**
   * @brief Sets the distance of the segment.
   * @param dist The new distance value.
   */
  void SetDistance(double dist);

  /**
   * @brief Sets the time duration of the segment.
   * @param t The new time value.
   */
  void SetTime(double t);

  /**
   * @brief Sets the type of the segment.
   * @param t The new SegmentType enum value.
   */
  void SetType(SegmentType t);
};

#endif
