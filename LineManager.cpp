#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"
namespace sdds
{
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
		Utilities util;
		std::ifstream f(file);

		if (f)
		{
			Workstation* firstWS{};
			Workstation* currentWS{};
			Workstation* nextWS{};
			std::string line{}, current{}, next{};
			bool more = false;
			size_t pos{};
			m_cntCustomerOrder = g_pending.size();

			while (std::getline(f, line))
			{
				current = util.extractToken(line, pos, more);
				currentWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station)
					{
						return station->getItemName() == current;
					});
				if (currentWS) 
					m_activeLine.push_back(currentWS);
				
				if (more)
				{
					next = util.extractToken(line, pos, more);
					nextWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station)
						{
							return station->getItemName() == next;
						});
					if (nextWS)
						currentWS->setNextStation(nextWS);
					
				}
			}
			for_each(stations.begin(), stations.end(), [&](Workstation* ws)
				{
					firstWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station)
						{
							return station->getNextStation() == firstWS;
						});
				});

			if (firstWS)
				m_firstStation = firstWS;
		}
		else
		{
			throw "Cannot open file!";
		}

		f.close();
    }
    void LineManager::reorderStations()
    {
        std::vector<Workstation*> reordered{};
        Workstation* temp = m_firstStation;

        while (temp)
        {
            reordered.push_back(temp);
            temp = temp->getNextStation();
        }
        m_activeLine = reordered;
    }
    bool LineManager::run(std::ostream& os)
    {
        static size_t count = 0;

        os << "Line Manager Iteration: " << ++count << std::endl;
        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station)
            {
                station->fill(os);
            });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station)
            {
                station->attemptToMoveOrder();
            });

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }
    void LineManager::display(std::ostream& os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station)
            {
                station->display(os);
            });
    }
}