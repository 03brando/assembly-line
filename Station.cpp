#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
namespace sdds
{
	size_t Station::m_widthField{};
	int Station::id_generator{};

	Station::Station(const std::string& str)
	{
		Utilities util{};
		size_t pos{};
		bool more = false;

		m_stationID = ++id_generator;
		m_name = util.extractToken(str, pos, more);
		m_serialNum = stoi(util.extractToken(str, pos, more));
		m_numItems = stoi(util.extractToken(str, pos, more));
		m_widthField = std::max(m_widthField, util.getFieldWidth());
		m_desc = util.extractToken(str, pos, more);
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	const size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}
	const size_t Station::getQuantity() const
	{
		return m_numItems;
	}
	void Station::updateQuantity()
	{
		if (m_numItems > 0) --m_numItems;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::right << std::setfill('0') << m_stationID << " | ";
		os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name << "  | ";
		os << std::setw(6) << std::right << std::setfill('0') << m_serialNum << " | ";

		if (full)
		{
			os << std::setw(4) << std::setfill(' ') << m_numItems << " | " << m_desc << std::endl;
		}
		else
		{
			os << std::endl;
		}
	}
}