#ifndef _GNST_INFOVIEW_H_
#define _GNST_INFOVIEW_H_


#include "GNNumberView.h"
#include "GNShape.h"

#define kGNSTInfoViewMoreInfoAnimSec 5.0
#define kGNSTInfoViewMoreInfoAnimMove 0.1

struct gnst_infoview {
	GNRect			frame;
	GNAnim*			anim; // not own
	GNNumberView*	totalp;
	GNNumberView*	killed;
	GNNumberView*	playerdead;
	GNNumberView*	curstage;
	int				playerlifecur;
	int				playerlifemax;
	int				bosslifecur;
	int				bosslifemax;
	float			playerlevelup;
	GNAnimID		stagemotionanimid;
	GNNumberView*	highscore;
};

typedef struct gnst_infoview GNSTInfoView;



GNSTInfoView*	GNSTInfoViewCreateWithAnim(GNAnim* anim, GNRect frame);
void			GNSTInfoViewDraw(GNSTInfoView* iv);
void			GNSTInfoViewRelease(GNSTInfoView* iv);

// Setter
void			GNSTInfoViewSetTotalPoint(GNSTInfoView* iv, long p);
void			GNSTInfoViewSetCountPlayerDead(GNSTInfoView* iv, int v);
void			GNSTInfoViewSetCountEnemyKilled(GNSTInfoView* iv, int v);
void			GNSTInfoViewSetStageNum(GNSTInfoView* iv, int v);
void			GNSTInfoViewSetPlayerLife(GNSTInfoView* iv, int cur, int max);
void			GNSTInfoViewSetBossLife(GNSTInfoView* iv, int cur, int max);
void			GNSTInfoViewSetPlayerLevUpProgress(GNSTInfoView* iv, float progress);
void			GNSTInfoViewSetHighScorePoint(GNSTInfoView* iv, long p);

// Show label
void			GNSTInfoViewShowMoreInfo(GNSTInfoView* iv);


#endif