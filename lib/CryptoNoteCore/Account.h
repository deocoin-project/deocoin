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

#include <crypto/crypto.h>
#include <CryptoNoteCore/CryptoNoteBasic.h>

namespace CryptoNote {

class ISerializer;

class AccountBase
{
public:
    AccountBase();

    void generate();
    void generateDeterministic();
    Crypto::SecretKey generate_key(
        const Crypto::SecretKey &recovery_key = Crypto::SecretKey(),
        bool recover = false,
        bool two_random = false);

    static void generateViewFromSpend(Crypto::SecretKey &, Crypto::SecretKey &,Crypto::PublicKey &);
    static void generateViewFromSpend(Crypto::SecretKey &, Crypto::SecretKey &);

    const AccountKeys &getAccountKeys() const;
    void setAccountKeys(const AccountKeys& keys);

    uint64_t get_createtime() const { return m_creation_timestamp; }
    void set_createtime(uint64_t val) { m_creation_timestamp = val; }

    void serialize(ISerializer &s);

    template <class t_archive>
    inline void serialize(t_archive &a, const unsigned int)
    {
        a & m_keys;
        a & m_creation_timestamp;
    }

private:
    void setNull();

private:
    AccountKeys m_keys;
    uint64_t m_creation_timestamp;
};

} // namespace CryptoNote
