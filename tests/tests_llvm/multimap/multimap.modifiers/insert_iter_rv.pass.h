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

// template <class P>
//     iterator insert(const_iterator position, P&& p);

#include <map>
#include <cassert>

#include "../../MoveOnly.h"

#include "../../../../rbmap.h"

void multi_insert_iter_rv()
{
	std::cout << "    iterator insert(const_iterator position, P&& p)" << std::endl;
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    {
        typedef rbmultimap<int, MoveOnly> M;
        typedef std::pair<int, MoveOnly> P;
        typedef M::iterator R;
        M m;
        R r = m.insert(m.end(), P(2, 2));
        assert(r == m.begin());
        assert(m.size() == 1);
        assert(r->first == 2);
        assert(r->second == 2);

        r = m.insert(m.end(), P(1, 1));
        assert(r == m.begin());
        assert(m.size() == 2);
        assert(r->first == 1);
        assert(r->second == 1);

        r = m.insert(m.end(), P(3, 3));
        assert(r == prev(m.end()));
        assert(m.size() == 3);
        assert(r->first == 3);
        assert(r->second == 3);

        r = m.insert(m.end(), P(3, 2));
        assert(r == prev(m.end()));
        assert(m.size() == 4);
        assert(r->first == 3);
        assert(r->second == 2);
    }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
}
