#include <iostream>
#include <string>

#include "delegate.h"
#include "multicast_delegate.h"

static int ReturnNumb()
{
	return 5;
}

static void PrintNumber()
{
	std::cout << "50 something" << std::endl;
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

	void MultiTestMember(const int health)
	{
		std::cout << "Health is : " << health << " And Age is : " << age << std::endl;
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

	// -------------------- Multicast delegate test --------------------
	MulticastDelegate<void()> multi_printNumber;
	multi_printNumber.Add(&PrintNumber);
	multi_printNumber.Broadcast();

	MulticastDelegate<void(const int)> multi_member_health;
	multi_member_health.Add(some_actor, &TestClass::MultiTestMember);
	multi_member_health.Add(TestFunctor());
	multi_member_health.Broadcast(42);

	return EXIT_SUCCESS;
}