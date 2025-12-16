#pragma once

#include <vector>
#include <functional>
#include <algorithm>

// Forward declaration
template<typename>
class MulticastDelegate;

template<typename... Args>
class MulticastDelegate<void(Args...)>
{
public:
	using FunctionType = std::function<void(Args...)>;
	using HandleType = size_t;

private:
	struct DelegateEntry
	{
		HandleType handle;
		FunctionType function;
	};

	std::vector<DelegateEntry> m_delegates;
	HandleType m_nextHandle = 0;

public:
	/* Add a free or static function */
	HandleType Add(void(*fn)(Args...))
	{
		return AddInternal(fn);
	}

	/* Add a member function */
	template<typename T>
	HandleType Add(T* object, void(T::* fn)(Args...))
	{
		auto lambda = [object, fn](Args... args) { (object->*fn)(std::forward<Args>(args)...);  };
		return AddInternal(std::move(lambda));
	}

	/* Add a const member function */
	template<typename T>
	HandleType Add(T* object, void(T::* fn)(Args...) const)
	{
		auto lambda = [object, fn](Args... args) { (object->*fn)(std::forward<Args>(args)...); };
		return AddInternal(std::move(lambda));
	}

	/* Add lambda or functor */
	template<typename Functor>
	HandleType Add(Functor&& functor)
	{
		return AddInternal(std::forward<Functor>(functor));
	}

	/* Remove a specific delegate by handle */
	void Remove(HandleType handle)
	{
		m_delegates.erase(std::remove_if(m_delegates.begin(), m_delegates.end(), [handle](const DelegateEntry& entry) {return entry.handle == handle; }), m_delegates.end());
	}

	// Clear all delegates
	void Clear()
	{
		m_delegates.clear();
	}

	void Broadcast(Args... args) const
	{
		for (const auto& entry : m_delegates)
		{
			entry.function(args...);
		}
	}

	bool IsBound() const
	{
		return !m_delegates.empty();
	}

	size_t Num() const
	{
		return m_delegates.size();
	}

private:
	template<typename Functor>
	HandleType AddInternal(Functor&& functor)
	{
		HandleType handle = m_nextHandle++;
		m_delegates.push_back({ handle, std::forward<Functor>(functor) });
		return handle;
	}
};
