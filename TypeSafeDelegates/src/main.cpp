#include <iostream>
#include <string>

#include "delegate.h"

static int ReturnNumb()
{
	return 5;
}

class TestClass
{
public:
	std::string ReturnNameAndId(const std::string& name)
	{
		return name + " 25";
	}
};

int main()
{
	// Sample Objects
	TestClass some_actor;

	// Event for signature int()
	Delegate<int()> simple_delegate;
	simple_delegate.Bind(&ReturnNumb);

	std::cout << simple_delegate.Execute() << std::endl;

	// Event for signature string(string)
	Delegate<std::string(const std::string&)> name_delegate;
	name_delegate.Bind(&some_actor, &TestClass::ReturnNameAndId);

	std::cout << name_delegate.Execute("Haris") << std::endl;

	return EXIT_SUCCESS;
}