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

// explicit map(const key_compare& comp);

#include <map>
#include <cassert>

#include "../../test_compare.h"
#include "../../../../rbmap.h"

void compare()
{
	std::cout << "    explicit map(const key_compare& comp)" << std::endl;
    typedef test_compare<std::less<int> > C;
    rbmap<int, double, C> m(C(3));
    assert(m.empty());
    assert(m.begin() == m.end());
    assert(m.key_comp() == C(3));
}
