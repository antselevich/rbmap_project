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
#include "../../../../rbmap.h"

struct X
{
    rbmultimap<int, X> m;
};

void default_recursive()
{
	std::cout << "    map()" << std::endl;
}
