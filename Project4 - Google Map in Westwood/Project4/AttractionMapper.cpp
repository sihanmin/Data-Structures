#include "provided.h"
#include <string>
#include "MyMap.h"
#include <cctype>
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> m_attractions;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    StreetSegment cur;
    for (int i = 0; i < ml.getNumSegments(); i++)
    {
        ml.getSegment(i, cur);  // find the current streetsegment
        for (int j = 0; j != cur.attractions.size(); j++)
        {
            string lowerName;   // turn the name all to lower
            for (int k = 0; k < cur.attractions[j].name.size(); k++)
                lowerName += tolower(cur.attractions[j].name[k]);
            m_attractions.associate(lowerName, cur.attractions[j].geocoordinates);
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    string lowerName;   // turn to lower cases
    for (int k = 0; k < attraction.size(); k++)
        lowerName += tolower(attraction[k]);
    const GeoCoord* temp = m_attractions.find(lowerName);
    if (temp == nullptr)
        return false;
    else
        gc = *temp;
    return true;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
