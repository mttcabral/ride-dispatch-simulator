#include "stop.h"

Stop::Stop() {}

Stop::Stop(std::string coord, StopType t, std::string pid)
    : coordinate_(coord), type_(t), passenger_id_(pid) {}

Stop::~Stop() {}

std::string Stop::GetCoordinate() const { return coordinate_; }

StopType Stop::GetType() const { return type_; }

std::string Stop::GetPassengerId() const { return passenger_id_; }

void Stop::SetCoordinate(std::string coord) { coordinate_ = coord; }

void Stop::SetType(StopType t) { type_ = t; }

void Stop::SetPassengerId(std::string pid) { passenger_id_ = pid; }
