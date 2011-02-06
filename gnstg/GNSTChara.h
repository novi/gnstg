#ifndef __GNST_CHARACTER_H_
#define __GNST_CHARACTER_H_


#include "GNStd.h"
#include "GNGeometory.h"
#include "GNAnim.h"
#include "GNShape.h"
#include "GNSTCharaParam.h"
#include "GNSTParam.h"

struct gnst_bullet {
	int			valid;
	GNPoint		curo;
	GNPoint		orig;
	GNPoint		target;
	GNRect		area;
	GNSTBulletType kind;
	GNAnimID	animid;
	long		randbase;
};
typedef struct gnst_bullet _GNSTBulletOne;


struct gnst_chara {
	GNPoint			curo; // Current pos
	GNSize			size; // Chara size
	GNRect			frame; // available frame
	GNAnim*			ani; // Global anim
	GNFloat			angle;
	_GNSTBulletOne blts[kCharaBulletMaxPerChar]; // bullet store
	_GNSTBulletOne beams[kCharaBulletMax];
	int				bulletcount;
	GNSTCharaStyle style;
	GNSTCharaStatus status;
	GNBool			alive;
	GNAnimID		sanimid; // status anim id
	int				life; // Current life
	GNAnimID		canimid; // chara anim id
};
typedef struct gnst_chara GNSTChara;

// Initialize Character object
// c : Allocated memory block
// frame : Available frame
// ani : Global animation object
int			GNSTCharaInitWithAnim(GNSTChara* c, GNSize size, GNPoint defOrig, GNRect frame, GNAnim* ani);

// Release Character object
void		GNSTCharaRelease(GNSTChara* c);


GNRect		GNSTCharaGetCharaFrame(GNSTChara* c);

// Set character property
void		GNSTCharaSetPos(GNSTChara* c, GNPoint pos);
void		GNSTCharaSetStyle(GNSTChara* c, GNSTCharaStyle s);
void		GNSTCharaSetStatus(GNSTChara* c, GNSTCharaStatus st);
void		GNSTCharaSetLife(GNSTChara* c, int life, GNBool delta);
void		GNSTCharaSetAngle(GNSTChara* c, GNFloat angle);

// Perform bullet
void		GNSTCharaAddBullet(GNSTChara* c, GNSTBulletType bul, int count, GNBool targeted, GNPoint* target);
void		GNSTCharaRemoveBulletBeam(GNSTChara* c);

void 		GNSTCharaDraw(GNSTChara* c);

#define GNSTCharaAlive(c) ((c)->alive)
#define GNSTCharaGetLife(c) ((c)->life)
#define GNSTCharaGetCurrentPos(c) ((c)->curo)
#define GNSTCharaGetInfo(c) (GNSTCharaInfo[(c)->style])

#endif
