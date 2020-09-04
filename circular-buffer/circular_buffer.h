#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <memory>

// A circular buffer is a container that has fixed memory. If you add elements to the container when it is full it will overwrite the oldest element.
// member functions:
// 	circular_buffer - creates a circular buffer object that can store elements up to number size.
// 	read			- returns the oldest element. If buffer is empty it throws a domain error.
// 	write			- add an element to the buffer. If the buffer is full it throws a domain error.
// 	overwrite		- add an element to the buffer. If the buffer is full it will overwrite the oldest element, the new element will be in place youngest.
namespace circular_buffer {

	template <class T>
	class circular_buffer
	{
		public:
			circular_buffer(std::size_t size);
			T read();
			void write(T add_to_buff);
			void clear();
			void overwrite(T add_to_buff);

		private:
			std::size_t max_size;
			std::unique_ptr<T[]> buffer_;
			std::size_t head_ = 0;
			std::size_t tail_ = 0;
			bool is_full_ = false;
			bool is_empty() const;
			void check_if_full();
			void increment(std::size_t& index);
	};
}  // namespace circular_buffer

#endif // CIRCULAR_BUFFER_H