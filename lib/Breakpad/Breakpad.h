// Copyright (c) 2018-2022, The Deocoin Group.
//
// Licensed under the GNU General Public License, Version 3.
// See the file LICENSE from this package for details.

#pragma once

#include <string>

namespace google_breakpad {
class ExceptionHandler;
} // namespace google_breakpad

namespace Deocoin {

namespace Breakpad {

class ExceptionHandler
{
public:
    explicit ExceptionHandler(const std::string &dumpPath = std::string());
    virtual ~ExceptionHandler();

    static void dummyCrash();

private:
    google_breakpad::ExceptionHandler *m_exceptionHandler = nullptr;
};

} // namespace Breakpad

} // namespace Deocoin
