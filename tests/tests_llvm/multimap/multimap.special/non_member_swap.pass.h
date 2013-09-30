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

// template <class Key, class T, class Compare, class Allocator>
//   void
//   swap(multimap<Key, T, Compare, Allocator>& x, multimap<Key, T, Compare, Allocator>& y);

#include <map>
#include <cassert>
#include "../../test_allocator.h"
#include "../../test_compare.h"

#include "../../../../rbmap.h"

void multi_non_member_swap()
{
	std::cout << "    void swap(multimap<Key, T, Compare, Allocator>& x, multimap<Key, T, Compare, Allocator>& y)" << std::endl;
    typedef std::pair<const int, double> V;
    typedef rbmultimap<int, double> M;
    {
        V ar1[] =
        {
			V(0,0.0),
        };
        V ar2[] =
        {
			V(0,0.0),
        };
        M m1(ar1, ar1);
        M m2(ar2, ar2);
        M m1_save = m1;
        M m2_save = m2;
        swap(m1, m2);
        assert(m1 == m2_save);
        assert(m2 == m1_save);
    }
    {
        V ar1[] =
        {
			V(0,0.0),
        };
        V ar2[] =
        {
            V(5, 5),
            V(6, 6),
            V(7, 7),
            V(8, 8),
            V(9, 9),
            V(10, 10),
            V(11, 11),
            V(12, 12)
        };
        M m1(ar1, ar1);
        M m2(ar2, ar2+sizeof(ar2)/sizeof(ar2[0]));
        M m1_save = m1;
        M m2_save = m2;
        swap(m1, m2);
        assert(m1 == m2_save);
        assert(m2 == m1_save);
    }
    {
        V ar1[] =
        {
            V(1, 1),
            V(2, 2),
            V(3, 3),
            V(4, 4)
        };
        V ar2[] =
        {
			V(0,0.0),
        };
        M m1(ar1, ar1+sizeof(ar1)/sizeof(ar1[0]));
        M m2(ar2, ar2);
        M m1_save = m1;
        M m2_save = m2;
        swap(m1, m2);
        assert(m1 == m2_save);
        assert(m2 == m1_save);
    }
    {
        V ar1[] =
        {
            V(1, 1),
            V(2, 2),
            V(3, 3),
            V(4, 4)
        };
        V ar2[] =
        {
            V(5, 5),
            V(6, 6),
            V(7, 7),
            V(8, 8),
            V(9, 9),
            V(10, 10),
            V(11, 11),
            V(12, 12)
        };
        M m1(ar1, ar1+sizeof(ar1)/sizeof(ar1[0]));
        M m2(ar2, ar2+sizeof(ar2)/sizeof(ar2[0]));
        M m1_save = m1;
        M m2_save = m2;
        swap(m1, m2);
        assert(m1 == m2_save);
        assert(m2 == m1_save);
    }
}
