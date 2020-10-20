//
//  support.h
//  Project4
//
//  Created by Mint MSH on 3/16/17.
//  Copyright © 2017 Mint MSH. All rights reserved.
//

#ifndef support_h
#define support_h

#include "provided.h"

bool operator==(GeoCoord &a, GeoCoord &b)   // overload comparison for geocoord
{
    return (a.latitude == b.latitude && a.longitude == b.longitude);
}

bool operator==(StreetSegment &a, StreetSegment &b)   // overload
{
    return (a.segment.start == b.segment.start && a.segment.end == b.segment.end);
}

#endif /* support_h */
