#pragma once

#include <functional>
#include <algorithm>

// Forward declaration
template<typename>
class Delegate;

template<typename ReturnType, typename... Args>
class Delegate<ReturnType(Args...)>
{
public:
	using FunctionType = std::function<ReturnType(Args...)>;

	Delegate() = default;

	/* Bind to a free or static function */
	void Bind(ReturnType(*fn)(Args...))
	{
		m_function = fn;
	}

	/* Bind to a member function */
	template<typename T>
	void Bind(T* object, ReturnType(T::* fn)(Args...))
	{
		m_function = [object, fn](Args... args) { return (object->*fn)(std::forward<Args>(args)...); };
	}

	/* Bind to a member function const overload */
	template<typename T>
	void Bind(T* object, ReturnType(T::* fn)(Args...) const)
	{
		m_function = [object, fn](Args... args) { return (object->*fn)(std::forward<Args>(args)...); };
	}

	/* Bind to lambda or functor */
	template<typename Functor>
	void BindLambda(Functor&& functor)
	{
		m_function = std::forward<Functor>(functor);
	}

	// Check if bound
	bool IsBound() const { return m_function != nullptr; }

	// Unbind
	void Unbind() { m_function = nullptr; }

	/* Execute */
	ReturnType Execute(Args... args) const
	{
		if (IsBound())
		{
			return m_function(std::forward<Args>(args)...);
		}

		if constexpr (!std::is_void_v<ReturnType>)
		{
			return ReturnType{};
		}
	}

private:
	FunctionType m_function;
};
