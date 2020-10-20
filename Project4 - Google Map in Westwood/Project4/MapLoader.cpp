#include "provided.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;

private:
    vector<StreetSegment*> m_streets;
    int m_segementsNum;
    
    int toNum(string &s);
};

MapLoaderImpl::MapLoaderImpl()
{
    m_segementsNum = 0;
}

MapLoaderImpl::~MapLoaderImpl()
{
    for (vector<StreetSegment*>::iterator i = m_streets.begin(); i != m_streets.end(); i++)
    {
        delete (*i);
    }
}


int MapLoaderImpl::toNum(string &s)
{
    stringstream a;
    int i;
    a << s;
    a >> i;
    return i;
}


bool MapLoaderImpl::load(string mapFile)
{
    ifstream map(mapFile);
    if (! map)
        return false;
    
    string line;
    //string lineNum = 3;
    unsigned long break1, break2, break3;
    unsigned long break4, break5;
    int curNum = 0;
    while (getline(map, line))
    {
        m_segementsNum++;
        m_streets.push_back(new StreetSegment);
        m_streets[m_segementsNum-1]->streetName = line;
        string startLat, startLong, endLat, endLong;
        
        // seperate each coordinate from the string
        getline(map, line);
        break1 = line.find(',', 0);
        startLat = line.substr(0, break1);
        
        while (line[break1] == ',' || line[break1] == ' ')
            break1++;
        break2 = line.find(' ', break1);
        startLong = line.substr(break1, break2-break1);
        
        while (line[break2] == ',' || line[break2] == ' ')
            break2++;
        break3 = line.find(',', break2);
        endLat = line.substr(break2, break3-break2);
        
        while (line[break3] == ',' || line[break3] == ' ')
            break3++;
        endLong = line.substr(break3, line.size()-break3);
        
        GeoCoord S(startLat, startLong);
        GeoCoord E(endLat, endLong);
        m_streets[m_segementsNum-1]->segment = GeoSegment(S, E);
        
        getline(map, line);
        curNum = toNum(line);
        for (int i  = 0; i < curNum; i++)
        {
            getline(map, line);
            break4 = line.find('|', 0);
            break5 = line.find(',', break4) + 1;
            m_streets[m_segementsNum-1]->attractions.push_back(*new Attraction);
            m_streets[m_segementsNum-1]->attractions[i].name = line.substr(0, break4);
            GeoCoord C(line.substr(break4+1, break5-break4-2), line.substr(break5, line.size()-break5));
            m_streets[m_segementsNum-1]->attractions[i].geocoordinates = C;
        }
        
    }
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
	return m_segementsNum;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum >= getNumSegments() || segNum < 0)
        return false;
    seg = *m_streets[segNum];
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}
