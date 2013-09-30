#pragma once
#ifndef _RBMAP_
#define _RBMAP_
#include "./rbtree.h"

namespace rbmap_project {

	/* Template types for tree */
template <
	class key_type,
	class mapped_type,
	class comparator,
	class allocator,
	bool multi>
	class rbTraits
		: public std::_Container_base0
	{
	public:	
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef comparator key_compare;
		typedef typename allocator::template rebind<value_type>::other allocator_type;
		typedef key_type key_type;
		
		/* Map or multimap */
		enum {multimap = multi};

		/* Empty constructor */
		rbTraits()
			: comp()
		{
		}

		/* Construct with comparator */
		rbTraits(comparator compare)
			: comp(compare)
		{
		}

		/* Compare 2 values */
		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
			friend class rbTraits<key_type, mapped_type, comparator, allocator, multi>;

		public:
			bool operator()(const value_type& left, const value_type& right) const
			{
				return (comp(left.first, right.first));
			}

			value_compare(key_compare compare)
				: comp(compare)
			{
			}

		protected:
			/* Comparison functor */
			key_compare comp;	
		};

		/* Get key of value */
	template<class type1, class type2>
		static const key_type& Key(const std::pair<type1, type2>& value)
		{
			return (value.first);
		}

		/* TODO Why not key_compare */
		comparator comp;

	};

	/* Map */
template<
	class key_type,
	class mapped_type,
	class comparator = std::less<key_type>,
	class allocator = std::allocator<std::pair<const key_type, mapped_type>>>
	class rbmap
		: public Tree<rbTraits<key_type, mapped_type, comparator, allocator, false>>
	{	
	public:
		typedef rbmap<key_type, mapped_type, comparator, allocator> this_map;
		typedef Tree<rbTraits<key_type, mapped_type, comparator, allocator, false>> base_tree;
		typedef comparator key_compare;
		typedef typename base_tree::value_compare value_compare;
		typedef typename base_tree::allocator_type allocator_type;
		typedef typename base_tree::size_type size_type;
		typedef typename base_tree::difference_type difference_type;
		typedef typename base_tree::pointer pointer;
		typedef typename base_tree::const_pointer const_pointer;
		typedef typename base_tree::reference reference;
		typedef typename base_tree::const_reference const_reference;
		typedef typename base_tree::iterator iterator;
		typedef typename base_tree::const_iterator const_iterator;
		typedef typename base_tree::reverse_iterator reverse_iterator;
		typedef typename base_tree::const_reverse_iterator const_reverse_iterator;
		typedef typename base_tree::value_type value_type;
		typedef mapped_type mapped_type;

		/* Empty constructor */
		rbmap()
			: base_tree(key_compare(), allocator_type())
		{
		}

		/* Copying constructor */
		rbmap(const this_map& right)
			: base_tree(right)
		{
		}

		/* Construct with comparator */
		rbmap(const key_compare& compare)
			: base_tree(compare, allocator_type())
		{
		}

		/* Construct with comparator and allocator */
		rbmap(const key_compare& compare, const allocator_type& allocator)
			: base_tree(compare, allocator)
		{
		}

		/* Construct with a set of iterators */
	template<class iterator_class>
		rbmap(iterator_class first, iterator_class last)
				: base_tree(key_compare(), allocator_type())
		{
			this->insert(first, last);
		}

		template<class iterator_class>
			rbmap(iterator_class first, iterator_class last, const key_compare& compare)
				: base_tree(compare, allocator_type())
		{
			this->insert(first, last);
		}

		template<class iterator_class>
			rbmap(iterator_class first, iterator_class last, const key_compare& compare, const allocator_type& allocator)
				: base_tree(compare, allocator)
		{
			this->insert(first, last);
		}

		this_map& operator=(const this_map& right)
		{
			base_tree::operator=(right);
			return (*this);
		}

		rbmap(this_map&& right)
			: base_tree(move(right))
		{
		}

		this_map& operator=(this_map&& right)
		{
			base_tree::operator=(move(right));
			return (*this);
		}

		mapped_type& operator[](key_type&& key)
		{
			iterator place = this->lower_bound(key);
			if (place == this->end() || comp(key, this->key(place.node())))
				place = this->insert(place, std::pair<key_type, mapped_type>(key, mapped_type()));
			return ((*place).second);
		}

		mapped_type& operator[](const key_type& key)
		{
			iterator place = this->lower_bound(key);
			if (place == this->end() || comp(key, this->key(place.node())))
				place = this->insert(place, value_type(key, mapped_type()));
			return ((*place).second);
		}

		/*void erase(const_iterator place)
		{
			base_tree::erase(place);
		}*/

		
		iterator erase(const_iterator place)
		{
			return base_tree::erase(place);
		}

		size_type erase(const key_type& key)
		{
			return (base_tree::erase(key));
		}

		iterator erase(const_iterator first, const_iterator second)
		{
			return base_tree::erase(first, second);
		}

		mapped_type& at(const key_type& key)
		{
			iterator place = this->lower_bound(key);
			if (place == this->end() || this->comp(key, this->key(place.node()))) {
				std::_Xout_of_range("No such key");
				//throw;
			}
			return ((*place).second);
		}

		const mapped_type& at(const key_type& key) const
		{
			const_iterator place = this->lower_bound(key);
			if (place == this->end() || this->comp(key, this->key(place.node()))) {
				std::_Xout_of_range("No such key");
			}
			return ((*place).second);
		}

		void swap(this_map& right)
		{
			base_tree::swap(right);
		}

		void swap(this_map&& right)
		{
			base_tree::swap(move(right));
		}
	};

	
template<
	class key_type,
	class mapped_type,
	class comparator,
	class allocator>
		inline void swap(rbmap<key_type, mapped_type, comparator, allocator>& left, rbmap<key_type, mapped_type, comparator, allocator>& right)
	{
		left.swap(right);
	}

template<
	class key_type,
	class mapped_type,
	class comparator,
	class allocator>
		inline void swap(rbmap<key_type, mapped_type, comparator, allocator>& left, rbmap<key_type, mapped_type, comparator, allocator>&& right)
	{
		left.swap(forward<rbmap<key_type, mapped_type, comparator, allocator>>(right));
	}

template<
	class key_type,
	class mapped_type,
	class comparator,
	class allocator> 
		inline void swap(rbmap<key_type, mapped_type, comparator, allocator>&& left, rbmap<key_type, mapped_type, comparator, allocator>& right)
	{
		right.swap(forward<rbmap<key_type, mapped_type, comparator, allocator>>(left));
	}




template<class key_type,
	class mapped_type,
	class comparator = std::less<key_type>,
	class allocator = std::allocator<std::pair<const key_type, mapped_type>>>
	class rbmultimap
		: public Tree<rbTraits<key_type, mapped_type, comparator, allocator, true>>
	{
	public:
		typedef rbmultimap<key_type, mapped_type, comparator, allocator> this_map;
		typedef Tree<rbTraits<key_type, mapped_type, comparator, allocator, true>> base_tree;
		typedef comparator key_compare;
		typedef typename base_tree::value_compare value_compare;
		typedef typename base_tree::allocator_type allocator_type;
		typedef typename base_tree::size_type size_type;
		typedef typename base_tree::difference_type difference_type;
		typedef typename base_tree::pointer pointer;
		typedef typename base_tree::const_pointer const_pointer;
		typedef typename base_tree::reference reference;
		typedef typename base_tree::const_reference const_reference;
		typedef typename base_tree::iterator iterator;
		typedef typename base_tree::const_iterator const_iterator;
		typedef typename base_tree::reverse_iterator reverse_iterator;
		typedef typename base_tree::const_reverse_iterator const_reverse_iterator;
		typedef typename base_tree::value_type value_type;
		typedef mapped_type mapped_type;

		rbmultimap()
			: base_tree(key_compare(), allocator_type())
		{
		}

		rbmultimap(const this_map& right)
			: base_tree(right)
		{
		}

		rbmultimap(const key_compare& compare)
			: base_tree(compare, allocator_type())
		{
		}

		rbmultimap(const key_compare& compare, const allocator_type& allocator)
			: base_tree(compare, allocator)
		{
		}

		template<class iterator_class>
			rbmultimap(iterator_class first, iterator_class last)
				: base_tree(key_compare(), allocator_type())
		{
			this->insert(first, last);
		}

		template<class iterator_class>
			rbmultimap(iterator_class first, iterator_class last, const key_compare& compare)
				: base_tree(compare, allocator_type())
		{
			this->insert(first, last);
		}

		template<class iterator_class>
			rbmultimap(iterator_class first, iterator_class last, const key_compare& compare, const allocator_type& allocator)
				: base_tree(compare, allocator)
		{
			this->insert(first, last);
		}

		this_map& operator=(const this_map& right)
		{
			base_tree::operator=(right);
			return (*this);
		}

		rbmultimap(this_map&& right)
			: base_tree(move(right))
		{
		}

		this_map& operator=(this_map&& right)
		{
			base_tree::operator=(move(right));
			return (*this);
		}

		template<class val_type> iterator insert(val_type&& value)
		{
			return (base_tree::insert(std::forward<val_type>(value)).first);
		}

		template<class val_type> iterator insert(const_iterator place, val_type&& value)
		{
			return (base_tree::insert(place, std::forward<val_type>(value)));
		}

		iterator insert(const value_type& value)
		{
			return (base_tree::insert(value).first);
		}

		iterator insert(const_iterator place, const value_type& value)
		{
			return (base_tree::insert(place, value));
		}

		template<class iterator_class> void insert(iterator_class first, iterator_class second)
		{
			for (iterator_class it = first; it != second; it++)
				insert(*it);
		}

		/*void erase(const_iterator place)
		{
			base_tree::erase(place);
		}*/

		iterator erase(const_iterator place)
		{
			return base_tree::erase(place);
		}

		size_type erase(const key_type& key)
		{
			return (base_tree::erase(key));
		}

		iterator erase(const_iterator first, const_iterator second)
		{
			return base_tree::erase(first, second);
		}

		void swap(this_map& right)
		{
			base_tree::swap(right);
		}

		void swap(this_map&& right)
		{
			base_tree::swap(move(right));
		}
	};

template<
	class key_type,
	class mapped_type,
	class comparator,
	class allocator>
		inline void swap(rbmultimap<key_type, mapped_type, comparator, allocator>& left, rbmultimap<key_type, mapped_type, comparator, allocator>& right)
	{
		left.swap(right);
	}

template<
	class key_type,
	class mapped_type,
	class comparator,
	class allocator>
		inline void swap(rbmultimap<key_type, mapped_type, comparator, allocator>& left, rbmultimap<key_type, mapped_type, comparator, allocator>&& right)
	{
		left.swap(forward<rbmultimap<key_type, mapped_type, comparator, allocator>>(right));
	}

template<
	class key_type,
	class mapped_type,
	class comparator,
	class allocator> 
		inline void swap(rbmultimap<key_type, mapped_type, comparator, allocator>&& left, rbmultimap<key_type, mapped_type, comparator, allocator>& right)
	{
		right.swap(forward<rbmultimap<key_type, mapped_type, comparator, allocator>>(left));
	}

}


#endif