#ifndef _GN_NUMVIEW_H_
#define _GN_NUMVIEW_H_

#include "GNStd.h"
#include "GNAnim.h"
#include "GNGeometory.h"
#include "GNFont.h"

struct gn_number_view {
	GNAnim* anim;
	GNPoint orig;
	GNFloat size;
	int		digit;
	char*	value;
	char	printfc[64];
};
typedef struct gn_number_view GNNumberView;

GNNumberView*	GNNumberViewCreateWithAnim(GNAnim* anim, GNPoint p, GNFloat size, int maxdigit);
void			GNNumberViewSetValue(GNNumberView* nv, long v);
void			GNNumberViewRelease(GNNumberView* nv);
void			GNNumberViewDraw(GNNumberView* nv);

#endif