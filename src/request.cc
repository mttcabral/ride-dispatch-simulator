#include "request.h"
#include "ride.h"

Request::Request()
    : request_time_(0), state_(kRequested), associated_ride_(nullptr) {}

Request::Request(std::string id, long time, std::string origin,
                 std::string dest)
    : id_(id), request_time_(time), origin_(origin), destination_(dest),
      state_(kRequested), associated_ride_(nullptr) {}

Request::~Request() {}

std::string Request::GetId() const { return id_; }

long Request::GetRequestTime() const { return request_time_; }

std::string Request::GetOrigin() const { return origin_; }

std::string Request::GetDestination() const { return destination_; }

RequestState Request::GetState() const { return state_; }

Ride *Request::GetAssociatedRide() const { return associated_ride_; }

void Request::SetId(std::string id) { id_ = id; }

void Request::SetRequestTime(long time) { request_time_ = time; }

void Request::SetOrigin(std::string origin) { origin_ = origin; }

void Request::SetDestination(std::string dest) { destination_ = dest; }

void Request::SetAssociatedRide(Ride *ride) { associated_ride_ = ride; }

void Request::UpdateState(RequestState new_state) { state_ = new_state; }
