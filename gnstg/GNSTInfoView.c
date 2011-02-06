/*
 *  GNSTInfoView.c
 *  gnstg
 *
 *  Created by ito on 2009/02/22.
 *  Copyright 2009 Ito. All rights reserved.
 *
 */

#include "GNSTInfoView.h"

GNSTInfoView*	GNSTInfoViewCreateWithAnim(GNAnim* anim, GNRect frame)
{
	GNSTInfoView* iv = calloc(1, sizeof(GNSTInfoView));
	if (!iv) {
		return NULL;
	}
	iv->anim = anim;
	iv->frame = frame;
	
	iv->highscore = GNNumberViewCreateWithAnim(iv->anim, GNPointZero, 0.05, 10);
	iv->totalp = GNNumberViewCreateWithAnim(iv->anim, GNPointCreate(-0.85, 1.3), 0.08, 10);
	iv->killed = GNNumberViewCreateWithAnim(iv->anim, GNPointZero, 0.05, 5);
	iv->curstage = GNNumberViewCreateWithAnim(iv->anim, GNPointCreate(0.6, 1.2), 0.2, 2);
	iv->playerdead = GNNumberViewCreateWithAnim(iv->anim, GNPointZero, 0.05, 3);
	
	return iv;
}

void			GNSTInfoViewDraw(GNSTInfoView* iv)
{
	if (!iv) return;
	
	glColor3f(0.918, 0.957, 0.988);
	
	GNPoint pt = GNPointCreate(0.15, 1.3);
	GNPoint pdead = GNPointCreate(-0.9, -1.4);
	GNPoint ptimes = GNPointCreate(-0.45, -1.4);
	GNPoint pkill = GNPointCreate(0.65, -1.4);
	
	GNPoint npkill = GNPointCreate(0.6, -1.4);
	GNPoint npdead = GNPointCreate(-0.85, -1.4);
	
	GNPoint nhigh = GNPointCreate(-0.85, 1.2);
	GNPoint phigh = GNPointCreate(-0.85, 1.2);
	// Perform stage motion
	if (iv->stagemotionanimid) {
		int cf, tf;
		GNAnimGetFrame(iv->anim, iv->stagemotionanimid, &cf, &tf);
		float prog = cf/(float)tf;
		
		if (cf == tf) {
			GNAnimRemove(iv->anim, iv->stagemotionanimid);
			iv->stagemotionanimid = 0;
		} else {
			float prog1 = 1;
			if (prog <= kGNSTInfoViewMoreInfoAnimMove) {
				prog1 = GNAnimConvertToEaseInOut2(prog/kGNSTInfoViewMoreInfoAnimMove);				
			}else if (prog >= 1-kGNSTInfoViewMoreInfoAnimMove) {
				prog1 = GNAnimConvertToEaseInOut2((1-prog)/kGNSTInfoViewMoreInfoAnimMove);	
			}
			
			pt.y =  0.5 * (1-prog1) + pt.y;
			pdead.y =  -0.4 * (1-prog1) + pdead.y;
			ptimes.y =  -0.4 * (1-prog1) + ptimes.y;
			pkill.y =  -0.4 * (1-prog1) + pkill.y;
			
			npkill.x =   npkill.x - 0.3 * (prog1);
			npdead.x =   npdead.x + 0.2 * (prog1);
			
			nhigh.x =   nhigh.x + 0.35 * (prog1);
			phigh.x =   phigh.x - 0.6 * (1-prog1);
			
			GNFontDrawAtPoint(pt, 0.1, 0.02, "STAGE");
			GNFontDrawAtPoint(pdead, 0.05, 0.02, "DEAD");
			GNFontDrawAtPoint(ptimes, 0.05, 0.02, "TIMES");
			GNFontDrawAtPoint(pkill, 0.05, 0.02, "KILLED");
			GNFontDrawAtPoint(phigh, 0.05, 0.015, "HIGHSCR");
		}
	}
	
	iv->killed->orig = npkill;
	iv->playerdead->orig = npdead;
	iv->highscore->orig = nhigh;
	
	GNNumberViewDraw(iv->killed);
	GNNumberViewDraw(iv->totalp);
	GNNumberViewDraw(iv->curstage);
	GNNumberViewDraw(iv->playerdead);
	GNNumberViewDraw(iv->highscore);
	
	static GLfloat playerbarcolor[] = {0.753, 0.635, 0.780, 0.7};
	static GLfloat playerbarbackcolor[] = {0.180, 0.161, 0.188, 0.5};
	GNShapeDrawProgressBar(GNRectCreate(-0.9, -1.0, 1.5, 0.025), iv->playerlifecur/(float)iv->playerlifemax,
						   playerbarcolor, playerbarbackcolor, 90);
	
	static GLfloat playerlevbarcolor[] = {0.745, 0.827, 0.792, 0.7};
	static GLfloat playerlevbarbackcolor[] = {0.180, 0.161, 0.188, 0.5};
	GNShapeDrawProgressBar(GNRectCreate(-0.8, -1.0, 1.5, 0.025), iv->playerlevelup,
						   playerlevbarcolor, playerlevbarbackcolor, 90);
	
	if (iv->bosslifemax) {
		static GLfloat playerbarcolor[] = {0.6, 0.6, 0.6, 0.7};
		static GLfloat playerbarbackcolor[] = {0.180, 0.161, 0.188, 0.5};
		GNShapeDrawProgressBar(GNRectCreate(-0.8, 1.1, 1.5, 0.025), iv->bosslifecur/(float)iv->bosslifemax,
							   playerbarcolor, playerbarbackcolor, 0);
	}
}

void			GNSTInfoViewSetTotalPoint(GNSTInfoView* iv, long p)
{
	if (!iv) return;
	GNNumberViewSetValue(iv->totalp, p);
}
void			GNSTInfoViewSetCountPlayerDead(GNSTInfoView* iv, int v)
{
	if (!iv) return;
	GNNumberViewSetValue(iv->playerdead, v);
}
void			GNSTInfoViewSetCountEnemyKilled(GNSTInfoView* iv, int v)
{
	if (!iv) return;
	GNNumberViewSetValue(iv->killed, v);
}
																
void			GNSTInfoViewSetStageNum(GNSTInfoView* iv, int v)
{
	if (!iv) return;
	GNSTInfoViewShowMoreInfo(iv);
	GNNumberViewSetValue(iv->curstage, v);
}

void			GNSTInfoViewShowMoreInfo(GNSTInfoView* iv)
{
	if (!iv) return;
	// Remove old anim
	GNAnimRemove(iv->anim, iv->stagemotionanimid);
	iv->stagemotionanimid = GNAnimAdd(iv->anim, kGNSTInfoViewMoreInfoAnimSec, No, No);
}

void			GNSTInfoViewSetHighScorePoint(GNSTInfoView* iv, long p)
{
	if (!iv) return;
	GNNumberViewSetValue(iv->highscore, p);
}

void			GNSTInfoViewSetPlayerLevUpProgress(GNSTInfoView* iv, float progress)
{
	if (!iv) return;
	iv->playerlevelup = progress;
}

void			GNSTInfoViewSetPlayerLife(GNSTInfoView* iv, int cur, int max)
{
	if (!iv) return;
	iv->playerlifemax = max; iv->playerlifecur = cur;
}

void			GNSTInfoViewSetBossLife(GNSTInfoView* iv, int cur, int max)
{
	if (!iv) return;
	iv->bosslifecur = cur; iv->bosslifemax = max;
}

void			GNSTInfoViewRelease(GNSTInfoView* iv)
{
	if (!iv) return;
	GNNumberViewRelease(iv->highscore);
	GNNumberViewRelease(iv->killed);
	GNNumberViewRelease(iv->totalp);
	GNNumberViewRelease(iv->curstage);
	GNNumberViewRelease(iv->playerdead);
	GNAnimRemove(iv->anim, iv->stagemotionanimid);
	free(iv);
}
