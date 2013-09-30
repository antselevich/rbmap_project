#ifndef __RBTREE__
#define __RBTREE__

#include <memory>
#include <xfunctional>
#include <stdexcept>
#include <iostream>
#include <string>
#include <utility>

namespace rbmap_project {

/* ITERATORS */

// Const iterator
template<class tree, class base_iterator_class = std::_Iterator_base0>
	class tree_const_iterator
		: public base_iterator_class
	{
	public:
		typedef tree_const_iterator<tree, base_iterator_class> this_iterator;
		typedef std::bidirectional_iterator_tag iterator_category;

		typedef typename tree::node_ptr node_ptr;
		typedef typename tree::value_type value_type;
		typedef typename tree::difference_type difference_type;
		typedef typename tree::const_pointer const_pointer;
		typedef typename tree::const_reference const_reference;
		typedef typename tree::pointer pointer;
		typedef typename tree::reference reference;

		node_ptr my_pointer;

		tree_const_iterator()
			: my_pointer(0)
		{
		}

		tree_const_iterator(node_ptr a_pointer, const tree *list)
			: my_pointer(a_pointer)
		{
			this->_Adopt(list);
		}

		const_reference operator*() const
		{
			return (tree::value(my_pointer));
		}

		const_pointer operator->() const
		{
			return (&**this);
		}

		this_iterator& operator++()
		{ // preincrement
			if (tree::isnil(my_pointer)) { // don't increment and don't check
			}
			else if (!tree::isnil(tree::right(my_pointer))) { // go to minimum in the not nill right subtree
				my_pointer = tree::min(tree::right(my_pointer));
			}
			else { // climb up the tree
				node_ptr node = tree::parent(my_pointer);
				while (!tree::isnil(node) && my_pointer == tree::right(node)) { // climb up while this is right
					my_pointer = node;
					node = tree::parent(my_pointer);
				}
				// now left child, so go up
				my_pointer = node;
			}
			return (*this);
		}

		this_iterator operator++(int)
		{ // postincrement
			this_iterator it = *this;
			++*this;
			return (it); // iterator changes, but operator returns it unchanged
		}

		this_iterator& operator--()
		{ // predecrement
			if (tree::isnil(my_pointer)) {
				my_pointer = tree::right(my_pointer); // head
			}
			else if (!tree::isnil(tree::left(my_pointer))) { // go to maximum in the not nill left subtree
				my_pointer = tree::max(tree::left(my_pointer));
			}
			else { // climb up the tree
				node_ptr node = tree::parent(my_pointer);
				while (!tree::isnil(node) && my_pointer == tree::left(node)) { // climb up while this is left
					my_pointer = node;
					node = tree::parent(my_pointer);
				}
				if (!tree::isnil(my_pointer)) { // if not begin
					my_pointer = node; // decrement
				}
			}
			return (*this);
		}

		this_iterator operator--(int)
		{ // postdecrement
			this_iterator it = *this;
			--*this;
			return (it); // iterator changes, but operator returns it unchanged
		}

		bool operator==(const this_iterator& right) const
		{
			return (my_pointer == right.my_pointer);
		}

		bool operator!=(const this_iterator& right) const
		{
			return (my_pointer != right.my_pointer);
		}

		node_ptr node() const
		{
			return (my_pointer);
		}

	};


// Mutable iterator
template<class tree>
	class tree_iterator
		: public tree_const_iterator<tree>
	{
	public:
		typedef tree_iterator<tree> this_iterator;
		typedef tree_const_iterator<tree> base_iterator;
		typedef std::bidirectional_iterator_tag iterator_category;

		typedef typename tree::node_ptr node_ptr;
		typedef typename tree::value_type value_type;
		typedef typename tree::difference_type difference_type;
		typedef typename tree::pointer pointer;
		typedef typename tree::reference reference;

		tree_iterator()
		{
		}

		tree_iterator(node_ptr a_pointer, const tree *list)
			: base_iterator(a_pointer, list)
		{
		}

		reference operator*() const
		{
			return ((reference)**(base_iterator *)this);
		}

		pointer operator->() const
		{
			return (&**this);
		}

		this_iterator& operator++()
		{	// preincrement
			++(*(base_iterator *)this);
			return (*this);
		}

		this_iterator operator++(int)
		{	// postincrement
			this_iterator it = *this;
			++*this;
			return (it);
		}

		this_iterator& operator--()
		{	// predecrement
			--(*(base_iterator *)this);
			return (*this);
		}

		this_iterator operator--(int)
		{	// postdecrement
			this_iterator it = *this;
			--*this;
			return (it);
		}
	};


/* ---------- */


template<class rbTraits>
	class Node
		: public rbTraits
	{
	public:
		typedef typename rbTraits::allocator_type allocator_type;
		typedef typename rbTraits::key_compare key_compare;
		typedef typename rbTraits::value_type value_type;
		
		typedef typename allocator_type::template rebind<value_type>::other
			allocate_obj_of_oth_ty;
		
		typedef typename allocate_obj_of_oth_ty::size_type size_type;

		struct a_node;
		typedef a_node *node_ptr;
		typedef node_ptr& node_ptr_ref;

		struct a_node
		{	// tree node
			node_ptr left;
			node_ptr parent;
			node_ptr right;
			value_type value;
			char rank;
			bool isnil;

	private:
		a_node& operator=(const a_node&);
		};

		Node(const key_compare& key_comp,
			allocator_type alloc)
			: rbTraits(key_comp), allocate_nodes(alloc), al_elems(alloc)
		{
		}
		node_ptr head;
		size_type my_size;	// number of elements

		typename allocator_type::template rebind<a_node>::other
			allocate_nodes;	// allocator object for nodes
		allocate_obj_of_oth_ty al_elems;	// allocator object for element values
	};

template <class rbTraits>
	class alNode
		: public Node<rbTraits>
	{
	public:
		typedef typename rbTraits::allocator_type allocator_type;
		typedef typename rbTraits::key_compare key_compare;
		typedef typename rbTraits::key_type key_type;

		typedef typename Node<rbTraits>::node_ptr node_ptr;
		typedef typename Node<rbTraits>::node_ptr_ref node_ptr_ref;
		typedef typename Node<rbTraits>::allocate_obj_of_oth_ty allocate_obj_of_oth_ty;

		typedef typename allocate_obj_of_oth_ty::size_type size_type;
		typedef typename allocate_obj_of_oth_ty::difference_type difference_type;
		typedef typename allocate_obj_of_oth_ty::pointer pointer;
		typedef typename allocate_obj_of_oth_ty::const_pointer const_pointer;
		typedef typename allocate_obj_of_oth_ty::reference reference;
		typedef typename allocate_obj_of_oth_ty::const_reference const_reference;
		typedef typename allocate_obj_of_oth_ty::value_type value_type;


		alNode(const key_compare& comp,
			allocator_type al)
			: Node<rbTraits>(comp, al)
		{
			this->my_size = 0;
			this->head = this->allocate_nodes.allocate(1);

			this->left(this->head) = this->head;
			this->parent(this->head) = this->head;
			this->right(this->head) = this->head;
			this->rank(this->head) = -1;
			this->isnil(this->head) = true;
		}

		~alNode()
		{
			this->allocate_nodes.deallocate(this->head, 1);
		}

		node_ptr allocate_node()
		{
			node_ptr node = this->allocate_nodes.allocate(1);

			this->left(node) = this->head;
			this->parent(node) = this->head;
			this->right(node) = this->head;
			this->rank(node) = 0;
			this->isnil(node) = false;
			return node;
		}

		node_ptr allocate_node(const value_type& value)
		{
				node_ptr node = allocate_node();
				try {
					al_elems.construct(addressof(this->value(node)), value);
				}
				catch (...) {
					this->allocate_nodes.deallocate(node, 1);
					throw;
				}
				return node;
		}

		template<class my_value_type>
			node_ptr allocate_node(my_value_type&& value)
		{
			node_ptr node = allocate_node();

			try {
				al_elems.construct(std::addressof(this->value(node)), std::forward<my_value_type>(value));
			}
			catch (...) {
				this->allocate_nodes.deallocate(node, 1);
				throw;
			}

			return node;
		}

		static char& rank(node_ptr node)
		{
			return ((char&)node->rank);
		}

		static bool& isnil(node_ptr node)
		{
			return ((bool&)node->isnil);
		}

		static key_type& key(node_ptr node)
		{
			return ((key_type&)rbTraits::Key(value(node)));
		}

		static node_ptr_ref left(node_ptr node)
		{
			return ((node_ptr_ref)(*node).left);
		}

		static node_ptr_ref parent(node_ptr node)
		{
			return ((node_ptr_ref)(*node).parent);
		}

		static node_ptr_ref right(node_ptr node)
		{
			return ((node_ptr_ref)(*node).right);
		}

		static reference value(node_ptr node)
		{
			return ((reference)(*node).value);
		}

		static node_ptr max(node_ptr node)
		{	// rightmost 
			while (!isnil(right(node)))
				node = right(node);
			return node;
		}

		static node_ptr min(node_ptr node)
		{	// leftmost
			while (!isnil(left(node)))
				node = left(node);
			return node;
		}
	};

template<class rbTraits>
	class Tree
		: public alNode<rbTraits>
	{
	public:
		typedef Tree<rbTraits> this_tree;
		typedef alNode<rbTraits> base_class;
		typedef typename base_class::a_node a_node;
		typedef typename base_class::node_ptr node_ptr;

		typedef typename rbTraits::key_type key_type;
		typedef typename rbTraits::key_compare key_compare;
		typedef typename rbTraits::value_compare value_compare;
		typedef typename rbTraits::value_type value_type;
		typedef typename rbTraits::allocator_type allocator_type;

		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;

		typedef tree_const_iterator<base_class> const_iterator;
		//typedef tree_iterator<base_class> iterator;

		typedef typename std::tr1::conditional<std::tr1::is_same<key_type, value_type>::value, const_iterator, tree_iterator<base_class> >::type iterator;
		

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef std::pair<iterator, bool> _Pairib;
		typedef std::pair<iterator, iterator> _Pairii;
		typedef std::pair<const_iterator, const_iterator> _Paircc;

		
		Tree(const key_compare& comp, const allocator_type& al)
			: base_class(comp, al)
		{
		}

		Tree(const value_type *first, const value_type *last,
			const key_compare& comp, const allocator_type& al)
			: base_class(comp, al)
		{
			try {
				insert(first, last);
			} 
			catch (...) {
				erase(begin(), end());
				throw;
			}
		}

		Tree(const this_tree& right)
			: base_class(right.key_comp(), right.al_elems)
		{
			try {
				copy(right);
			}
			catch (...) {
				erase(begin(), end());
				throw;
			}
		}

		Tree(this_tree&& right)
			: base_class(right.key_comp(), right.al_elems)
		{
			assign(std::forward<this_tree>(right));
		}

		Tree& operator=(this_tree&& right)
		{
			assign(std::forward<this_tree>(right));
			return (*this);
		}

		this_tree& operator=(const this_tree& right)
		{
			if (this != &right)
			{
				erase(begin(), end());
				this->comp = right.comp;
				copy(right);
			}
			return (*this);
		}

		void assign(this_tree&& right)
		{
			if (this == &right) {}
			else if (get_allocator() != right.get_allocator())
				std::_Xinvalid_argument("invalid map/set<T> move assign");
			else
			{
				clear();
				this->_Swap_all(right);
				std::_Swap_adl(this->comp, right.comp);
				std::swap(this->head, right.head);
				std::swap(this->my_size, right.my_size);
			}
		}

		~Tree()
		{
			erase(begin(), end());
		}

		void swap(this_tree&& right)
		{
			assign(std::forward<this_tree>(right));
		}

		allocator_type get_allocator() const
		{
			return (this->al_elems);
		}

		key_compare key_comp() const
		{
			return (this->comp);
		}

		value_compare value_comp() const
		{
			return (value_compare(key_comp()));
		}

		iterator begin()
		{
			return (iterator(most_left(), this));
		}

		const_iterator begin() const
		{
			return (const_iterator(most_left(), this));
		}

		iterator end()
		{
			return (iterator(this->head, this));
		}

		const_iterator end() const
		{
			return (const_iterator(this->head, this));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		size_type size() const
		{
			return (this->my_size);
		}

		size_type size()
		{
			return (this->my_size);
		}

		size_type max_size() const
		{
			return (this->al_elems.max_size());
		}

		bool empty() const
		{
			return (size() == 0);
		}
		
		node_ptr& root() const
		{
			return (this->parent(this->head));
		}

		node_ptr& most_right() const
		{
			return (this->right(this->head));
		}

		node_ptr& most_left() const
		{
			return (this->left(this->head));
		}

		node_ptr& most_right()
		{
			return (this->right(this->head));
		}

		node_ptr& most_left()
		{
			return (this->left(this->head));
		}

		
		template<class type_to_insert>
			_Pairib insert(type_to_insert&& value)
		{
			return (search_insert_left_if_eq(this->allocate_node(std::forward<type_to_insert>(value)), false));
		}

		template<class type_to_insert>
			iterator insert(const_iterator _where, type_to_insert&& value)
		{
			return (insert_node_with_hint(_where, this->allocate_node(std::forward<type_to_insert>(value))));
		}

		_Pairib insert(const value_type& value)
		{
			return (insert(value, false)); // false means insert right
		}

		_Pairib insert(const value_type& value, bool favor_left)
		{
			node_ptr temp = this->parent(this->head);
			node_ptr place = this->head;

			bool go_left = true;

			while (!this->isnil(temp))
			{
				place = temp;
				go_left = (favor_left && !_DEBUG_LT_PRED(this->comp, this->key(temp), this->Key(value))) ||
							(!favor_left && _DEBUG_LT_PRED(this->comp, this->Key(value), this->key(temp)));
				temp = go_left ? this->left(temp) : this->right(temp);
			}

			if (this->multimap) { // multimap
				return (_Pairib(insert_value_with_hint_and_favor(go_left, place, value), true));
			}
			else { // map
				iterator place_iterator = iterator(place, this);
				if (go_left) {
					if (place_iterator == begin())
						return (_Pairib(insert_value_with_hint_and_favor(true, place, value), true));
					else // if not the very beginning, try to go further
						--place_iterator;
				}

				if (_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value))) { // if the lefter one is less, insert
					return (_Pairib(insert_value_with_hint_and_favor(go_left, place, value), true));
				}
				else  { // if it's not less, the key is already present
					return (_Pairib(place_iterator, false));
				}
			}
		}


		_Pairib search_insert_left_if_eq(node_ptr node, bool favor_left)
		{
			const value_type& value = this->value(node);
			node_ptr temp = root();
			node_ptr place = this->head;
			bool go_left = true;
			while (!this->isnil(temp)) {
				place = temp;
				go_left = (favor_left && !_DEBUG_LT_PRED(this->comp, this->key(temp), this->Key(value))) ||
						(!favor_left && _DEBUG_LT_PRED(this->comp, this->Key(value), this->key(temp)));
				temp = go_left ? this->left(temp) : this->right(temp);
			}

			if (this->multimap) { // multimap
				return (_Pairib(insert_node_with_hint_and_favor(go_left, place, node), true));
			}
			else {	// map
				iterator place_iterator = iterator(place, this);
				if (go_left) {
					if (place_iterator == begin())
						return (_Pairib(insert_node_with_hint_and_favor(true, place, node), true));
					else
						--place_iterator;
				}

				if (_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)))
					return (_Pairib(insert_node_with_hint_and_favor(go_left, place, node), true));
				else
				{ // if it's not less, the key is already present, remove node
					_Dest_val(this->al_elems, addressof(this->value(node)));
					this->allocate_nodes.deallocate(node, 1);
					return (_Pairib(place_iterator, false));
				}
			}
		}

		iterator insert(const_iterator place_iterator, const value_type& value)
		{
			const_iterator temp_iterator;

			const_iterator before_place = place_iterator;
			before_place--;
			const_iterator after_place = place_iterator;
			after_place++;

			bool favor_left = false;

			/* empty tree */
			if (size() == 0)
				return (insert_value_with_hint_and_favor(true, this->head, value));
			/* multimap */
			else if (this->multimap) {
				/* insert at beginning if before first element */
				if (place_iterator == begin()) {
					if (!_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)))
						return (insert_value_with_hint_and_favor(true, place_iterator.node(), value));
					favor_left = true;
				}
				/* insert at end if after last element */
				else if (place_iterator == end()) {
					if (!_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(most_right())))
						return (insert_value_with_hint_and_favor(false, most_right(), value));
				}
				/* value between place_iterator and --place_iterator */
				else if (!_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)) &&
						(!_DEBUG_LT_PRED(this->comp, this->Key(value), this->key((before_place).node())))) {
					/* right is nil => insert at --place_iterator favoring right side */
					if (this->isnil(this->right(before_place.node())))
						return (insert_value_with_hint_and_favor(false, before_place.node(), value));
					/* right is not nil => insert at place_iterator favoring left side */
					else
						return (insert_value_with_hint_and_favor(true, before_place.node(), value));
				}
				/* value between place_iteraror and ++place_iterator */
				else if (!_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(place_iterator.node())) && 
						(after_place == end() || 
						(!_DEBUG_LT_PRED(this->comp, this->key(after_place.node()), this->Key(value))))) {
					/* right is nil => insert at place_iterator favoring right side */
					if (this->isnil(this->right(place_iterator.node())))
						return (insert_value_with_hint_and_favor(false,place_iterator.node(), value));
					/* right is not nil => insert at ++place_iterator favoring left side */
					else
						return (insert_value_with_hint_and_favor(true, after_place.node(), value));
				}
				else
					favor_left = true;
			}
			/* map */
			else 
			{
				/* insert at beginning if before first element */
				if (place_iterator == begin())
				{
					if (_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(place_iterator.node())))
						return (insert_value_with_hint_and_favor(true, place_iterator.node(), value));
				}
				/* insert at end if after last element */
				else if (place_iterator == end())
				{
					if (_DEBUG_LT_PRED(this->comp, this->key(most_right()), this->Key(value)))
						return (insert_value_with_hint_and_favor(false, most_right(), value));
				}
				/* value between place_iterator and --place_iterator */
				else if (_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(place_iterator.node())) && 
						 _DEBUG_LT_PRED(this->comp, this->key(before_place.node()), this->Key(value)))
				{
					/* right is nil => insert at --place_iterator favoring right side */
					if (this->isnil(this->right(before_place.node())))
						return (insert_value_with_hint_and_favor(false, before_place.node(), value));
					/* right is not nil => insert at place_iterator favoring left side */
					else
						return (insert_value_with_hint_and_favor(true, place_iterator.node(), value));
				}
				/* value between place_iteraror and ++place_iterator */
				else if (_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)) && 
						(after_place == end() || 
						_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(after_place.node()))))
				{
					/* right is nil => insert at place_iterator favoring right side */
					if (this->isnil(this->right(place_iterator.node())))
						return (insert_value_with_hint_and_favor(false, place_iterator.node(), value));
					/* right is not nil => insert at ++place_iterator favoring left side */
					else
						return (insert_value_with_hint_and_favor(true, after_place.node(), value));
				}
			}
			return (insert(value, favor_left).first);
		}

		iterator insert_node_with_hint(const_iterator place_iterator, node_ptr node) {

			const value_type& value = this->value(node);

			const_iterator before_place = place_iterator;
			before_place--;
			const_iterator after_place = place_iterator;
			after_place++;

			bool favor_left = false;

			/* empty tree */
			if (size() == 0)
				return (insert_node_with_hint_and_favor(true, this->head, node));
			/* multimap */
			else if (this->multimap) {
				/* insert at beginning if before first element */
				if (place_iterator == begin()) {
					if (!_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)))
						return (insert_node_with_hint_and_favor(true, place_iterator.node(), node));
					favor_left = true;	// nearest point is beginning of sequence
				}
				/* insert at end if after last element */
				else if (place_iterator == end()) {
					if (!_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(most_right())))
						return (insert_node_with_hint_and_favor(false, most_right(), node));
				}
				/* value between place_iterator and --place_iterator */
				else if (!_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)) && 
						 !_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(before_place.node()))) {
					/* right is nil => insert at --place_iterator favoring right side */
					if (this->isnil(this->right(before_place.node())))
						return (insert_node_with_hint_and_favor(false, before_place.node(), node));
					/* right is not nil => insert at place_iterator favoring left side */
					else
						return (insert_node_with_hint_and_favor(true, place_iterator.node(), node));
				}
				/* value between place_iterator and ++place_iterator */
				else if (!_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(place_iterator.node())) && 
						(after_place == end() || 
						 !_DEBUG_LT_PRED(this->comp, this->key(after_place.node()), this->Key(value)))) {
					/* right is nil => insert at place_iterator favoring right side */
					if (this->isnil(this->right(place_iterator.node())))
						return (insert_node_with_hint_and_favor(false, place_iterator.node(), node));
					/* right is not nil => insert at ++place_iterator favoring left side */
					else
						return (insert_node_with_hint_and_favor(true, after_place.node(), node));
				}
				else
					favor_left = true;
			}
			/* map */
			else
			{
				/* insert at beginning if before first element */
				if (place_iterator == begin()) {
					if (_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(place_iterator.node())))
						return (insert_node_with_hint_and_favor(true, place_iterator.node(), node));
				}
				/* insert at end if after last element */
				else if (place_iterator == end()) {
					if (_DEBUG_LT_PRED(this->comp, this->key(most_right()), this->Key(value)))
						return (insert_node_with_hint_and_favor(false, most_right(), node));
				}
				/* value between place_iterator and --place_iterator */
				else if (_DEBUG_LT_PRED(this->comp, this->Key(value), this->key(place_iterator.node())) && 
						 _DEBUG_LT_PRED(this->comp, this->key(before_place.node()), this->Key(value)))
				{
					/* right is nil => insert at --place_iterator favoring right side */
					if (this->isnil(this->right(before_place.node())))
						return (insert_node_with_hint_and_favor(false, before_place.node(), node));
					/* right is not nil => insert at place_iterator favoring left side */
					else
						return (insert_node_with_hint_and_favor(true, place_iterator.node(), node));
				}
				/* value between place_iterator and ++place_iterator */
				else if (_DEBUG_LT_PRED(this->comp, this->key(place_iterator.node()), this->Key(value)) && 
						(after_place == end() || 
						 _DEBUG_LT_PRED(this->comp, this->Key(value), this->key(after_place.node()))))
				{
					/* right is nil => insert at place_iterator favoring right side */
					if (this->isnil(this->right(place_iterator.node())))
						return (insert_node_with_hint_and_favor(false, place_iterator.node(), node));
					/* right is nil => insert at ++place_iterator favoring left side */
					else
						return (insert_node_with_hint_and_favor(true, after_place.node(), node));
				}
			}
			return (search_insert_left_if_eq(node, favor_left).first);
		}

		template<class iterator_class>
			void insert(iterator_class first, iterator_class last) 
		{
			for (iterator_class it = first; it != last; ++it)
			{
				const value_type& value = *it;
				insert(end(), value);
			}
		}

		iterator erase(const_iterator place) {
			if (this->isnil(place.node())) {
				std::_Xout_of_range("invalid map/set<T> iterator");
			}
			node_ptr node_to_erase = place.node();
			node_ptr node_to_rebalance = node_to_erase;
			node_ptr parent_of_node_to_rebalance = this->parent(node_to_rebalance);
			place++;	
			/* left is nil */
			if (this->isnil(this->left(node_to_erase))) {
				node_ptr right = this->right(node_to_erase);
				node_ptr parent_of_erased = this->parent(node_to_erase);
				/* parent of right is parent of erased */
				if (!this->isnil(right)) {
					this->parent(right) = parent_of_erased;
				}
				/* root changes */
				if (root() == node_to_erase) {
					root() = right;
				}
				/* left child changes */
				else if (this->left(parent_of_erased) == node_to_erase) {
					this->left(parent_of_erased) = right;
				}
				/* right child changes */
				else {
					this->right(parent_of_erased) = right;
				}
				/* lmost changes */
				if (most_left() == node_to_erase) {
					if (this->isnil(right)) {
						most_left() = parent_of_erased;
					}
					else {
						most_left() =  this->min(right);
					}
				}
				/* rmost changes */
				if (most_right() == node_to_erase) {
					if (this->isnil(right)) {
						most_right() = parent_of_erased;
					}
					else {
						most_right() =  this->max(right);
					}
				}
				node_to_rebalance = right;
				parent_of_node_to_rebalance = parent_of_erased;
			}
			/* right is nil */
			else if (this->isnil(this->right(node_to_erase))) {
				node_ptr left = this->left(node_to_erase);
				node_ptr parent_of_erased = this->parent(node_to_erase);
				/* parent of left is parent of erased */
				if (!this->isnil(left)) {
					this->parent(left) = parent_of_erased;
				}
				/* root changes */
				if (root() == node_to_erase) {
					root() = left;
				}
				/* left child changes */
				else if (this->left(parent_of_erased) == node_to_erase) {
					this->left(parent_of_erased) = left;
				}
				/* right child changes */
				else {
					this->right(parent_of_erased) = left;
				}
				/* lmost changes */
				if (most_left() == node_to_erase) {
					if (this->isnil(left)) {
						most_left() = parent_of_erased;
					}
					else {
						most_left() =  this->min(left);
					}
				}
				/* rmost changes */
				if (most_right() == node_to_erase) {
					if (this->isnil(left)) {
						most_right() = parent_of_erased;
					}
					else {
						most_right() =  this->max(left);
					}
				}
				node_to_rebalance = left;
				parent_of_node_to_rebalance = parent_of_erased;
			}
			/* both are present */
			else {
				/* successor will be leftmost node of right subtree */
				node_ptr successor = place.node();
				
				parent_of_node_to_rebalance = this->parent(successor);
				bool recheck = false;

				node_ptr right_of_successor = this->right(successor);
				/* relink left subtree to left of successor */
				this->parent(this->left(node_to_erase)) = successor;
				this->left(successor) = this->left(node_to_erase);
				this->rank(successor) = this->rank(node_to_erase);
				
				if (successor == this->right(node_to_erase)) {
					recheck = true;
					/* successor is already the right subtree */
				}
				else {
					/* Relink right son of successor to left son of successor's parent (successor was it's left son) */
					if (!this->isnil(right_of_successor)) {
						this->parent(right_of_successor) = this->parent(successor);
					}
					this->left(this->parent(successor)) = right_of_successor;
					
					/* Relink right son of erased node to right son of successor */
					this->right(successor) = this->right(node_to_erase);
					this->parent(this->right(node_to_erase)) = successor;
				}

				/* Successor now stays at the place of node_to_erase */
				if (root() == node_to_erase) {
					root() = successor;
				}
				else if (this->left(this->parent(node_to_erase)) == node_to_erase) {
					this->left(this->parent(node_to_erase)) = successor;
				}
				else {
					this->right(this->parent(node_to_erase)) = successor;
				}
				this->parent(successor) = this->parent(node_to_erase);

				
				node_to_rebalance = this->left(parent_of_node_to_rebalance);
				if (recheck) {
					parent_of_node_to_rebalance = successor;
					node_to_rebalance = this->right(successor);
				}

			}

			/* Now deallocate erase node and it's internals */
			_Dest_val(this->al_elems, addressof(this->value(node_to_erase)));	// delete erased node
			this->allocate_nodes.deallocate(node_to_erase, 1);

			if (this->size() > 0)
				--this->my_size;

			this->rebalance_after_erase(node_to_rebalance, parent_of_node_to_rebalance);

			return (iterator(place.my_pointer, this));
		}

		iterator erase(const_iterator begin, const_iterator end) {
			if (begin == this->begin() && end == this->end())
			{
				clear();
				return (this->begin());
			}
			else
			{
				const_iterator it = begin;
				const_iterator temp_it;
				while (it != end) {
					temp_it = it;
					it++;
					erase(temp_it);
				}
				return (iterator(end.my_pointer, this));
			}
		}

		size_type erase(const key_type& key) {
			_Pairii place = equal_range(key);
			size_type sz = 0;
			_Distance(place.first, place.second, sz);
			erase(place.first, place.second);
			return (sz);
		}

		void erase(const key_type *begin, const key_type *end) {
			while (begin != end)
				erase(*begin++);
		}

		void clear() {
			erase_node_recursively(root());
			root() = this->head;
			most_left() = this->head;
			most_right() = this->head;
			this->my_size = 0;
		}

		iterator find(const key_type& key) {
			iterator place = lower_bound(key);
			if (place == end() ||  _DEBUG_LT_PRED(this->comp, key, this->key(place.node()))) {
				return end();
			}
			else {
				return place;
			}
		}

		const_iterator find(const key_type& key) const {
			const_iterator place = lower_bound(key);
			if (place == end() ||  _DEBUG_LT_PRED(this->comp, key, this->key(place.node()))) {
				return end();
			}
			else {
				return place;
			}
		}

		size_type count(const key_type& key) const {
			_Paircc range = equal_range(key);
			size_type sz = 0;
			_Distance(range.first, range.second, sz);
			return (sz);
		}

		iterator lower_bound(const key_type& key) {
			return (iterator(lower_bound_node(key), this));
		}

		const_iterator lower_bound(const key_type& key) const {
			return (const_iterator(lower_bound_node(key), this));
		}

		iterator upper_bound(const key_type& key) {
			return (iterator(upper_bound_node(key), this));
		}

		const_iterator upper_bound(const key_type& key) const {
			return (const_iterator(upper_bound_node(key), this));
		}

		_Pairii equal_range(const key_type& key) {
			node_ptr node = root();
			node_ptr lower_node = this->head;
			node_ptr higher_node = this->head;

			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, this->key(node), key)) {
					node = this->right(node);
				}
				else {
					if (this->isnil(higher_node) && _DEBUG_LT_PRED(this->comp, key, this->key(node))) {
						higher_node = node;
					}
					lower_node = node;
					node = this->left(node);
				}
			}

			node = this->isnil(higher_node) ? root() : this->left(higher_node);
			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, key, this->key(node))) {
					higher_node = node;
					node = this->left(node);	// descend left subtree
				}
				else {
					node = this->right(node);
				}
			}

			iterator begin = iterator(lower_node, this);
			iterator end = iterator(higher_node, this);
			return (_Pairii(begin, end));
		}

		_Paircc equal_range(const key_type& key) const {
			node_ptr node = root();
			node_ptr lower_node = this->head;
			node_ptr higher_node = this->head;

			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, this->key(node), key)) {
					node = this->right(node);
				}
				else {
					if (this->isnil(higher_node) && _DEBUG_LT_PRED(this->comp, key, this->key(node))) {
						higher_node = node;
					}
					lower_node = node;
					node = this->left(node);
				}
			}



			node = this->isnil(higher_node) ? root() : this->left(higher_node);
			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, key, this->key(node))) {
					higher_node = node;
					node = this->left(node);	// descend left subtree
				}
				else {
					node = this->right(node);
				}
			}

			const_iterator begin = const_iterator(lower_node, this);
			const_iterator end = const_iterator(higher_node, this);
			return (_Paircc(begin, end));
		}

		void swap(this_tree& right) {
			if (this == &right) {
				return;
			}
			if (get_allocator() == right.get_allocator()) {
				this->_Swap_all(right);
				_Swap_adl(this->comp, right.comp);
				std::swap(this->head, right.head);
				std::swap(this->my_size, right.my_size);
			}
			else {
				this_tree temp = _Move(*this);
				*this = _Move(right);
				right = _Move(temp);
			}
		}

		bool is_balanced(bool has_been_deleted_from) {
			if (empty()) {
				return true;
			}
			for (iterator it = begin(); it != end(); it++) {
				node_ptr node = it.node();
				if (this->rank(node) - this->rank(this->right(node)) <= 0) {
					std::cout << "right <= 0" << std::endl;
					return false;
				}
				if (this->rank(node) - this->rank(this->right(node)) > 2) {
					std::cout << "right > 2" << std::endl;
					return false;
				}
				if (this->rank(node) - this->rank(this->left(node)) <= 0) {
					std::cout << "left <= 0" << std::endl;
					return false;
				}
				if (this->rank(node) - this->rank(this->left(node)) > 2) {
					std::cout << "left > 2" << std::endl;
					return false;
				}
				if (this->isnil(this->right(node)) && this->isnil(this->left(node)) && this->rank(node)==1) {
					std::cout << "2,2-leaf" << std::endl;
					return false;
				}
				if (!has_been_deleted_from && this->rank(node) - this->rank(this->left(node)) == 2 && this->rank(node) - this->rank(this->right(node)) == 2) {
					std::cout << "2,2-node without deletion" << std::endl;
					return false;
				}
			}
			return true;
		}

		std::string print_tree(node_ptr node, int spaces) {
				string sp = "";
				for (int i = 0; i < spaces; i++)
					sp += "        ";
				if (this->isnil(node)) {
					return sp + ".";
				}
				string right = print_tree(this->right(node), spaces + 1);
				string left = print_tree(this->left(node), spaces + 1);
				char *num = new char[15];
				itoa(this->rank(node),num,10);
				string elem = num;

				
				char *num2 = new char[15];
				itoa(this->key(node),num2,10);
				string elem2 = num2;
				elem = sp + "[" + elem2 + "] r:" + elem;

				return right + "\n" + elem + "\n" + left;

		}

		void print_tree() {	
			cout << print_tree(root(), 0) << endl;
		}

		int height(node_ptr node) {
			int hleft, hright;
			if (this->isnil(node)) {
				return 0;
			}
			else {
				hleft = height(this->left(node));
				hright = height(this->right(node));
				return (hleft >= hright ? hleft : hright) + 1;
			}
		}

		int height() {
			return height(root());
		}

protected:

		void copy(const this_tree& right) {
			root() = copy(right.root(), this->head);
			this->my_size = right.size();
			if (!this->isnil(root())) {
				most_left() = this->min(root());
				most_right() = this->max(root());
			}
			else {
				most_left() = this->head;
				most_right() = this->head;
			}
		}

		node_ptr copy(node_ptr root, node_ptr place) {
			node_ptr new_root = this->head;

			if (!this->isnil(root)) {
				node_ptr node = this->allocate_node(this->value(root));
				node->parent = place;
				node->rank = this->rank(root);
				if (this->isnil(new_root))
					new_root = node;

				try {
					this->left(node) = copy(this->left(root), node);
					this->right(node) = copy(this->right(root), node);
				} catch (...) {
					erase_node_recursively(new_root);
					throw;
				}
			}
			return (new_root);
		}

		/* erase tree recursively */
		void erase_node_recursively(node_ptr root) {
			node_ptr node = root;
			while (!this->isnil(node)) {
				erase_node_recursively(this->right(node));	
				node = this->left(node);
				_Dest_val(this->al_elems, addressof(this->value(root)));
				this->allocate_nodes.deallocate(root, 1);
				root = node;
			}
		}

		iterator insert_value_with_hint_and_favor(bool favor_left, node_ptr place, const value_type& value)
		{
			return (insert_node_with_hint_and_favor(favor_left, place, this->allocate_node(value)));
		}

		iterator insert_node_with_hint_and_favor(bool favor_left, node_ptr place, node_ptr new_node) {
			if (this->size() + 1 >= max_size()) {
				_Dest_val(this->al_elems, addressof(this->value(new_node)));
				this->allocate_nodes.deallocate(new_node, 1);
				std::_Xlength_error("map/set<T> too long");
			}
			++this->my_size;
			new_node->parent = place;

			/* First node in the tree */
			if (place == this->head) {
				root() = new_node;
				most_left() = new_node;
				most_right() = new_node;
			}
			/* Left of place */
			else if (favor_left) {
				this->left(place) = new_node;
				if (place == most_left()) {
					most_left() = new_node;
				}
				rebalance_after_insert(new_node, true);
			}
			/* Right of place */
			else {
				this->right(place) = new_node;
				if (place == most_right())
					most_right() = new_node;				
				rebalance_after_insert(new_node, false);
			}


			return (iterator(new_node, this));
		}

		/* find leftmost node not less than _Keyval */
		node_ptr lower_bound_node(const key_type& key) const {
			node_ptr node = root();
			node_ptr place = this->head;

			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, this->key(node), key)) {
					node = this->right(node);
				}
				else {
					place = node;
					node = this->left(node);
				}
			}

			return (place);
		}
		
		/* find leftmost node not less than _Keyval */
		node_ptr lower_bound_node(const key_type& key)  {
			node_ptr node = root();
			node_ptr place = this->head;

			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, this->key(node), key)) {
					node = this->right(node);
				}
				else {
					place = node;
					node = this->left(node);
				}
			}

			return (place);
		}
		
		/* find leftmost node greater than _Keyval */
		node_ptr upper_bound_node(const key_type& key) const {
			node_ptr node = root();
			node_ptr place = this->head;

			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, key, this->key(node))) {
					place = node;
					node = this->left(node);
				}
				else {
					node = this->right(node);
				}
			}

			return (place);
		}

		/* find leftmost node greater than _Keyval */
		node_ptr upper_bound_node(const key_type& key) {
			node_ptr node = root();
			node_ptr place = this->head;

			while (!this->isnil(node)) {
				if (_DEBUG_LT_PRED(this->comp, key, this->key(node))) {
					place = node;
					node = this->left(node);
				}
				else {
					node = this->right(node);
				}
			}

			return (place);
		}

		/* left rotate */
		void left_rotate(node_ptr place)
		{
			node_ptr node = this->right(place);
			this->right(place) = this->left(node);

			if (!this->isnil(this->left(node))) {
				this->parent(this->left(node)) = place;
			}
			this->parent(node) = this->parent(place);

			if (place == root()) {
				root() = node;
			}
			else if (place == this->left(this->parent(place))) {
				this->left(this->parent(place)) = node;
			}
			else {
				this->right(this->parent(place)) = node;
			}

			this->left(node) = place;
			this->parent(place) = node;
		}

		/* right rotate */
		void right_rotate(node_ptr place)
		{
			node_ptr node = this->left(place);
			this->left(place) = this->right(node);

			if (!this->isnil(this->right(node))) {
				this->parent(this->right(node)) = place;
			}
			this->parent(node) = this->parent(place);

			if (place == root()) {
				root() = node;
			}
			else if (place == this->right(this->parent(place))) {
				this->right(this->parent(place)) = node;
			}
			else {
				this->left(this->parent(place)) = node;
			}

			this->right(node) = place;
			this->parent(place) = node;
		}
		
		int rank_dif(node_ptr node) {
			if (node == root()) {
				return 0;
			}
			return this->rank(this->parent(node)) - this->rank(node);
		}

		void promote(node_ptr node) {
			this->rank(node)++;
		}
		
		void demote(node_ptr node) {
			this->rank(node)--;
		}

		void rebalance_after_insert(node_ptr new_node, bool was_left) {
			node_ptr current = new_node;
			node_ptr parent = this->parent(new_node);
			node_ptr sibling = was_left ? this->right(parent) : this->left(parent);
			if (this->isnil(this->parent(current)) || rank_dif(current) != 0) {
				return;
			}
			while ((rank(parent)-rank(sibling)) == 1) {
				promote(parent);
				current = parent;
				if (this->isnil(this->parent(current)) || rank_dif(current) != 0) {
					return;
				}
				parent = this->parent(current);
				if (this->left(parent) == current) {
					was_left = true;
					sibling = this->right(parent);
				}
				else {
					was_left = false;
					sibling = this->left(parent);
				}
			}
			node_ptr t = was_left ? this->right(current) : this->left(current);
			if ((rank(current) - rank(t)) == 2) {
				if (was_left) {
					right_rotate(parent);
				}
				else {
					left_rotate(parent);
				}
				demote(parent);
			}
			else if ((rank(current) - rank(t)) == 1) {
				if (was_left) {
					left_rotate(current);
					right_rotate(parent);
				}
				else {
					right_rotate(current);
					left_rotate(parent);
				}
				promote(t);
				demote(current);
				demote(parent);
			}
		}

		void rebalance_after_erase(node_ptr deleted, node_ptr parent) {
			char parent_rank = this->rank(parent);

			bool was_left = this->left(parent) == deleted;
			node_ptr sibling = was_left ? this->right(parent) : this->left(parent);

			if (this->isnil(parent) || 
					(
						(parent_rank - this->rank(deleted) != 3) &&
						!(
							(parent_rank == 1) && 
							(this->isnil(this->left(parent))) && 
							(this->isnil(this->right(parent)))
						)
					)
				) { // stop
				return;
			}

			char sibling_rank = this->rank(sibling);

			bool demotion = parent_rank - sibling_rank == 2;

			node_ptr t = was_left ? this->left(sibling) : this->right(sibling);
			node_ptr u = was_left ? this->right(sibling) : this->left(sibling);

			bool double_demotion = !this->isnil(sibling) && 
									(sibling_rank - this->rank(t) == 2) && 
									(sibling_rank - this->rank(u) == 2);

			while (demotion || double_demotion) {
				if (demotion) {
					this->demote(parent);
				}
				else { // double demotion
					this->demote(parent);
					this->demote(sibling);
				}
				deleted = parent;
				parent = this->parent(deleted);
				parent_rank = this->rank(parent);

				if (this->isnil(parent) || 
					(
						(parent_rank - this->rank(deleted) != 3) &&
						!(
							(parent_rank == 1) && 
							(this->isnil(this->left(parent))) && 
							(this->isnil(this->right(parent)))
						)
					)
					) { // stop
					return;
				}

				was_left = this->left(parent) == deleted;
				sibling = was_left ? this->right(parent) : this->left(parent);
				sibling_rank = this->rank(sibling);	
				t = was_left ? this->left(sibling) : this->right(sibling);
				u = was_left ? this->right(sibling) : this->left(sibling);
				
				demotion = parent_rank - sibling_rank == 2;
				
				double_demotion = !this->isnil(sibling) && 
									(sibling_rank - this->rank(t) == 2) && 
									(sibling_rank - this->rank(u) == 2);
			}

			if (!this->isnil(sibling)) {
				if (sibling_rank - this->rank(u) == 1) { // Rotation
					if (was_left) {
						left_rotate(parent);
					}
					else {
						right_rotate(parent);
					}
					promote(sibling);
					demote(parent);
					if (this->isnil(t)) {
						demote(parent);
					}

				}
				else if ((sibling_rank - this->rank(t) == 1) && (sibling_rank - this->rank(u) == 2)) { // Double rotation
					if (was_left) {
						right_rotate(sibling);
						left_rotate(parent);
					}
					else {
						left_rotate(sibling);
						right_rotate(parent);
					}
					promote(t);
					promote(t);
					demote(sibling);
					demote(parent);
					demote(parent);
				}
			}
		}


	};


template<class rbTraits> inline
	bool operator==(const Tree<rbTraits>& left, const Tree<rbTraits>& right)
	{
		return (left.size() == right.size() && std::equal(left.begin(), left.end(), right.begin()));
	}

template<class rbTraits> inline
	bool operator!=(const Tree<rbTraits>& left, const Tree<rbTraits>& right)
	{
		return (!(left == right));
	}

template<class rbTraits> inline
	bool operator<(const Tree<rbTraits>& left, const Tree<rbTraits>& right)
	{
		return (lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
	}

template<class rbTraits> inline
	bool operator>(const Tree<rbTraits>& left, const Tree<rbTraits>& right)
	{
		return (right < left);
	}

template<class rbTraits> inline
	bool operator<=(const Tree<rbTraits>& left, const Tree<rbTraits>& right)
	{
		return (!(right < left));
	}

template<class rbTraits> inline
	bool operator>=(const Tree<rbTraits>& left, const Tree<rbTraits>& right)
	{
		return (!(left < right));
	}
}

#endif