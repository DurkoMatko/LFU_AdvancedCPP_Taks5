#include "MyUniquePointer.h"
#include <stddef.h>
#include <string>
#include <iostream>


//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os,const MyUniquePointer& g)
{
    os << "MyUniquePointer pointing to " << *g.pointer << std::endl;
    return os;
}

//move assign operator
/*MyUniquePointer &MyUniquePointer::operator=(MyUniquePointer&& ptr) noexcept{
	std::cout << "move assign operator" <<std::endl;
	//"unpoint" from previous value
	this->clear();
	//point to new place
	this->pointer = ptr.pointer;
	this->refs = ptr.refs;
	this->IncreaseReferences();
	//delete source
	ptr.pointer=nullptr;

	return *this;
}*/



MyUniquePointer::MyUniquePointer() : pointer(nullptr) {
	//const
	std::cout << "Default MyUniquePointer constructor " <<std::endl;
}

MyUniquePointer::MyUniquePointer(int *matrix) :  pointer(matrix){
	//const
	std::cout << "constructing MyUniquePointer for " << *matrix <<std::endl;
}

//move constructor
MyUniquePointer::MyUniquePointer(MyUniquePointer&& ptr) noexcept{
	std::cout << "MyUniquePointer move constructor ";
	this->pointer = ptr.pointer;
	ptr.pointer = nullptr;
}


MyUniquePointer::~MyUniquePointer() noexcept{
	std::cout << "MyUniquePointer destructor" <<  std::endl;
	delete pointer;
}

void MyUniquePointer::reset(int* matrix){
	//if they point to the same memory - no need to do anything cuz they already share the pointed object
	if(this->pointer == matrix){
		return;
	}
	//forget about last one
	delete this->pointer;;
	//point to new one
	this->pointer = matrix;
}

