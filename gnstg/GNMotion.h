#ifndef _GN_MOTION_H_
#define _GN_MOTION_H_

#include "GNStd.h"

#include "GNAnim.h"
#include "GNGeometory.h"

enum gn_motion_type {
	GNMotionTypeStable = 0,
	GNMotionTypeLine,
	GNMotionTypeZig, //no imp
	GNMotionTypeCycle,
	GNMotionTypeSine,
};
typedef enum gn_motion_type GNMotionType;

struct gn_motion {
	GNAnim*		anim;
	GNAnimID	motionanimid;
	GNMotionType type;
	GNPoint		orig;
	GNPoint		targetpos;
	GNPoint		movedelta;
	int			appedframe;
	float		speed;
	GNBool		overrun;
	float		angle;
	GNPoint		oldpos;
};
typedef struct gn_motion GNMotion;

// Create motion with anim.
//
// Return		: Created motion object
// anim			: Valid anim object
// origpoint	: Start of the point
// target		: End of the point
// overrun		: When motion is over, continue motion
// type			: Motion type
// speed		: Motion speed
//
GNMotion*	GNMotionCreateWithAnim(GNAnim* anim, GNPoint origpoint, GNPoint target, GNBool overrun, GNMotionType type, GNFloat speed);

// Get current point for the motion.
//
// Return: No = motion is over
//
GNBool		GNMotionGetCurPos(GNMotion* m, GNPoint* curpos, GNFloat* angle);

// Release the motion
//
// NOTE : Anim object is not released.
//
void		GNMotionRelease(GNMotion* m);

#endif