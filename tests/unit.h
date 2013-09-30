/* Unit tests for map */

#include "./tests_llvm/map/types.pass.h"

#include "./tests_llvm/map/map.access/at.pass.h"
#include "./tests_llvm/map/map.access/empty.pass.h"
#include "./tests_llvm/map/map.access/index_key.pass.h"
#include "./tests_llvm/map/map.access/index_rv_key.pass.h"
#include "./tests_llvm/map/map.access/iterator.pass.h"
#include "./tests_llvm/map/map.access/max_size.pass.h"
#include "./tests_llvm/map/map.access/size.pass.h"

#include "./tests_llvm/map/map.cons/alloc.pass.h"
#include "./tests_llvm/map/map.cons/compare.pass.h"
#include "./tests_llvm/map/map.cons/compare_alloc.pass.h"
#include "./tests_llvm/map/map.cons/copy.pass.h"
#include "./tests_llvm/map/map.cons/copy_assign.pass.h"
#include "./tests_llvm/map/map.cons/default.pass.h"
#include "./tests_llvm/map/map.cons/default_recursive.pass.h"
#include "./tests_llvm/map/map.cons/iter_iter.pass.h"
#include "./tests_llvm/map/map.cons/iter_iter_comp.pass.h"
#include "./tests_llvm/map/map.cons/iter_iter_comp_alloc.pass.h"
#include "./tests_llvm/map/map.cons/move.pass.h"

#include "./tests_llvm/map/map.modifiers/clear.pass.h"
#include "./tests_llvm/map/map.modifiers/erase_iter.pass.h"
#include "./tests_llvm/map/map.modifiers/erase_iter_iter.pass.h"
#include "./tests_llvm/map/map.modifiers/erase_key.pass.h"
#include "./tests_llvm/map/map.modifiers/insert_cv.pass.h"
#include "./tests_llvm/map/map.modifiers/insert_iter_cv.pass.h"
#include "./tests_llvm/map/map.modifiers/insert_iter_iter.pass.h"
#include "./tests_llvm/map/map.modifiers/insert_iter_rv.pass.h"
#include "./tests_llvm/map/map.modifiers/insert_rv.pass.h"

#include "./tests_llvm/map/map.ops/count.pass.h"
#include "./tests_llvm/map/map.ops/equal_range.pass.h"
#include "./tests_llvm/map/map.ops/find.pass.h"
#include "./tests_llvm/map/map.ops/lower_bound.pass.h"
#include "./tests_llvm/map/map.ops/upper_bound.pass.h"

#include "./tests_llvm/map/map.special/member_swap.pass.h"
#include "./tests_llvm/map/map.special/non_member_swap.pass.h"


/* Unit tests for multimap */

#include "./tests_llvm/multimap/empty.pass.h"
#include "./tests_llvm/multimap/iterator.pass.h"
#include "./tests_llvm/multimap/max_size.pass.h"
#include "./tests_llvm/multimap/size.pass.h"
#include "./tests_llvm/multimap/types.pass.h"

#include "./tests_llvm/multimap/multimap.cons/alloc.pass.h"
#include "./tests_llvm/multimap/multimap.cons/compare.pass.h"
#include "./tests_llvm/multimap/multimap.cons/compare_alloc.pass.h"
#include "./tests_llvm/multimap/multimap.cons/copy.pass.h"
#include "./tests_llvm/multimap/multimap.cons/default.pass.h"
#include "./tests_llvm/multimap/multimap.cons/iter_iter.pass.h"
#include "./tests_llvm/multimap/multimap.cons/iter_iter_comp.pass.h"
#include "./tests_llvm/multimap/multimap.cons/iter_iter_comp_alloc.pass.h"
#include "./tests_llvm/multimap/multimap.cons/move.pass.h"

#include "./tests_llvm/multimap/multimap.modifiers/clear.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/erase_iter.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/erase_iter_iter.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/erase_key.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/insert_cv.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/insert_iter_cv.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/insert_iter_iter.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/insert_iter_rv.pass.h"
#include "./tests_llvm/multimap/multimap.modifiers/insert_rv.pass.h"

#include "./tests_llvm/multimap/multimap.ops/count.pass.h"
#include "./tests_llvm/multimap/multimap.ops/equal_range.pass.h"
#include "./tests_llvm/multimap/multimap.ops/find.pass.h"
#include "./tests_llvm/multimap/multimap.ops/lower_bound.pass.h"
#include "./tests_llvm/multimap/multimap.ops/upper_bound.pass.h"

#include "./tests_llvm/multimap/multimap.special/member_swap.pass.h"
#include "./tests_llvm/multimap/multimap.special/non_member_swap.pass.h"

/* Unit tests for rebalancing */
#include "./tests_balanced/balanced_after_insertion.h"
#include "./tests_balanced/balanced_after_erasing.h"

void unit_map_access() {
	std::cout << "   Testing map access" << std::endl;

	atpass();
	empty();
	index_key();
	index_rv_key();
	iter();
	max_size();
	size();
}

void unit_map_cons() {
	std::cout << "   Testing map cons" << std::endl;

	alloc();
	compare();
	compare_alloc();
	copy();
	copy_assign();
	_default();
	default_recursive();
	iter_iter();
	iter_iter_comp();
	iter_iter_comp_alloc();
	move();
}

void unit_map_modifiers() {
	std::cout << "   Testing map modifiers" << std::endl;

	clear();
	erase_iter();
	erase_iter_iter();
	erase_key();
	insert_cv();
	insert_iter_cv();
	insert_iter_iter();
	insert_iter_rv();
	insert_rv();
}

void unit_map_ops() {	
	std::cout << "   Testing map ops" << std::endl;

	count();
	equal_range();
	find();
	lower_bound();
	upper_bound();
}

void unit_map_special() {
	std::cout << "   Testing map special" << std::endl;

	member_swap();
	non_member_swap();
}

void unit_map() {
	std::cout << "  Testing map" << std::endl;

	types();

	unit_map_access();
	unit_map_cons();
	unit_map_modifiers();
	unit_map_ops();
	unit_map_special();
}

void unit_multi_map_cons() {
	std::cout << "   Testing multimap cons" << std::endl;

	multi_alloc();
	multi_compare();
	multi_compare_alloc();
	multi_copy();
	multi_default();
	multi_iter_iter();
	multi_iter_iter_comp();
	multi_iter_iter_comp_alloc();
	multi_move();
}

void unit_multi_map_modifiers() {
	std::cout << "   Testing multimap modifiers" << std::endl;

	multi_clear();
	multi_erase_iter();
	multi_erase_iter_iter();
	multi_erase_key();
	multi_insert_cv();
	multi_insert_iter_cv();
	multi_insert_iter_iter();
	multi_insert_iter_rv();
	multi_insert_rv();
}

void unit_multi_map_ops() {
	std::cout << "   Testing multimap ops" << std::endl;

	multi_count();
	multi_equal_range();
	multi_find();
	multi_lower_bound();
	multi_upper_bound();

}

void unit_multi_map_special() {
	std::cout << "   Testing multimap special" << std::endl;
	multi_member_swap();
	multi_non_member_swap();
}

void unit_multi_map() {
	std::cout << std::endl << "  Testing multimap" << std::endl;

	multi_empty();
	multi_iterator();
	multi_max_size();
	multi_size();
	multi_types();

	unit_multi_map_cons();
	unit_multi_map_modifiers();
	unit_multi_map_ops();
	unit_multi_map_special();
}

void unit() {
	std::cout << " Unit tests are launched" << std::endl;

	unit_map();
	unit_multi_map();
	balanced_after_insertion();
	balanced_after_erasing();
}
