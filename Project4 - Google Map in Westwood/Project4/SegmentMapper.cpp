#include "provided.h"
#include <vector>
#include "MyMap.h"
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<string, vector<StreetSegment>> m_associations;
    
    void addAssociate(string coor, StreetSegment street);
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    StreetSegment cur;
    string coord;
    for (int i = 0; i < ml.getNumSegments(); i++)
    {
        ml.getSegment(i, cur);  // turn coordinate into a string as the key
        coord = cur.segment.start.latitudeText + ',' + cur.segment.start.longitudeText;
        addAssociate(coord, cur);
        coord = cur.segment.end.latitudeText + ',' + cur.segment.end.longitudeText;
        addAssociate(coord, cur);
        for (int j = 0; j != cur.attractions.size(); j++)
        {
            coord = cur.attractions[j].geocoordinates.latitudeText + ',' + cur.attractions[j].geocoordinates.longitudeText;
            addAssociate(coord, cur);
        }
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    string coord = gc.latitudeText + ',' + gc.longitudeText;
    return *(m_associations.find(coord));
}

void SegmentMapperImpl::addAssociate(string coor, StreetSegment street)
{
    vector<StreetSegment> segments;
    vector<StreetSegment>* place = m_associations.find(coor);
    if (place == nullptr)
    {
        segments.push_back(street);
        m_associations.associate(coor, segments);
        return;
    }
    else
        (*place).push_back(street);
    
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
