#pragma once

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <new>
#include <iostream>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const CMyArray& other)
	{
		if (other.GetSize() != 0)
		{
			m_begin = new T[other.GetCapacity()];
			memcpy(m_begin, other.m_begin, sizeof(T) * other.GetSize());
			m_size = other.GetSize();
			m_capacity = other.GetCapacity();
		}
	}

	CMyArray& operator=(const CMyArray& other)
	{
		if (this != &other)
		{
			CMyArray tmp(other);

			std::swap(m_begin, tmp.m_begin);
			std::swap(m_size, tmp.m_size);
			std::swap(m_capacity, tmp.m_capacity);
		}
		return *this;
	}

	CMyArray(CMyArray&& other) noexcept
		: m_begin(other.m_begin)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		other.m_begin = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_begin;
			m_begin = other.m_begin;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			other.m_begin = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	~CMyArray()
	{
		delete[] m_begin;
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Out of range");
		}
		return m_begin[index];
	}

	T const& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Out of range");
		}
		return m_begin[index];
	}

	void Resize(size_t size)
	{
		if (size != GetSize())
		{
			T* p = new T[size];
			if (size > GetCapacity())
			{
				Reserve(size);
			}
			size_t elementsToCopy = std::min(GetSize(), size);
			for (size_t i = 0; i < elementsToCopy; ++i)
			{
				p[i] = m_begin[i];
			}
			for (size_t i = GetSize(); i < size; ++i)
			{
				p[i] = T();
			}
			delete[] m_begin;
			m_begin = p;
			m_size = size;
		}
	}

	void Clear()
	{
		m_begin = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	size_t GetCapacity() const
	{
		return m_capacity;
	}

	void Push(const T & value)
	{
		if (m_size == m_capacity)
		{
			Reserve(m_capacity ? m_capacity * 2 : 1);
		}
		new (m_begin + m_size) T(value);
		++m_size;
	}

	void Reserve(size_t newCapacity)
	{
		if (GetCapacity() >= newCapacity)
		{
			return;
		}
		T* p = new T[newCapacity];
		for (size_t i = 0; i < GetSize(); ++i)
		{
			p[i] = m_begin[i];
		}
		delete[] m_begin;
		m_begin = p;
		m_capacity = newCapacity;
	}

	template <bool isReverse>
	class CIterator
	{
	public:
		CIterator(T* ptr)
			: m_ptr(ptr)
		{
		}

		CIterator operator++(int)
		{
			if (isReverse)
			{
				return m_ptr--;
			}
			else
			{
				return m_ptr++;
			}
		}

		CIterator operator--(int)
		{
			if (isReverse)
			{
				return m_ptr++;
			}
			else
			{
				return m_ptr--;
			}
		}

		CIterator operator++()
		{
			if (isReverse)
			{
				return --m_ptr;
			}
			else
			{
				return ++m_ptr;
			}
		}

		CIterator operator--()
		{
			if (isReverse)
			{
				return ++m_ptr;
			}
			else
			{
				return --m_ptr;
			}
		}

		bool operator!=(const CIterator& it) const
		{
			return m_ptr != it.m_ptr;
		}

		bool operator==(const CIterator& it) const
		{
			return m_ptr == it.m_ptr;
		}

		T& operator*()
		{
			return *m_ptr;
		}
		const T& operator*() const
		{
			return *m_ptr;
		}
	
	private:
		T* m_ptr;
	};

	template <bool isReverse>
	class CIterator;

	typedef CIterator<false> Iterator;
	typedef CIterator<true> IteratorReverse;

	Iterator begin()
	{
		return m_begin;
	}

	Iterator end()
	{
		return m_begin + m_size;
	}

	Iterator begin() const
	{
		return m_begin;
	}

	Iterator end() const
	{
		return m_begin + m_size;
	}

	IteratorReverse rbegin()
	{
		return m_begin + m_size - 1;
	}

	IteratorReverse rend()
	{
		return m_begin - 1;
	}

	IteratorReverse rbegin() const
	{
		return m_begin + m_size - 1;
	}

	IteratorReverse rend() const
	{
		return m_begin - 1;
	}

private:
    T *m_begin = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};
