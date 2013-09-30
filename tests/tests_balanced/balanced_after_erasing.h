#include "../../rbmap.h"
#include <iostream>
#include <cassert>

void balanced_after_erasing() {
	std::cout << "  balanced after erasing" << std::endl;
    typedef std::pair<const int, double> V;	

	V ar[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(7, 7.5),
        };
     rbmap<int, double> m(ar, ar+sizeof(ar)/sizeof(ar[0]));
	 m.erase(1);
	 assert(m.is_balanced(true)); // stop
	 m.erase(2);
	 assert(m.is_balanced(true)); // stop

	 V ar2[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(7, 7.5),
        };
     rbmap<int, double> m2(ar2, ar2+sizeof(ar2)/sizeof(ar2[0]));
	 m2.erase(1);
	 m2.erase(3);
	 assert(m2.is_balanced(true)); // stop, demotion


	 V ar3[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(7, 7.5),
        };
	 rbmap<int, double> m3(ar3, ar3+sizeof(ar3)/sizeof(ar3[0]));
	 m3.erase(4);
	 assert(m3.is_balanced(true)); // stop
	 m3.erase(2);
	 assert(m3.is_balanced(true)); // stop
	 m3.erase(3);
	 assert(m3.is_balanced(true)); // stop

	 V ar4[] =
        {
            V(1, 1.5),
            V(2, 2.5),
        };
	rbmap<int, double> m4(ar4, ar4+sizeof(ar4)/sizeof(ar4[0]));
	m4.erase(2);
	assert(m4.is_balanced(true)); // stop, demotion

	V ar5[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(7, 7.5),
            V(8, 8.5),
        };
	rbmap<int, double> m5(ar5, ar5+sizeof(ar5)/sizeof(ar5[0]));
	m5.erase(5);
	assert(m5.is_balanced(true)); // rotation
	m5.erase(3);
	rbmap<int, double> m8 = m5;
	m8.erase(1);
	assert(m8.is_balanced(true)); // demotion, double demotion, stop
	m5.erase(2);
	assert(m8.is_balanced(true)); // double demotion, stop


	V ar6[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(7, 7.5),
            V(8, 8.5),
        };
	rbmap<int, double> m6(ar6, ar6+sizeof(ar6)/sizeof(ar6[0]));
	m6.erase(4);
	assert(m6.is_balanced(true)); // rotation

	V ar7[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
            V(4, 4.5),
            V(5, 5.5),
            V(6, 6.5),
            V(8, 8.5),
            V(7, 7.5),
        };
	rbmap<int, double> m7(ar7, ar7+sizeof(ar7)/sizeof(ar7[0]));
	rbmap<int, double> m9(ar7, ar7+sizeof(ar7)/sizeof(ar7[0]));
	m7.erase(5);
	assert(m7.is_balanced(true)); // double rotation
	m9.erase(4);
	assert(m9.is_balanced(true)); // double rotation

	/*Staff*/

	V ar8[] =
        {
            V(1, 1.5),
            V(2, 2.5),
            V(3, 3.5),
        };
	rbmap<int, double> m14(ar8, ar8+sizeof(ar8)/sizeof(ar8[0]));
	m14.erase(2);
	assert(m14.is_balanced(true));
	

	rbmap<int, double> m10;
	for (int i = 0; i < 100; i++) {
		m10.insert(V(i, 0.0));
	}
	for (int i = 0; i < 50; i++) {
		m10.erase(i);
		assert(m10.is_balanced(true));
	}
	for (int i = 0; i < 50; i++) {
		m10.insert(V(i, 0.0));
		assert(m10.is_balanced(true));
	}

	rbmap<int, double> m11;
	for (int i = 0; i < 100; i++) {
		m11.insert(V(i, 0.0));
	}
	for (int i = 99; i >= 50; i--) {
		m11.erase(i);
		assert(m11.is_balanced(true));
	}
	for (int i = 99; i >= 50; i--) {
		m11.insert(V(i, 0.0));
		assert(m11.is_balanced(true));
	}

	
	rbmap<int, double> m12;
	for (int i = 0; i < 50; i++) {
		m12.insert(V(i, 0.0));
		m12.insert(V(99-i, 0.0));
	}
	for (int i = 0; i < 50; i++) {
		m12.erase(99-i);
		assert(m12.is_balanced(true));
		m12.erase(i);
		assert(m12.is_balanced(true));
	}

	rbmap<int, double> m13;
	for (int i = 0; i < 50; i++) {
		m13.insert(V(i, 0.0));
		m13.insert(V(99-i, 0.0));
	}
	for (int i = 0; i < 50; i++) {
		m13.erase(i);
		assert(m13.is_balanced(true));
		m13.erase(i+50);
		assert(m13.is_balanced(true));
	}

}