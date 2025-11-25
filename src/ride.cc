#include "ride.h"

#include <cmath>
#include <iostream>
#include <sstream>

#include "request.h"

Ride::Ride() : total_distance_(0.0), total_duration_(0.0), efficiency_(0.0) {}

Ride::~Ride() {
  for (size_t i = 0; i < segments_.size(); ++i) {
    delete segments_[i];
  }
}

void Ride::AddRequest(Request *request) { requests_.push_back(request); }

void Ride::AddSegment(Segment *segment) {
  segments_.push_back(segment);
  total_distance_ += segment->getDistance();
  total_duration_ += segment->getTime();
}

// Helper to calculate distance between two coordinate strings
double calcDist(std::string c1, std::string c2) {
  double x1, y1, x2, y2;
  std::stringstream ss1(c1);
  ss1 >> x1 >> y1;
  std::stringstream ss2(c2);
  ss2 >> x2 >> y2;
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

void Ride::UpdateRoute(double speed) {
  // Clear existing segments
  for (size_t i = 0; i < segments_.size(); ++i) {
    delete segments_[i];
  }
  segments_.clear();
  total_distance_ = 0;
  total_duration_ = 0;

  if (requests_.empty())
    return;

  // Create Stops
  Vector<Stop *> stops;
  // Pickups
  for (size_t i = 0; i < requests_.size(); ++i) {
    stops.push_back(
        new Stop(requests_[i]->GetOrigin(), PICKUP, requests_[i]->GetId()));
  }
  // Dropoffs
  for (size_t i = 0; i < requests_.size(); ++i) {
    stops.push_back(new Stop(requests_[i]->GetDestination(), DROPOFF,
                             requests_[i]->GetId()));
  }

  // Create Segments connecting stops
  for (size_t i = 0; i < stops.size() - 1; ++i) {
    Stop *start = stops[i];
    Stop *end = stops[i + 1];
    double dist = calcDist(start->getCoordinate(), end->getCoordinate());
    double time = (speed > 0) ? dist / speed : 0;

    SegmentType type = DISPLACEMENT_SEGMENT;

    if (start->getType() == PICKUP && end->getType() == PICKUP) {
      type = PICKUP_SEGMENT;
    } else if (start->getType() == DROPOFF && end->getType() == DROPOFF) {
      type = DROPOFF_SEGMENT;
    } else {
      type = DISPLACEMENT_SEGMENT;
    }

    AddSegment(new Segment(start, end, dist, time, type));
  }

  CalculateEfficiency();
}

void Ride::CalculateEfficiency() {
  if (total_distance_ == 0) {
    efficiency_ = 0.0;
    return;
  }

  // Efficiency = (Sum of Direct Distances) / Total Distance
  double sum_direct = 0.0;
  for (size_t i = 0; i < requests_.size(); ++i) {
    sum_direct +=
        calcDist(requests_[i]->GetOrigin(), requests_[i]->GetDestination());
  }

  efficiency_ = sum_direct / total_distance_;
}

int Ride::GetDemandCount() const { return requests_.size(); }

std::string Ride::GetDemandId(int index) const {
  if (index >= 0 && index < (int)requests_.size()) {
    return requests_[index]->GetId();
  }
  return "";
}

int Ride::GetSegmentCount() const { return segments_.size(); }

Segment *Ride::GetSegment(int index) const {
  if (index >= 0 && index < (int)segments_.size()) {
    return segments_[index];
  }
  return nullptr;
}

double Ride::GetTotalDistance() const { return total_distance_; }

double Ride::GetTotalDuration() const { return total_duration_; }

double Ride::GetEfficiency() const { return efficiency_; }

void Ride::SetEfficiency(double eff) { efficiency_ = eff; }
