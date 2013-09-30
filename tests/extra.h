#include <iostream>

#include "../rbmap.h"
#include <map>

#include <vector>
#include <algorithm>
#include <cassert>


void test_balanced_undeterministic(int times) {
	typedef std::pair<const int, double> V;	


	while (times > 0) {
		times--;
		std::vector< int > v(100);
		rbmap<int, double> m15;
		for (int i = 0; i < 100; i++) {
			v[i] = i;
		}
		std::random_shuffle( v.begin(), v.end() );
		for (int i = 0; i < 100; i++) {
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;

		for (int i = 0; i < 100; i++) {
			m15.insert(V(v[i], 0.0));
			assert(m15.is_balanced(false));
		}
		std::random_shuffle( v.begin(), v.end() );
		for (int i = 0; i < 50; i++) {
			m15.erase(v[i]);
			assert(m15.is_balanced(true));
		}
		for (int i = 50; i < 100; i++) {
			v.erase(v.begin() + 50);
		}
		std::random_shuffle( v.begin(), v.end() );
		for (int i = 0; i < 50; i++) {
			m15.insert(V(v[i], 0.0));
			assert(m15.is_balanced(true));
		}
	}
}

void extra() {
	test_balanced_undeterministic(1E6);
}