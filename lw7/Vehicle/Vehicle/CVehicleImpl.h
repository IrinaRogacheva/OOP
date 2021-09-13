#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

template <typename Base, typename Passenger>
class CVehicleImpl : public Base
{
public:
	CVehicleImpl(size_t placeCount)
		: m_placeCount(placeCount){};

	bool IsEmpty() const
	{
		return m_passengers.empty();
	};

	bool IsFull() const
	{
		return m_passengers.size() == m_placeCount;
	};

	size_t GetPlaceCount() const
	{
		return m_placeCount;
	};

	size_t GetPassengerCount() const
	{
		return m_passengers.size();
	};

	void RemoveAllPassengers()
	{
		m_passengers.clear();
	};

	void AddPassenger(std::shared_ptr<Passenger> pPassenger)
	{
		if (IsFull())
		{
			throw std::logic_error("Trying to add passenger in full vehicle");
		}
		m_passengers.push_back(pPassenger);
	};

	Passenger const& GetPassenger(size_t index) const
	{
		if (index >= m_passengers.size())
		{
			throw std::out_of_range("passenger index is out of range");
		}
		return *m_passengers[index];
	};

	void RemovePassenger(size_t index) override
	{
		if (index >= m_passengers.size())
		{
			throw std::out_of_range("passenger index is out of range");
		}
		m_passengers.erase(m_passengers.begin() + index);
	};

private:
	std::vector<std::shared_ptr<Passenger>> m_passengers;
	const size_t m_placeCount;
};
