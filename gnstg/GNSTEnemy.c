#include "GNSTEnemy.h"

GNSTEnemy* GNSTEnemyCreateWithAnim(GNPoint defOrig, GNRect frame, GNAnim* anim, int  level, GNBool isboss)
{
	GNSTEnemy* en = calloc(sizeof(GNSTEnemy), 1);
	if (!en) return NULL;
	
	// Initialize enemy object
	GNSTCharaInitWithAnim(&en->chara, GNSizeZero, defOrig, frame, anim);
	en->anim = anim;
	en->motion = NULL;
	en->orig = defOrig;
	//en->maxlen = sqrtf(powf(frame.s.w, 2)*powf(frame.s.h, 2));
	
	// Fix level
	if (level < 0) {
		level = 0;
	}
	if (level > kEnemyMaxLevel) {
		level = kEnemyMaxLevel;
	}
	en->level = level;
	en->isboss = isboss;
	en->bossbulletindex = 0;
	if (isboss) {
		en->bulleter = GNAnimAdd(en->anim, GNSTEnemyBossLev[level].bulletsec, Yes, No);
		en->bossanimid = GNAnimAdd(en->anim, 2.0, Yes, No);
		en->bossbulletchangeranimid = GNAnimAdd(en->anim, 3.0, Yes, No);
	} else {
		en->bulleter = GNAnimAdd(en->anim, GNSTEnemyLev[level].bulletsec, Yes, No);
	}

	if (en->isboss) {
	 	GNSTCharaSetStyle(&en->chara, GNSTEnemyBossLev[level].chara);
	} else {
		GNSTCharaSetStyle(&en->chara, GNSTEnemyLev[level].chara);
	}

	GNSTCharaSetStatus(&en->chara, GNSTCharaStatusNormal);
	
	return en;
}


void		GNSTEnemySetMotion(GNSTEnemy* en, GNMotionType mt, GNBool outframe, GNFloat speed, GNPoint target)
{
	if (!en) return;
	en->curplayer = target;
	GNMotionRelease(en->motion);
	en->motion = GNMotionCreateWithAnim(en->anim, en->orig, target, No, mt, speed);
}


void		GNSTEnemyCalcMotion(GNSTEnemy* en)
{
	if (!en) return;
	
	// Check enemy in frame
	GNBool inframe = No;
	if (en->chara.frame.o.y+en->chara.frame.s.h > en->chara.curo.y) {
		inframe = Yes;
	}

	// Add bullet to enemy
	if (en->bulleter && inframe) {
		int bcf, btf;
		GNAnimGetFrame(en->anim, en->bulleter, &bcf, &btf);
		float bprog = bcf/(float)btf;
		GNPoint enpos = GNSTCharaGetCurrentPos((GNSTChara*)en);
		
				
		if (!en->isboss &&  enpos.y > en->curplayer.y &&
			bprog > GNSTEnemyLev[en->level].bulletamount && bcf % GNSTEnemyLev[en->level].bulletfreq == 0) {
			GNPoint plp[5];
			plp[0] = en->curplayer;
			plp[1] = GNPointCreate(en->curplayer.x - GNSTCharaInfo[GNSTCharaStylePlayer].size.w, en->curplayer.y);
			plp[2] = GNPointCreate(en->curplayer.x + GNSTCharaInfo[GNSTCharaStylePlayer].size.w, en->curplayer.y);			
				GNSTCharaAddBullet(&en->chara, GNSTEnemyLev[en->level].bullet, GNSTEnemyLev[en->level].count, Yes, plp);
		}
		if (en->isboss &&
			bprog > GNSTEnemyBossLev[en->level].bulletamount && bcf % GNSTEnemyBossLev[en->level].bulletfreq == 0) {	
			GNPoint plp[5];
			plp[0] = en->curplayer;
			plp[1] = GNPointCreate(xrandFloat(-1, 1), en->curplayer.y);
			plp[2] = GNPointCreate(xrandFloat(-1, 1), en->curplayer.y);
			GNSTCharaAddBullet(&en->chara, GNSTEnemyBossLev[en->level].bullet[en->bossbulletindex], GNSTEnemyBossLev[en->level].count, Yes, plp);
		}
	}
	
	if (en->isboss) {
		int bccf, bctf;
		GNAnimGetFrame(en->anim, en->bossbulletchangeranimid, &bccf, &bctf);
		if (bccf == bctf) {
			en->bossbulletindex = random()% GNSTEnemyBossLev[en->level].bullettypecount;
		}
	}
	
	// Boss motion add
	if (en->bossanimid) {
		int bacf, batf;
		GNAnimGetFrame(en->anim, en->bossanimid, &bacf, &batf);
		if (bacf == batf) {
			GNMotionRelease(en->motion);
			printf("boss motion add\n");
			en->motion = GNMotionCreateWithAnim(en->anim, en->chara.curo, GNPointCreate(xrandFloat(-1, 1), xrandFloat(-0.5, 1.3333)), Yes, GNMotionTypeLine, 4.0);
		}
	}

	if (!en->motion) return;
	if (en->chara.status == GNSTCharaStatusDead) return;
	
	// Check whether motion is over
	GNPoint targetp;
	GNFloat angle;
	if (GNMotionGetCurPos(en->motion, &targetp, &angle) == No) {
		GNMotionRelease(en->motion);
		en->motion = NULL; 
	} else {
		GNSTCharaSetAngle((GNSTChara*)en, angle);
		GNSTCharaSetPos((GNSTChara*)en, targetp);
	}
}

void		GNSTEnemyRelease(GNSTEnemy* en)
{
	if (!en) return;
	GNAnimRemove(en->anim, en->bossanimid);
	GNAnimRemove(en->anim, en->bossbulletchangeranimid);
	GNAnimRemove(en->anim, en->bulleter);
	GNMotionRelease(en->motion);
	GNSTCharaRelease(&en->chara);
	free(en);
}


