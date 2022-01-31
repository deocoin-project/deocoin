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

#pragma once

#include <cstdint>
#include <string>

namespace System {

class Dispatcher;
class Ipv4Address;
class TcpConnection;

class TcpConnector
{
public:
    TcpConnector();
    explicit TcpConnector(Dispatcher &dispatcher);
    TcpConnector(const TcpConnector &) = delete;
    TcpConnector(TcpConnector &&other) noexcept;
    ~TcpConnector();

    TcpConnection connect(const Ipv4Address &address, uint16_t port);

    TcpConnector &operator=(const TcpConnector &) = delete;
    TcpConnector &operator=(TcpConnector &&other) noexcept;

private:
    void *context;
    Dispatcher *dispatcher;
};

} // namespace System
