#include "GNGeometory.h"
#include <math.h>


GNPoint GNPointCreate(GNFloat x, GNFloat y)
{
	GNPoint p;
	p.x = x; p.y = y;
	return p;
}


GNSize GNSizeCreate(GNFloat w, GNFloat h)
{
	GNSize s;
	s.w = w; s.h = h;
	return s;
}


GNRect GNRectCreate(GNFloat x, GNFloat y, GNFloat w, GNFloat h)
{
	GNRect r;
	r.o = GNPointCreate(x, y);
	r.s = GNSizeCreate(w, h);
	return r;
}


GNPoint GNConvertToOrigin(GNPoint center, GNSize size)
{
	return GNPointCreate(center.x - size.w*0.5, center.y - size.h*0.5);
}


GNPoint GNConvertToOriginByRect(GNRect centerAndSize)
{
	return GNPointCreate(centerAndSize.o.x - centerAndSize.s.w*0.5, centerAndSize.o.y - centerAndSize.s.h*0.5);
}


GNPoint GNCalcOriginByRect(GNRect size)
{
	return GNPointCreate(-size.s.w*0.5, -size.s.h*0.5);
}


GNPolar GNPolarCreate(GNFloat len, GNFloat angle)
{
	GNPolar pl;
	pl.l = len; pl.a = angle;
	return pl;
}


GNPolar GNPolarCreateByPoint(GNPoint p)
{
	GNPolar pl;
	pl.l = sqrtf(powf(p.x, 2)+powf(p.y, 2));
	pl.a = atanf(p.y/p.x);
	return pl;
}


GNPoint GNPointCreateByPolar(GNPolar pl)
{
	GNPoint p;
	p.x = pl.l*cosf(pl.a);
	p.y = pl.l*sinf(pl.a);
	return p;
}


GNRotation GNRotationCreate(GNFloat ax, GNFloat ay, GNFloat az)
{
	GNRotation rr;
	rr.ax = ax; rr.ay = ay; rr.az = az;
	return rr;
}


GNBool GNRectIsOverlap(GNRect ar, GNRect br)
{
	float axMin, ayMin, axMax, ayMax;
	float bxMin, byMin, bxMax, byMax;
    
	axMin = ar.o.x;
    ayMin = ar.o.y;
    axMax = axMin + ar.s.w;
    ayMax = ayMin + ar.s.h;
    
	bxMin = br.o.x;
    byMin = br.o.y;
    bxMax = bxMin + br.s.w;
    byMax = byMin + br.s.h;
	
	if (byMax < ayMin) {
    } else if (ayMax < byMin) {
    } else if (axMax < bxMin) {
    } else if (bxMax < axMin) {
    } else {
        return Yes;
    }

	return No;
}

