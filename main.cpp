#include "MySharedPointer.cpp"
#include "MyUniquePointer.cpp"

MySharedPointer test(){
	return MySharedPointer(new int(3));
};

MySharedPointer testMove(){
	return MySharedPointer(new int(4));
};

MyUniquePointer testMoveUnique(){
	return MyUniquePointer(new int(40));
};

int main(){


	MySharedPointer a (new int(1));
	//copy constructor
	MySharedPointer b = a;

	MySharedPointer c (new int(2));
	//copy assign operator
	c = a;

	std::cout << b;
	std::cout << a;

	a.~MySharedPointer();   //Calling a destructor releases the resources owned by the object, but it does not release the memory allocated to the object itself

	std::cout << b;
	std::cout << a;

	std::cout <<std::endl<< "FUNCTION" <<std::endl;
	MySharedPointer d (test());
	MySharedPointer e = d;
	std::cout << e;


	//move assign operator
	std::cout <<std::endl<< "MOVE" <<std::endl;
	MySharedPointer f;
	f = testMove();
	e=f;
	std::cout << f;
	//e.reset(new int(10));
	std::cout << f;


	std::cout <<std::endl<< "UNIQUE POINTER" <<std::endl;
	MyUniquePointer z (new int(10));
	std::cout << z;
	z.reset(new int(20));
	std::cout << z;
	//z = MyUniquePointer(new int(30));   //error - because it needs copy operation and MyUniquePointer is not copyable


	MyUniquePointer x (testMoveUnique());
	std::cout << x;

	std::cout <<std::endl<< "DESTRUCTORS" <<std::endl;
}