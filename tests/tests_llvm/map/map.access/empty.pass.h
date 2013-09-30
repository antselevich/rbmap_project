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

// bool empty() const;

#include <map>
#include "../../../../rbmap.h"
#include <cassert>

void empty()
{
	std::cout << "    bool empty() const" << std::endl;
    typedef rbmap<int, double> M;
    M m;
    assert(m.empty());
    m.insert(M::value_type(1, 1.5));
    assert(!m.empty());
    m.clear();
    assert(m.empty());
}
