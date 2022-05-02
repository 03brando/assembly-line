#include<iostream>
#include "Utilities.h"
namespace sdds
{
    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        size_t delim_pos = (str.find(getDelimiter(), next_pos));
        std::string temp = str.substr(next_pos, delim_pos - next_pos);
    
        temp = clearSpace(temp);
        if (delim_pos == next_pos)
        {
            more = false;
            throw std::string("Delimiter found at next_pos!");
        }

        next_pos = delim_pos + 1;
        if (m_widthField < temp.length())
        {
            setFieldWidth(temp.length());
        }
        if (delim_pos != std::string::npos)
        {
            more = true;
        }
        else
        {
            more = false;
        }

        return temp;
    }
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
    std::string& Utilities::clearSpace(std::string& str)
    {
        while (str.length() > 0 && str[0] == ' ')
        {
            str.erase(0, 1);
        }
        while (str.length() > 0 && str[str.length() - 1] == ' ')
        {
            str.erase(str.length() - 1, 1);
        }
        return str;
    }
}