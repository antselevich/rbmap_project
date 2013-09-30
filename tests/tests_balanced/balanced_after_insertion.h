#include "../../rbmap.h"
#include <iostream>
#include <cassert>

void balanced_after_insertion() {
	std::cout << "  balanced after insertion" << std::endl;
    typedef std::pair<const int, double> V;
	rbmap <int, double>m;
	m.insert(V(1, 1.5));
	assert(m.is_balanced(false)); /* insertion to empty - ok? */
	m.insert(V(2, 2.5));
	assert(m.is_balanced(false)); /* promotion - ok? */
	m.insert(V(3, 3.5));
	assert(m.is_balanced(false)); /* rotation - ok? */

	rbmap <int, double>m1;
	m1.insert(V(1, 1.5));
	m1.insert(V(3, 3.5));
	m1.insert(V(2, 2.5));
	assert(m1.is_balanced(false)); /* double rotation - ok? */


	/* just staff */
	V ar[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(7, 7.5),
            V(8, 8.5),
            V(8, 8.5),
            V(9, 9.5),
            V(10, 10.5),
        };
     rbmap<int, double> m2(ar, ar+sizeof(ar)/sizeof(ar[0]));
	 assert(m2.is_balanced(false));

	 V ar2[] =
        {
            V(10, 10.5),
            V(9, 9.5),
            V(8, 8.5),
            V(7, 7.5),
            V(6, 6.5),
            V(5, 5.5),
            V(4, 4.5),
            V(3, 3.5),
            V(2, 2.5),
            V(1, 1.5),
        };
     rbmap<int, double> m3(ar2, ar2+sizeof(ar2)/sizeof(ar2[0]));
	 assert(m3.is_balanced(false));

	 V ar3[] =
        {
            V(2, 2.5),
            V(4, 4.5),
            V(6, 6.5),
            V(8, 8.5),
            V(10, 10.5),
            V(9, 9.5),
            V(7, 7.5),
            V(5, 5.5),
            V(3, 3.5),
            V(1, 1.5),
        };
     rbmap<int, double> m4(ar3, ar3+sizeof(ar3)/sizeof(ar3[0]));
	 assert(m4.is_balanced(false));

	 V ar4[] =
        {
            V(10, 10.5),
            V(8, 8.5),
            V(6, 6.5),
            V(4, 4.5),
            V(2, 2.5),
            V(1, 1.5),
            V(3, 3.5),
            V(5, 5.5),
            V(7, 7.5),
            V(9, 9.5),
        };
     rbmap<int, double> m5(ar4, ar4+sizeof(ar4)/sizeof(ar4[0]));
	 assert(m5.is_balanced(false));

	 V ar5[] =
        {
            V(7, 7.5),
            V(2, 2.5),
            V(3, 3.5),
            V(9, 9.5),
            V(6, 6.5),
            V(1, 1.5),
            V(4, 4.5),
            V(8, 8.5),
            V(10, 10.5),
            V(5, 5.5),
        };
     rbmap<int, double> m6(ar5, ar5+sizeof(ar5)/sizeof(ar5[0]));
	 assert(m6.is_balanced(false));
        
}