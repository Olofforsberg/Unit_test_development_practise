#include "binary_search_tree.h"

#include <string>

using namespace std;
namespace binary_search_tree {

	template<typename T>
	const T& binary_tree<T>::data() const
	{
		return root_;
	}
	template<typename T>
	const std::unique_ptr<binary_tree<T>>& binary_tree<T>::left() const
	{
		return left_;
	}
	template<typename T>
	const std::unique_ptr<binary_tree<T>>& binary_tree<T>::right() const
	{
		return right_ ;
	}
	template<typename T>
	binary_tree<T>::binary_tree(T data): root_{data}, right_{nullptr}, left_{nullptr}, parent_{nullptr} {}

	template<typename T>
	void binary_tree<T>::insert(const T& data)
	{
		if (data <= root_)
		{
			if((bool) left())
			{
				left()->insert(data);
			}
			else
			{
				left_ = make_unique<binary_tree<T>>( binary_tree(data) );
				left_->parent_ = this;
			}
		}
		else
		{
			if((bool) right())
			{
				right()->insert(data);
			}
			else
			{
				right_ = make_unique<binary_tree<T>>( binary_tree(data ));
				right_->parent_ = this;
			}
		}
	}

	template<typename T>
	typename binary_tree<T>::const_iterator binary_tree<T>::begin() const
	{
		return const_iterator(this);
	}

	template<typename T>
	typename binary_tree<T>::const_iterator binary_tree<T>::end() const
	{
		return {};
	}

	template<typename T>
	binary_tree<T>::const_iterator::const_iterator(const binary_tree* root)
	{
		current_leaf_ = root;
		current_leaf_ = go_left(current_leaf_);
	}

	template<typename T>
	const binary_tree<T>* binary_tree<T>::const_iterator::go_left(const binary_tree<T>* find_left_leaf)
	{
        const binary_tree<T>* temp = find_left_leaf;
		while ((bool) temp->left() ) 
		{
			temp = temp->left_.get();
		}
        return temp;
	}

	template<typename T>
	const T& binary_tree<T>::const_iterator::operator*() const
	{
		return current_leaf_->data();
	}

	template <typename T>
	bool binary_tree<T>::const_iterator::operator!=(const const_iterator& other) const
	{
		return !(*this == other);
	}

	template <typename T>
	bool binary_tree<T>::const_iterator::operator==(const const_iterator& other) const
	{
	    return current_leaf_ == other.current_leaf_;
	}

	template<typename T>
	typename binary_tree<T>::const_iterator& binary_tree<T>::const_iterator::operator++()
	{
		if ((bool) current_leaf_->right())
		{
			current_leaf_ = go_left(current_leaf_->right().get());
			return *this;
		}
		else
		{
			while((bool) current_leaf_->parent_ && current_leaf_ == current_leaf_->parent_->right().get())
			{
				current_leaf_ = current_leaf_->parent_;
			}
			current_leaf_ = current_leaf_->parent_;
			return *this;
		}
	}

	template class binary_tree<uint32_t>;
	template class binary_tree<string>;
}  // namespace binary_search_tree
