#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <memory>

namespace binary_search_tree {

	template <typename T>
	class binary_tree
	{
		public:
			binary_tree(T data);
			binary_tree(T data, binary_tree<T>& parent);
			void insert(const T& data);
			const T& data() const;
			using unique_tree_ptr = std::unique_ptr<binary_tree<T>>;
			const unique_tree_ptr& left() const;
			const unique_tree_ptr& right() const;

			class const_iterator
			{
			public:
				const_iterator() = default;
				explicit const_iterator(const binary_tree *root);
				bool operator==(const const_iterator& other) const;
				bool operator!=(const const_iterator& other) const;
				const T& operator*() const;
				const_iterator& operator++();
			private:
				static const binary_tree<T>* go_left(const binary_tree<T>* find_left_leaf);
				const binary_tree<T>* current_leaf_;
			};

			const_iterator begin() const;
			const_iterator end() const;
		private:
			T root_;
			unique_tree_ptr right_;
			unique_tree_ptr left_;
			binary_tree<T>* parent_;
	};
}  // namespace binary_search_tree
#endif // BINARY_SEARCH_TREE_H