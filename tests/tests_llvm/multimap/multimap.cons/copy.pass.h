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

// multimap(const multimap& m);

#include <map>
#include <cassert>

#include "../../test_compare.h"
#include "../../test_allocator.h"

#include "../../../../rbmap.h"

void multi_copy()
{
	std::cout << "    multimap(const multimap& m)" << std::endl;
    {
        typedef std::pair<const int, double> V;
        V ar[] =
        {
            V(1, 1),
            V(1, 1.5),
            V(1, 2),
            V(2, 1),
            V(2, 1.5),
            V(2, 2),
            V(3, 1),
            V(3, 1.5),
            V(3, 2),
        };
        typedef test_compare<std::less<int> > C;
        typedef test_allocator<V> A;
        rbmultimap<int, double, C, A> mo(ar, ar+sizeof(ar)/sizeof(ar[0]), C(5), A(7));
        rbmultimap<int, double, C, A> m = mo;
        assert(m == mo);
        assert(m.get_allocator() == A(7));
        assert(m.key_comp() == C(5));

        assert(mo.get_allocator() == A(7));
        assert(mo.key_comp() == C(5));
    }
}
