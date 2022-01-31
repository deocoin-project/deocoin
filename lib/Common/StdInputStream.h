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

#include <istream>
#include <Common/IInputStream.h>

namespace Common {

class StdInputStream : public IInputStream
{
public:
    explicit StdInputStream(std::istream &in);

    size_t readSome(void *data, size_t size) override;

    StdInputStream &operator=(const StdInputStream &) = delete;

private:
    std::istream &in;
};

} // namespace Common