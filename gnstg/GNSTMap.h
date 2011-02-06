

#ifndef __GNST_MAP_H_
#define __GNST_MAP_H_

#include "GNSTPlayer.h"
#include "GNSTEnemy.h"
#include "GNSTInfoView.h"

struct gnst_script {
	int enemylevel; 
	GNMotionType enemymotion;
	float		speed;
	float	spawntimer;
	int			enemymax;
	GNBool		isboss;
};
typedef struct gnst_script GNSTScript;

struct gnst_map_s {
	GNRect		frame;
	GNRect		enemyframe;
	GNAnim*		anim; // create global anim // owner
	GNSTPlayer* player; // owner
	GNSTEnemy*	enem[kMapMaxEnemies];// owner
	GNAnimID	spawnner;
	GNSTScript  cscript;
	int			enemykilled;
	int			playerkilled;
	long		totalp;
	GNSTInfoView* infov;
	int			bosscount;
	float		playerlevup;
	long		highscorep;
};

typedef struct gnst_map_s GNSTMap;


GNSTMap* GNSTMapCreate(GNRect frame);
void	GNSTMapSetInfoView(GNSTMap* m, const GNSTInfoView* iv);

#define GNSTMapGetPlayerChara(m) ((GNSTChara*)&(m)->player->chara)

void	GNSTMapSetScript(GNSTMap* m, const GNSTScript* s);
void	GNSTMapSetHighScore(GNSTMap* m, long v);

#define GNSTMapGetCountEnemyKilled(m) ((m)->enemykilled)
#define GNSTMapGetCountPlayerKilled(m) ((m)->playerkilled)
#define GNSTMapGetHighScore(m)			((m)->highscorep)

void	GNSTMapStepFrame(GNSTMap* m);
void	GNSTMapDraw(GNSTMap* m);
void	GNSTMapIdle(GNSTMap* m);

void	GNSTMapRelease(GNSTMap* m);





#endif