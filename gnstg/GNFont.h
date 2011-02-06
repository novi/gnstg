#ifndef _GN_FONT_H_
#define _GN_FONT_H_

#include "GNStd.h"
#include "GNGeometory.h"

float GNFontDrawCharAtPoint(GNPoint p, GNFloat size, char c);
void GNFontDrawAtPoint(GNPoint p, GNFloat size, GNFloat spacing, const char* str);

#endif