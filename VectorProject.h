#pragma once

#include <memory>
#include <iostream>
#include <new>

template<typename T>
class Vector
{
public:
	class VectorIterator
	{
	public:
		VectorIterator(T* ptr)
			:_ptr(ptr) {}

		VectorIterator& operator++()
		{
			++_ptr;
			return *this;
		}

		VectorIterator operator++(int)
		{
			VectorIterator iterator = *this;
			++(*this);
			return iterator;
		}

		VectorIterator& operator--()
		{
			_ptr--;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator iterator = *this;
			--(*this);
			return iterator;
		}

		T& operator*()
		{
			return *_ptr;
		}
	
		bool operator ==(const VectorIterator& other) const
		{
			return _ptr == other._ptr;
		}

		bool operator !=(const VectorIterator& other) const
		{
			return !(*this == other);
		}
	private:
		T* _ptr;
	};
public:
	Vector()
	{
		AllocMemory(5);
	}

	~Vector()
	{
		::operator delete(_data, _capacity * sizeof(T));
	}

	size_t Size() const
	{
		return _size;
	}

	size_t Capacity() const
	{
		return _capacity;
	}

	void V_pushback(const T& value)
	{
		if (_size >= _capacity)
		{
			AllocMemory(_capacity * 2);
		}
		_data[_size] = value;
		_size++;
	}

	void V_pushback(T&& value)
	{
		if (_size >= _capacity)
		{
			AllocMemory(_capacity * 2);
		}
		_data[_size] = std::move(value);
		_size++;
	}

	template<typename... Args>
	auto& V_EmplaceBack(Args&&... args)
	{
		if (_size >= _capacity)
		{
			AllocMemory(_capacity * 2);
		}

		new(&_data[_size]) T(std::forward<Args>(args)...);
		return _data[_size++];
	}

	void V_popback()
	{
		if (_size > 0)
		{
			_size--;
			_data[_size].~T();
		}
	}

	void V_clear()
	{
		if (_size == 0)
		{
			return;
		}

		for (size_t i = 0; i < _size; i++)
		{
			_data[i].~T();
		}
		_size = 0;
	}

	bool V_Empty()
	{
		return _size == 0;
	}

	const auto& operator [] (size_t value) const
	{
		if (value >= _size)
		{
			throw std::out_of_range("out of size");
		};
		return _data[value];
	}

	auto& operator [] (size_t value)
	{
		if (value >= _size)
		{
			throw std::out_of_range("out of size");
		};
		return _data[value];
	}

	VectorIterator begin()
	{
		return VectorIterator(_data);
	}

	VectorIterator end()
	{
		return VectorIterator(_data + _size);
	}

private:
	void AllocMemory(size_t newcapacity)
	{
		//std::unique_ptr<T[]> NewMemory(new T[newcapacity]);
		
		T* NewMemory = (T*)::operator new(newcapacity * sizeof(T));

		for (size_t i = 0; i < newcapacity; ++i) {
			new (NewMemory + i) T; 
		}

		size_t __size = _size;
		if (newcapacity < __size)
		{
			__size = std::move(newcapacity);
		}

		for (size_t i = 0; i < _size; ++i)
		{
			NewMemory[i] = (std::move(_data[i]));
		}

		for (size_t i = 0; i < _size; ++i)
		{
			_data[i].~T();
		}

		//_data.reset();

		::operator delete(_data, _capacity * sizeof(T));
		_data = NewMemory;
		_capacity = newcapacity;

	}
private:
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};

