#include <iostream>
#include <string>

#include "delegate.h"
#include "multicast_delegate.h"

static int ReturnNumb()
{
	return 5;
}

class TestClass
{
public:
	// ctor
	TestClass(int x) : age{ x } {}

	std::string ReturnNameAndId(const std::string& name)
	{
		return name + std::to_string(age);
	}

private:
	int age;
};

class TestFunctor
{
public:
	void operator()(int x)
	{
		std::cout << "The Value is (Functor): " << x << std::endl;
	}
};

int main()
{
	// Sample Objects
	TestClass* some_actor = new TestClass(25);

	// Event for signature int()
	Delegate<int()> simple_delegate;
	simple_delegate.Bind(&ReturnNumb);

	std::cout << simple_delegate.Execute() << std::endl;

	// Event for signature string(string)
	Delegate<std::string(const std::string&)> name_delegate;
	name_delegate.Bind(some_actor, &TestClass::ReturnNameAndId);

	std::cout << name_delegate.Execute("Haris") << std::endl;

	// Event signature for a functor
	Delegate<void(int)> lambda_delegate;
	lambda_delegate.BindLambda([](int x) { std::cout << "The value is: " << x << std::endl; });
	lambda_delegate.BindLambda(TestFunctor());

	lambda_delegate.Execute(19);

	return EXIT_SUCCESS;
}