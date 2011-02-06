#ifndef __GNST_CHARACTER_SET_H_
#define __GNST_CHARACTER_SET_H_

#include "GNSTParam.h"

struct gnst_charainfo {
	GNSize size;
	GNPoint bulOffset[kCharaBulletMax];
	int maxlife;
	GNFloat deadanimsec;
	int bulAngle;
	GNFloat damageanimsec;
	GNFloat motionanimsec;
};

enum gnst_charastyle {
	GNSTCharaStyleUnknown = 0,
	GNSTCharaStylePlayer,
	GNSTCharaStyleEnemy1,
	GNSTCharaStyleEnemy2,
	GNSTCharaStyleEnemy3,
	GNSTCharaStyleEnemy4,
	GNSTCharaStyleEnemy5,
	GNSTCharaStyleBoss1,
};
typedef enum gnst_charastyle GNSTCharaStyle;

const static struct gnst_charainfo GNSTCharaInfo[] = {
/* Size */						/*BullOffset*/													                           
/* MaxLife */	/* Dead sec */		/* Bullet angle */	/* Damage anim sec */ /* motion anim sec */
{{0.1, 0.1},	{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
100,				1.1,				60,					1.0,	1.0},
// GNSTCharaStylePlayer
{{0.2, 0.2},	{{0.0, 0.1}, {0.0, 0.05}, {0.0, 0.05}, {0.0, 0.05}, {0.0, 0.05}},	
100,				3,				60,					0.2,	1.0},
// GNSTCharaStyleEnemy1
{{0.05, 0.05},	{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
2,					0.5,				60,					0.5,	1.0},
// GNSTCharaStyleEnemy2
{{0.1, 0.1},	{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
5,					1.0,				60,					0.5,	1.0},
// GNSTCharaStyleEnemy3
{{0.1, 0.1},	{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
10,					1.0,				60,					0.5,	2.0},
// GNSTCharaStyleEnemy4
{{0.15, 0.15},	{{0.0, 0.0}, {0.0, -0.2}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
20,					1.5,				60,					0.5,	3.0},
// GNSTCharaStyleEnemy5
{{0.18, 0.18},	{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
30,					1.5,				60,					0.5,	1.0},
// GNSTCharaStyleBoss1
{{0.5, 0.5},	{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},	
400,					1.5,				60,					0.2,	1.0},
};


struct gnst_bulinfo {
	GNSize size;
	GNFloat animsec;
	int maxlife;
	int colorpat;
	GNPoint target[kCharaBulletMax];
};

enum gnst_bullet_kind {
	GNSTBulletTypeNormal = 0,
	GNSTBulletTypeNormal2,
	GNSTBulletTypeTwin,
	GNSTBulletTypeHex1,
	GNSTBulletTypeHex2,
	GNSTBulletTypeBeam1,
	GNSTBulletTypeBeam2,
};

const static struct gnst_bulinfo GNSTBulletInfo[] = {
/* Size *//* Anim sec */ /* Max Life*/ /* Color pattern*/		/* Bullet target */
// GNSTBulletNormal
{{0.05, 0.05},		2.5,		1,		0,		{{0.0, 3}, {0.2, 3}, {-0.2, 3}, {0.4, 3}, {-0.4, 3}} },
// GNSTBulletNormal2{{-0.2, 2.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}},
{{0.07, 0.07},		1.5,		2,		0,		{{0.0, 3}, {0.3, 3}, {-0.3, 3}, {0.6, 3}, {-0.6, 3}} },
// GNSTBulletTypeTwin
{{0.07, 0.07},		3.0,		4,		0,		{{0.0, 3}, {0.3, 3}, {-0.3, 3}, {0.6, 3}, {-0.6, 3}} },
// GNSTBulletTypeHex1
{{0.03, 0.1},		4,			6,		0,		{{0.0, 3}, {0.4, 3}, {-0.4, 3}, {0.8, 3}, {-0.8, 3}} },
// GNSTBulletTypeHex2
{{0.03, 0.1},		4,			8,		0,		{{0.0, 3}, {0.4, 3}, {-0.4, 3}, {0.8, 3}, {-0.8, 3}} },
// GNSTBulletTypeBeam1
{{0.03, 1.5},		3,			3,		0,		{{0.0, 2.0}, {0.4, 3}, {-0.4, 3}, {0.8, 3}, {-0.8, 3}} },
// GNSTBulletTypeBeam2
{{0.05, 2.0},		4,			5,		0,		{{0.0, 2.5}, {0.4, 3}, {-0.4, 3}, {0.8, 3}, {-0.8, 3}} },
};

typedef enum gnst_bullet_kind GNSTBulletType;

enum gnst_charastatus {
	GNSTCharaStatusUnknown = 0,
	GNSTCharaStatusNormal,
	GNSTCharaStatusDead,
	GNSTCharaStatusDamaged,
};
typedef enum gnst_charastatus GNSTCharaStatus;


#endif