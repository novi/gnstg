#ifndef __GN_ANIMATION_H_
#define __GN_ANIMATION_H_

#include "GNStd.h"

#define GN_ANIM_STORE 100

#define GNAnimConvertToEaseInOut(prog) ((1.0-sinf(M_PI/2.0+(prog)*M_PI))/2.0)
#define GNAnimConvertToEaseInOut2(prog) ((prog) - sinf((prog)*2*M_PI) / (2*M_PI))

typedef int GNAnimID;

struct gnst_anim_one {
	//int		valid;
	int		id;
	GNBool removewd;
	GNBool repeat;
	uint curframe;
	uint maxframe;
};

typedef struct gnst_anim_one _GNAnimOne;

struct gn_anim {
	GNFloat framespeed;
	int animcount;
	int storesize;
	_GNAnimOne* store;
	int* storetable;
	int latestid;
};

typedef struct gn_anim GNAnim;


// Create animation object
GNAnim*			GNAnimCreateWithFPS(int fps);

// Add to animation to anim object
// Return: Animation ID created by anim object
// repeat: Repeats animation
// removeWhenDone: Remove animation when done. (But not recommend, remove your self)
GNAnimID		GNAnimAdd(GNAnim* anim, GNFloat sec, GNBool repeat, GNBool removeWhenDone);
void			GNAnimRelease(GNAnim* anim);

// Get current frame with Animation ID
// rcur: Current frame
// rmax: Total frame
void			GNAnimGetFrame(GNAnim* anim, GNAnimID id, int* rcur, int* rmax);

// Remove animation with Animation ID
void			GNAnimRemove(GNAnim* anim, GNAnimID id);


// Foward one animation frame.
// It will be perfromed by runloop.
void			GNAnimStepFrame(GNAnim* anim);


#endif 
