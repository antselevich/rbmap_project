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

// size_type size() const;

#include <map>
#include <cassert>
#include "../../../../rbmap.h"

void size()
{
	std::cout << "    size_type size() const" << std::endl;
    typedef rbmap<int, double> M;
    M m;
    assert(m.size() == 0);
    m.insert(M::value_type(2, 1.5));
    assert(m.size() == 1);
    m.insert(M::value_type(1, 1.5));
    assert(m.size() == 2);
    m.insert(M::value_type(3, 1.5));
    assert(m.size() == 3);
    m.erase(m.begin());
    assert(m.size() == 2);
    m.erase(m.begin());
    assert(m.size() == 1);
    m.erase(m.begin());
    assert(m.size() == 0);
}