#ifndef __GN_SHAPE_H
#define __GN_SHAPE_H

#include "GNStd.h"
#include "GNGeometory.h"

void GNShapeDrawFreak(GNBool fill, GNRect r, GNFloat* f4);

void GNShapeDrawBox(GNBool fill, GNRect r, GNFloat angle);
void GNShapeDrawBoxWithZ(GNBool fill, GNRect r, GNFloat angle, GNFloat zpos);
void GNShapeDrawBox3D(GNBool fill, GNRect r, GNRotation a, GNFloat zsize); 

void GNShapeDrawHex(GNBool fill, GNRect r, GNFloat angle);
void GNShapeDrawHex3D(GNBool fill, GNRect r, GNRotation a, GNFloat zsize);

void GNShapeDrawProgressBar(GNRect r, float progress, GLfloat* color4bar, GLfloat* color4back, GNFloat angle);
#endif 

