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

// iterator erase(const_iterator first, const_iterator last);

#include <map>
#include <cassert>

#include "../../../../rbmap.h"

void multi_erase_iter_iter()
{
	std::cout << "    iterator erase(const_iterator first, const_iterator last)" << std::endl;
    {
        typedef rbmultimap<int, double> M;
        typedef std::pair<int, double> P;
        typedef M::iterator I;
        P ar[] =
        {
            P(1, 1.5),
            P(2, 2.5),
            P(3, 3.5),
            P(4, 4.5),
            P(5, 5.5),
            P(6, 6.5),
            P(7, 7.5),
            P(8, 8.5),
        };
        M m(ar, ar + sizeof(ar)/sizeof(ar[0]));
        assert(m.size() == 8);
        I i = m.erase(m.begin(), m.begin());
        assert(m.size() == 8);
        assert(i == m.begin());
        assert(m.begin()->first == 1);
        assert(m.begin()->second == 1.5);
        assert(next(m.begin())->first == 2);
        assert(next(m.begin())->second == 2.5);
        assert(next(m.begin(), 2)->first == 3);
        assert(next(m.begin(), 2)->second == 3.5);
        assert(next(m.begin(), 3)->first == 4);
        assert(next(m.begin(), 3)->second == 4.5);
        assert(next(m.begin(), 4)->first == 5);
        assert(next(m.begin(), 4)->second == 5.5);
        assert(next(m.begin(), 5)->first == 6);
        assert(next(m.begin(), 5)->second == 6.5);
        assert(next(m.begin(), 6)->first == 7);
        assert(next(m.begin(), 6)->second == 7.5);
        assert(next(m.begin(), 7)->first == 8);
        assert(next(m.begin(), 7)->second == 8.5);

        i = m.erase(m.begin(), next(m.begin(), 2));
        assert(m.size() == 6);
        assert(i == m.begin());
        assert(next(m.begin(), 0)->first == 3);
        assert(next(m.begin(), 0)->second == 3.5);
        assert(next(m.begin(), 1)->first == 4);
        assert(next(m.begin(), 1)->second == 4.5);
        assert(next(m.begin(), 2)->first == 5);
        assert(next(m.begin(), 2)->second == 5.5);
        assert(next(m.begin(), 3)->first == 6);
        assert(next(m.begin(), 3)->second == 6.5);
        assert(next(m.begin(), 4)->first == 7);
        assert(next(m.begin(), 4)->second == 7.5);
        assert(next(m.begin(), 5)->first == 8);
        assert(next(m.begin(), 5)->second == 8.5);

        i = m.erase(next(m.begin(), 2), next(m.begin(), 6));
        assert(m.size() == 2);
        assert(i == next(m.begin(), 2));
        assert(next(m.begin(), 0)->first == 3);
        assert(next(m.begin(), 0)->second == 3.5);
        assert(next(m.begin(), 1)->first == 4);
        assert(next(m.begin(), 1)->second == 4.5);

        i = m.erase(m.begin(), m.end());
        assert(m.size() == 0);
        assert(i == m.begin());
        assert(i == m.end());
    }
}