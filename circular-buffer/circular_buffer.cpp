#include "circular_buffer.h"
#include <stdexcept>
#include <string>

using namespace std;

namespace circular_buffer {

	template <class T>
	circular_buffer<T>::circular_buffer(std::size_t size) : max_size{size}, buffer_(std::unique_ptr<T[]> (new T[size])) {}

	template <class T>
	T circular_buffer<T>::read()
	{
		if( is_empty())
		{
			throw (std::domain_error( "The buffer is empty"));
		}
		else
		{
			auto return_this = buffer_[tail_];
			increment(tail_);
			is_full_ = false;
			return return_this;
		}
	}

	template <class T>
	void circular_buffer<T>::write(T add_to_buff)
	{
		if(is_full_)
		{
			throw (std::domain_error( "The buffer is full"));
		}
		else
		{
			buffer_[head_] = add_to_buff;
			increment(head_);
			check_if_full();
		}
	}

	template <class T>
	void circular_buffer<T>::clear()
	{
		tail_ = head_;
		is_full_ = false;
	}

	template <class T>
	void circular_buffer<T>::overwrite(T add_to_buff)
	{
		if(is_full_)
		{
			buffer_[head_] = add_to_buff;
			increment(head_);
			increment(tail_);
		}
		else
		{
			write(add_to_buff);
		}
	}

	template <class T>
	void circular_buffer<T>::check_if_full()
	{
		if((head_ > tail_) && (head_ - tail_ == max_size))
		{
			is_full_ = true;
		}
		if( head_ + max_size - tail_ == max_size)
		{
			is_full_ = true;
		}
	}

	template <class T>
	bool circular_buffer<T>::is_empty() const
	{
		return (head_ == tail_) && (!is_full_);
	}

	template <class T>
	void circular_buffer<T>::increment(std::size_t& index)
	{
		index++;
		index %= max_size;
	}

	template class circular_buffer<int>;
	template class circular_buffer<string>;
}  // namespace circular_buffer
