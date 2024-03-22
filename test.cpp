#include "VectorProject.h"
#include <iostream>

int main()
{
	Vector <std::string> test01;

	test01.V_pushback("hellow");
	test01.V_pushback("world");

	std::cout << test01[0] << " " << test01[1] << std::endl;

	test01.V_popback();

	std::cout << "test01 capaity : " << test01.Capacity() << " test01 size : " << test01.Size() << std::endl;

	//std::cout << test01[0] << " " << test01[1] << std::endl;

	Vector<int> test02;
	test02.V_EmplaceBack(1);
	test02.V_EmplaceBack(2);
	test02.V_EmplaceBack(3);
	test02.V_EmplaceBack(4);
	test02.V_EmplaceBack(5);

	for (Vector<int>::VectorIterator it = test02.begin(); it != test02.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	
	for (auto values : test02)
	{
		std::cout << values << std::endl;
	}

	test02.V_clear();

	std::cout << test02.V_Empty() << std::endl;
}