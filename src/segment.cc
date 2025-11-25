#include "segment.h"

Segment::Segment()
    : start_(nullptr), end_(nullptr), distance_(0.0), time_(0.0),
      type_(SegmentType::kDisplacement) {}

Segment::Segment(Stop *s, Stop *e, double dist, double t, SegmentType seg_type)
    : start_(s), end_(e), distance_(dist), time_(t), type_(seg_type) {}

Segment::~Segment() {}

Stop *Segment::GetStart() const { return start_; }

Stop *Segment::GetEnd() const { return end_; }

double Segment::GetDistance() const { return distance_; }

double Segment::GetTime() const { return time_; }

SegmentType Segment::GetType() const { return type_; }

void Segment::SetStart(Stop *s) { start_ = s; }

void Segment::SetEnd(Stop *e) { end_ = e; }

void Segment::SetDistance(double dist) { distance_ = dist; }

void Segment::SetTime(double t) { time_ = t; }

void Segment::SetType(SegmentType t) { type_ = t; }
