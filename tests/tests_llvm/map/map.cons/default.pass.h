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

// map();

#include <map>
#include <cassert>

#include "../../../../rbmap.h"

void _default()
{
	std::cout << "    map()" << std::endl;
    rbmap<int, double> m;
    assert(m.empty());
    assert(m.begin() == m.end());
}
