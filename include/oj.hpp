#pragma once
#include <memory>
#include <utility>

namespace std
{
template<class T, class U = T>
T exchange(T& obj, U&& new_value)
{
	T old_value = std::move(obj);
	obj = std::forward<U>(new_value);
	return old_value;
}

template<class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
} // namespace std
