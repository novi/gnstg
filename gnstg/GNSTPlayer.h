#ifndef _GNST_PLAYER_H_

#define _GNST_PLAYER_H_

#include "GNSTChara.h"


struct gnst_player {
	GNSTChara chara;
	int bulletlevel;
};

typedef struct gnst_player GNSTPlayer;

struct player_lev {
	GNSTBulletType bullet;
	int		count;
};

const static struct player_lev GNSTPlayerLev[] = {
// Lv0
{GNSTBulletTypeNormal, 1},
{GNSTBulletTypeNormal, 3},
{GNSTBulletTypeNormal, 5},

{GNSTBulletTypeNormal2, 1},
{GNSTBulletTypeNormal2, 3},
//{GNSTBulletTypeNormal2, 5},

{GNSTBulletTypeTwin, 1},
{GNSTBulletTypeTwin, 3},
//{GNSTBulletTypeTwin, 5},

{GNSTBulletTypeHex1, 1},
//{GNSTBulletTypeHex1, 2},
{GNSTBulletTypeHex1, 3},
//{GNSTBulletTypeHex1, 4},
//{GNSTBulletTypeHex1, 5},

{GNSTBulletTypeHex2, 1},
{GNSTBulletTypeHex2, 3},

/*
{GNSTBulletTypeHex2, 2},
{GNSTBulletTypeHex2, 3},
{GNSTBulletTypeHex2, 4},
{GNSTBulletTypeHex2, 5},

{GNSTBulletTypeHex3, 1},
{GNSTBulletTypeHex4, 2},
{GNSTBulletTypeHex5, 3},
{GNSTBulletTypeHex6, 4},
{GNSTBulletTypeHex7, 5},
*/
{GNSTBulletTypeBeam1, 1},

{GNSTBulletTypeBeam2, 1},

//{GNSTBulletTypeBeam3, 1},

};

#define kPlayerMaxLevel (sizeof(GNSTPlayerLev)/sizeof(struct player_lev)-1)

GNSTPlayer* GNSTPlayerCreateWithAnim(GNSize size, GNPoint defOrig, GNRect frame, GNAnim* anim);
void		GNSTPlayerRelease(GNSTPlayer* pl);

void		GNSTPlayerFireBullet(GNSTPlayer* pl);

void		GNSTPlayerSetBulletLevel(GNSTPlayer* pl, int lev, GNBool delta);
#define		GNSTPlayerGetBulletLevel(pl) ((pl)->bulletlevel)

#endif 
