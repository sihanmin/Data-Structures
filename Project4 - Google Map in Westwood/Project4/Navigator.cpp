#include "provided.h"
#include <string>
#include <vector>
#include <queue>
#include "MyMap.h"
#include "support.h"
using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;

private:
    struct Node
    {
        Node() {};
        Node(int dad, double H, double len, GeoCoord geo, string name)
        {
            myDad = dad;
            myH = H;
            myLen = len;
            myTotal = len + H;
            myGeo = geo;
            myName = name;
        }
        double myTotal;
        GeoCoord myGeo;
        double myLen;
        double myH;
        string myName;
        int myDad;  // index of the last point in the close vector
                    // once a node is pushed in, it would not change position
        
        bool operator<(const Node &b) const
        {
            return myTotal > b.myTotal;    // overload to enable the use of priority queue
                // create a min heep
        }
    };
    
    MapLoader m_mapLoader;
    AttractionMapper m_attractions;
    SegmentMapper m_segments;
    
    void findPath(GeoCoord &start, GeoCoord &end, priority_queue<Node>* open, vector<Node> *close, int &last) const;
    void organizeDirections(vector<Node> *close, int cur, vector<NavSegment> &directions) const;
    void clear(priority_queue<Node>* open, vector<Node> *close) const;
    
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    if (!m_mapLoader.load(mapFile))
        return false;
    
    m_attractions.init(m_mapLoader);
    m_segments.init(m_mapLoader);
    
    return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    GeoCoord startGeo;
    GeoCoord endGeo;
    if (!m_attractions.getGeoCoord(start, startGeo))
        return NAV_BAD_SOURCE;
    if (!m_attractions.getGeoCoord(end, endGeo))
        return NAV_BAD_DESTINATION;
        
    while (directions.size() != 0)
        directions.pop_back();  // empty the vector
    
    priority_queue<Node>* open = new priority_queue<Node>;
    vector<Node>* close = new vector<Node>;
    int last = 0;   // the remeber the last node in the route
    
    
    
    findPath(startGeo, endGeo, open, close, last);
    
    if (last == -2)
        return NAV_NO_ROUTE;
    
    organizeDirections(close, last, directions);
    
    clear(open, close);
	return NAV_SUCCESS;  // This compiles, but may not be correct
}



void NavigatorImpl::findPath(GeoCoord &start, GeoCoord &end, priority_queue<Node>* open, vector<Node> *close, int &last) const
{
    GeoCoord startGeo = start;
    GeoCoord endGeo = end;
    vector<StreetSegment> startStreets = m_segments.getSegments(start);
    vector<StreetSegment> endStreets = m_segments.getSegments(end);
    
    Node first(-1, distanceEarthMiles(startGeo, endGeo), 0, startGeo, startStreets[0].streetName);
    MyMap<string, int> book;    // mark the state // value == 1 -> already visited
    book.associate(first.myGeo.latitudeText+','+first.myGeo.longitudeText, 1);
    
    open->push(first);
    Node cur;
    
    while (!open->empty())
    {
        cur = open->top();
        if (cur.myGeo == endGeo)    // stop when reach the end
        {
            last = close->size();
            close->push_back(cur);
            return;
        }
        close->push_back(cur);
        vector<StreetSegment> curAss = m_segments.getSegments(cur.myGeo);
        for (int i = 0; i < curAss.size(); i++) // add current unvisited associated coordinates into the open queue
        {
            int mark = 0;
            for (int j = 0; j < endStreets.size(); j++)
            {
                if (curAss[i] == endStreets[j]) // find if the destination in the next step
                {
                    Node son(close->size()-1, 0, cur.myLen + distanceEarthMiles(cur.myGeo, end), end, curAss[i].streetName);
                    open->push(son);
                    mark = 1;
                    break;
                }
            }
            if (mark == 1)
                break;
            
            if (!(curAss[i].segment.start == cur.myGeo))  // for end or attraction, next stop would be the start in this segment
            {
                if (book.find(curAss[i].segment.start.latitudeText+','+curAss[i].segment.start.longitudeText) == nullptr)
                {
                    Node son(close->size()-1, distanceEarthMiles(curAss[i].segment.start, end), cur.myLen + distanceEarthMiles(cur.myGeo, curAss[i].segment.start), curAss[i].segment.start, curAss[i].streetName);
                    open->push(son);
                    book.associate(curAss[i].segment.start.latitudeText+','+curAss[i].segment.start.longitudeText, 1);
                }
            }
            if (!(curAss[i].segment.end == cur.myGeo))    // for start or attraction, next stop would be the end in this segment
            {
                if (book.find(curAss[i].segment.end.latitudeText+','+curAss[i].segment.end.longitudeText) == nullptr)
                {
                    Node son(close->size()-1, distanceEarthMiles(curAss[i].segment.end, end), cur.myLen + distanceEarthMiles(cur.myGeo, curAss[i].segment.end), curAss[i].segment.end, curAss[i].streetName);
                    open->push(son);
                    book.associate(curAss[i].segment.end.latitudeText+','+curAss[i].segment.end.longitudeText, 1);
                }
            }
        }
        open->pop();
    }
    
    last = -2;
}

void NavigatorImpl::organizeDirections(vector<Node> *close, int cur, vector<NavSegment> &directions) const
{
    int curDad = (*close)[cur].myDad;
    if (curDad == -1)
    {
        return;
    }
    
    organizeDirections(close, curDad, directions);
    
    GeoSegment	geoSegment((*close)[curDad].myGeo, (*close)[cur].myGeo);
    double		distance = distanceEarthMiles((*close)[curDad].myGeo, (*close)[cur].myGeo);
    double angle  = angleOfLine(geoSegment);
    string	direction;
    if (angle >= 0 && angle <= 22.5)
        direction = "east";
    else if (angle > 22.5 && angle <= 67.5)
        direction = "northeast";
    else if (angle > 67.5 && angle <= 112.5)
        direction = "north";
    else if (angle > 112.5 && angle <= 157.5)
        direction = "northwest";
    else if (angle > 157.5 && angle <= 202.5)
        direction = "west";
    else if (angle > 202.5 && angle <= 247.5)
        direction = "southwest";
    else if (angle > 247.5 && angle <= 292.5)
        direction = "south";
    else if (angle > 292.5 && angle <= 337.5)
        direction = "southeast";
    else if (angle > 337.5 && angle < 360)
        direction = "southeast";

    NavSegment curNav(direction, (*close)[cur].myName, distance, geoSegment);
    
    if ((*close)[curDad].myName != (*close)[cur].myName)
    {
        string directionTurn;
        double angleTurn = angleBetween2Lines(directions[directions.size()-1].m_geoSegment, geoSegment);
        if (angleTurn >= 0 && angleTurn < 180)
            directionTurn = "left";
        else if (angleTurn >= 180 && angleTurn < 360)
            directionTurn = "right";
            
        NavSegment turnNow(directionTurn, (*close)[cur].myName);
        directions.push_back(turnNow);
    }
   
    directions.push_back(curNav);
}

void NavigatorImpl::clear(priority_queue<Node>* open, vector<Node> *close) const
{
    delete open;
    delete close;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
