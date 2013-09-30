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

// size_type max_size() const;

#include <map>
#include <cassert>

#include "../../../rbmap.h"

void multi_max_size()
{
	std::cout << "    size_type max_size() const" << std::endl;
    typedef rbmultimap<int, double> M;
    M m;
    assert(m.max_size() != 0);
}
