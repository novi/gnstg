#ifndef __GNST_ENEMY_H_
#define __GNST_ENEMY_H_

#include "GNSTChara.h"
#include "GNMotion.h"


struct gnst_enemy {
	GNSTChara chara;
	GNPoint		orig;
	GNAnim*		anim;
	GNMotion*	motion;
	GNAnimID	bulleter; // bullet add anim
	GNPoint		curplayer;
	float		maxlen;
	int			level;
	GNBool		isboss;
	GNAnimID	bossanimid;
	int			bossbulletindex;
	GNAnimID	bossbulletchangeranimid;
};

typedef struct gnst_enemy GNSTEnemy;

struct enemy_lev {
	GNSTCharaStyle chara;
	GNSTBulletType bullet;
	int		count;
	float		bulletamount;
	int		bulletfreq;
	float	bulletsec;
};

//if (bprog > bulletamount && bcf % .bulletfreq == 0)
//
const static struct enemy_lev GNSTEnemyLev[] = {
// lv0
{GNSTCharaStyleEnemy1, GNSTBulletTypeNormal, 1, 0.8, 5, 2.0},
{GNSTCharaStyleEnemy1, GNSTBulletTypeNormal, 3, 0.8, 1,1.0},
// 2
{GNSTCharaStyleEnemy2, GNSTBulletTypeNormal2, 1, 0.8, 5, 3.0},
{GNSTCharaStyleEnemy2, GNSTBulletTypeNormal2, 3 ,0.5 ,7, 1.0},
// 4
{GNSTCharaStyleEnemy3, GNSTBulletTypeNormal2, 1, 0.8, 8, 1.0},
{GNSTCharaStyleEnemy3, GNSTBulletTypeNormal2, 3, 0.8, 7, 2.0},
// 6
{GNSTCharaStyleEnemy4, GNSTBulletTypeTwin	, 1, 0.7, 4, 1.0},
{GNSTCharaStyleEnemy4, GNSTBulletTypeHex1	, 3, 0.6, 4, 3.0},
// 8
{GNSTCharaStyleEnemy5, GNSTBulletTypeHex1	, 1, 0.5, 4, 4.0},
{GNSTCharaStyleEnemy5, GNSTBulletTypeHex2	, 3, 0.5, 4, 4.0},

};

struct enemyboss_lev {
	GNSTCharaStyle chara;
	int		bullettypecount;
	const GNSTBulletType* bullet;
	int		count;
	int		bulletamount;
	int		bulletfreq;
	float	bulletsec;
};

const static GNSTBulletType bullettypeb1[] = {GNSTBulletTypeHex2, GNSTBulletTypeHex1, GNSTBulletTypeTwin, GNSTBulletTypeNormal2};

const static struct enemyboss_lev GNSTEnemyBossLev[] = {
// lv0
{GNSTCharaStyleBoss1, 4, bullettypeb1, 3, 0.3, 3,5.0},
{GNSTCharaStyleBoss1, 2, bullettypeb1, 3, 3, 1,1.0},
};

#define kEnemyMaxLevel (sizeof(GNSTEnemyLev)/sizeof(struct enemy_lev)-1)

GNSTEnemy* GNSTEnemyCreateWithAnim(GNPoint defOrig, GNRect frame, GNAnim* anim, int  level, GNBool isboss);
void		GNSTEnemyRelease(GNSTEnemy* en);

// Move enemy
void		GNSTEnemyCalcMotion(GNSTEnemy* en);
void		GNSTEnemySetMotion(GNSTEnemy* en, GNMotionType mt, GNBool outframe, GNFloat speed, GNPoint target);

#endif 
