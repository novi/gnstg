#ifndef _GNST_BACKG_H_
#define _GNST_BACKG_H_

#include "GNStd.h"
#include "GNGeometory.h"
#include "GNAnim.h"


enum gnst_backg_style {
	GNSTBackgStyleNone = 0,
	GNSTBackgStyleNormal,
	GNSTBackgStyleDark1,
	GNSTBackgStyleDark2,
	GNSTBackgStyleDark3,
	GNSTBackgStyleBlack1,
	GNSTBackgStyleBlack2,
	GNSTBackgStyleBlack3,
};

enum gnst_backg_motion {
	GNSTBackgMotionStable = 0,
	GNSTBackgMotionMoveDown, // not imp
	GNSTBackgMotionMoveDownRight, // not imp
	GNSTBackgMotionMoveDownRightFaster,
};

typedef enum gnst_backg_style GNSTBackgStyle;
typedef enum gnst_backg_motion GNSTBackgMotion;

struct gnst_backg {
	GNRect			frame;
	GNAnim*			anim;
	GNSTBackgStyle style;
	GNSTBackgMotion motion;
	GNAnimID		animid[5];
};

typedef struct gnst_backg GNSTBackg;

GNSTBackg*		GNSTBackgCreate(GNRect frame);
void			GNSTBackgRelease(GNSTBackg* bg);

void			GNSTBackgSetStyle(GNSTBackg* bg, GNSTBackgStyle style);
void			GNSTBackgSetMotion(GNSTBackg* bg, GNSTBackgMotion motion);

void			GNSTBackgStemFrame(GNSTBackg* bg);
void			GNSTBackgDraw(GNSTBackg* bg);


#endif


