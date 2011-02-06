#ifndef __GN_GEOMETORY_H_
#define __GN_GEOMETORY_H_

#include "GNStd.h"


typedef struct gn_point {
	GNFloat x;
	GNFloat y;
} GNPoint;

struct gn_size {
	GNFloat w;
	GNFloat h;
};

typedef struct gn_size GNSize;

struct gn_rect {
	GNPoint o;
	GNSize s;
};

typedef struct gn_rect GNRect; 

struct gn_polar {
	GNFloat l;
	GNFloat a;
};

typedef struct gn_polar GNPolar;

struct gn_rotation {
	GNFloat ax;
	GNFloat ay;
	GNFloat az;
};
typedef struct gn_rotation GNRotation;

GNPoint GNPointCreate(GNFloat x, GNFloat y);
GNSize GNSizeCreate(GNFloat w, GNFloat h);
GNRect GNRectCreate(GNFloat x, GNFloat y, GNFloat w, GNFloat h);

GNPoint GNConvertToOrigin(GNPoint center, GNSize size);
GNPoint GNConvertToOriginByRect(GNRect centerAndSize);
GNPoint GNCalcOriginByRect(GNRect size);

GNPolar GNPolarCreate(GNFloat len, GNFloat angle);
GNPolar GNPolarCreateByPoint(GNPoint p);
GNPoint GNPointCreateByPolar(GNPolar pl);

GNRotation GNRotationCreate(GNFloat ax, GNFloat ay, GNFloat az);

GNBool GNRectIsOverlap(GNRect ar, GNRect br);

const static GNPoint GNPointZero = {0, 0};
const static GNSize GNSizeZero = {0, 0};
const static GNRect GNRectZero = {{0, 0}, {0, 0}};
const static GNPolar GNPolarZero = {0, 0};
const static GNRotation GNRotationZero = {0, 0, 0};

#endif 

