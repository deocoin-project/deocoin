// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2022, The Deocoin Group.
//
// This file is part of Deocoin.
//
// Deocoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Deocoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Deocoin.  If not, see <http://www.gnu.org/licenses/>.

#include "EventWaiter.h"

void EventWaiter::notify() {
  std::unique_lock<std::mutex> lck(mtx);
  available = true;
  cv.notify_all();
}

void EventWaiter::wait() {
  std::unique_lock<std::mutex> lck(mtx);
  cv.wait(lck, [this]() { return available; });
  available = false;
}

bool EventWaiter::wait_for(const std::chrono::milliseconds& rel_time) {
  std::unique_lock<std::mutex> lck(mtx);
  auto result = cv.wait_for(lck, rel_time, [this]() { return available; });
  available = false;
  return result;
}
