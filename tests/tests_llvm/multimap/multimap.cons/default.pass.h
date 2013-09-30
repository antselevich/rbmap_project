//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// class multimap

// multimap();

#include <map>
#include <cassert>

#include "../../../../rbmap.h"

void multi_default()
{
	std::cout << "    multimap()" << std::endl;
    rbmultimap<int, double> m;
    assert(m.empty());
    assert(m.begin() == m.end());
}
