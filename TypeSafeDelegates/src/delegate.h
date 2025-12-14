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

	// Check if bound
	bool IsBound() const { return m_function != nullptr; }

	// Unbind
	void Unbind() { m_function = nullptr; }

	/* Execute */
	ReturnType Execute(Args... args) const
	{
		if (m_function)
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
