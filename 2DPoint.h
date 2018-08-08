// 2Dpoint.h defines all operations for a 2D point

#ifndef __2DPOINT_H__
#define __2DPOINT_H__

// 2D point
class TwoDPoint
{
public:
	double x;
	double y;

public:
	TwoDPoint() { x=0.0f; y=0.0f; }
	TwoDPoint( double xx, double yy)	{ x = xx; y = yy;}

};

#endif
