#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(){}
    CustomerOrder::CustomerOrder(const std::string& str)
    {
        if (!str.empty())
        {
            Utilities util;
            size_t pos = 0;
            bool more = false;
            std::string temp;

            m_name = util.extractToken(str, pos, more);
            m_product = util.extractToken(str, pos, more);
            temp = str.substr(pos, str.length() - pos);
            m_cntItem = (std::count(temp.begin(), temp.end(), util.getDelimiter())) + 1;
            m_lstItem = new Item * [m_cntItem];
            for (size_t i = 0; i < m_cntItem; i++)
            {
                m_lstItem[i] = new Item(util.extractToken(str, pos, more));
            }
            if (m_widthField < util.getFieldWidth())
                m_widthField = util.getFieldWidth();
        }
    }
    CustomerOrder::CustomerOrder(const CustomerOrder& co)
    {
        throw "Cannot perform copy operations!";
    }
    CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
    {
        *this = std::move(co);
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
    {
        if (this != &co)
        {
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_name = co.m_name;
            m_product = co.m_product;
            m_cntItem = co.m_cntItem;
            m_lstItem = co.m_lstItem;
            co.m_name = "";
            co.m_product = "";
            co.m_cntItem = 0;
            co.m_lstItem = nullptr;
        }
        return *this;
    }
    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete this->m_lstItem[i];
        }
        delete[] m_lstItem;
    }
    bool CustomerOrder::isOrderFilled() const
    {
        bool res = true;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (!m_lstItem[i]->m_isFilled)
                res = false;
        }
        return res;
    }
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        bool res = true;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName)
            {
                if (!m_lstItem[i]->m_isFilled)
                    res = false;
            }
        }
        return res;
    }
    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        bool filled = false;
       
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (station.getItemName() == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false && !filled)
            {
                if (station.getQuantity() > 0)
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    filled = true;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }
    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
            os << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName << "   - ";
            if (m_lstItem[i]->m_isFilled)
            {
                os << "FILLED";
            }
            else
            {
                os << "TO BE FILLED";
            }
            os << std::endl;
        }
    }
}