#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include <stddef.h>
#include <string>
#include <iostream>


class MyUniquePointer{
	public:
		MyUniquePointer();
		MyUniquePointer(int rows, int cols);
		MyUniquePointer(MyUniquePointer&& ptr) noexcept; 		//move constructor
		MyUniquePointer(MyUniquePointer& ptr) = delete;		//copy constructor can't be defined by compiler  because that would mean there are 2 unique_ptrs pointing to one target (not unique anymore)
		virtual ~MyUniquePointer() noexcept;
		void reset();
		void reset(int rows,int cols);
		friend std::ostream& operator<<(std::ostream& os,const MyUniquePointer& g);		//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		MyUniquePointer& operator=(MyUniquePointer&& ptr) noexcept;						//move assign can exist
		MyUniquePointer& operator=(const MyUniquePointer& ptr) = delete;   					//also copy assignment operator cant be defined.....MyUniquePointer must stay noncopyable\
	private:
		void clear();
		int **pointer;
		int *rows;
		int *cols;
};

#endif // MY_UNIQUE_PTR