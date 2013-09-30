//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// class map

// size_type max_size() const;

#include <map>
#include <cassert>
#include "../../../../rbmap.h"

void max_size()
{
	std::cout << "    size_type max_size() const" << std::endl;
    typedef rbmap<int, double> M;
    M m;
    assert(m.max_size() != 0);
}
