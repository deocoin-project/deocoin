// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The Karbowanec developers
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

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <Global/CryptoNoteConfig.h>

#pragma once

namespace CryptoNote {

namespace {

boost::uuids::uuid name;
boost::uuids::name_generator gen(name);
boost::uuids::uuid u = gen("010301ff0001a2e2d38d3d029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd08807121016e445497e339097337f430e551acfe3564068cd7570703965fb9ca6a4377c856.1.1.1");
} // namespace

const static boost::uuids::uuid DEOCOIN_NETWORK = u;

} // namespace CryptoNote
