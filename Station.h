#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
namespace sdds
{
    class Station
    {
        int m_stationID{};
        std::string m_name{};
        std::string m_desc{};
        size_t m_serialNum{};
        size_t m_numItems{};
        static size_t m_widthField;
        static int id_generator;

    public:
        Station(){};
        Station(const std::string& str);
        const std::string& getItemName() const;
        const size_t getNextSerialNumber();
        const size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif // !SDDS_STATION_H
