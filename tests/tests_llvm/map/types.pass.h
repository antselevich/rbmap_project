//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// template <class Key, class T, class Compare = less<Key>,
//           class Allocator = allocator<pair<const Key, T>>>
// class map
// {
// public:
//     // types:
//     typedef Key                                      key_type;
//     typedef T                                        mapped_type;
//     typedef pair<const key_type, mapped_type>        value_type;
//     typedef Compare                                  key_compare;
//     typedef Allocator                                allocator_type;
//     typedef typename allocator_type::reference       reference;
//     typedef typename allocator_type::const_reference const_reference;
//     typedef typename allocator_type::pointer         pointer;
//     typedef typename allocator_type::const_pointer   const_pointer;
//     typedef typename allocator_type::size_type       size_type;
//     typedef typename allocator_type::difference_type difference_type;
//     ...
// };

#include "../../../rbmap.h"
#include <type_traits>

using namespace rbmap_project;

void types()
{
	std::cout << "    types" << std::endl;
    static_assert((std::is_same<rbmap<int, double>::key_type, int>::value), "");
    static_assert((std::is_same<rbmap<int, double>::mapped_type, double>::value), "");
    static_assert((std::is_same<rbmap<int, double>::value_type, std::pair<const int, double> >::value), "");
    static_assert((std::is_same<rbmap<int, double>::key_compare, std::less<int> >::value), "");
    static_assert((std::is_same<rbmap<int, double>::allocator_type, std::allocator<std::pair<const int, double> > >::value), "");
    static_assert((std::is_same<rbmap<int, double>::reference, std::pair<const int, double>&>::value), "");
    static_assert((std::is_same<rbmap<int, double>::const_reference, const std::pair<const int, double>&>::value), "");
    static_assert((std::is_same<rbmap<int, double>::pointer, std::pair<const int, double>*>::value), "");
    static_assert((std::is_same<rbmap<int, double>::const_pointer, const std::pair<const int, double>*>::value), "");
    static_assert((std::is_same<rbmap<int, double>::size_type, std::size_t>::value), "");
    static_assert((std::is_same<rbmap<int, double>::difference_type, std::ptrdiff_t>::value), "");
}
