#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include <stddef.h>
#include <string>
#include <iostream>


class MyUniquePointer{
	public:
		MyUniquePointer();
		MyUniquePointer(int* matrix);
		MyUniquePointer(MyUniquePointer& ptr) = delete;		//copy constructor can't be defined by compiler  because that would mean there are 2 unique_ptrs pointing to one target (not unique anymore)
		MyUniquePointer(MyUniquePointer&& ptr) noexcept; 		//move constructor
		virtual ~MyUniquePointer() noexcept;
		void reset(int* matrix);
		friend std::ostream& operator<<(std::ostream& os,const MyUniquePointer& g);		//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		MyUniquePointer& operator=(const MyUniquePointer& ptr) = delete;   					//also copy assignment operator cant be defined.....MyUniquePointer must stay noncopyable\
		//MyUniquePointer& operator=(MyUniquePointer&& ptr) noexcept;						//move assign can exist
	private:
		int *pointer;
		std::size_t *refs;
		int mWidth, mHeight;
};

#endif // MY_UNIQUE_PTR