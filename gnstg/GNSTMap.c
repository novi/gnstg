#include "GNSTMap.h"

void _GNSTCharaBulletRemove(GNSTChara* c, _GNSTBulletOne* blt);
void _GNSTMapCalcCol(GNSTMap* m);

GNSTMap* GNSTMapCreate(GNRect frame)
{
	
	GNSTMap* m = calloc(1, sizeof(GNSTMap));
	if (!m) return NULL;
	//(-1,-kMaxHeight,2,kMaxHeight*2)
	m->frame = frame;
	m->enemyframe.o.x = frame.o.x - 0.1;
	m->enemyframe.o.y = frame.o.y - 0.1;
	m->enemyframe.s.w = frame.s.w + 0.2;
	m->enemyframe.s.h = frame.s.h + 0.2;
	
	m->anim = GNAnimCreateWithFPS(kFPS);
	if (!m->anim) {
		free(m);
		return NULL;
	}
	
	m->player = GNSTPlayerCreateWithAnim(GNSTCharaInfo[GNSTCharaStylePlayer].size, GNPointCreate(0.0, -0.5), frame, m->anim);
	if (!m->player) {
		GNAnimRelease(m->anim);
		free(m);
		return NULL;
	}
	m->spawnner = 0;// = GNAnimAdd(m->anim, 1.0, Yes, No);
	m->playerkilled = 0;
	m->infov = NULL;
	m->totalp = 0;
	m->bosscount = 0;
	m->playerlevup = 0;
	m->highscorep = 0;
	
	return m;
}

void	GNSTMapSetScript(GNSTMap* m, const GNSTScript* s)
{
	if (!m) return;
	memcpy(&m->cscript, s, sizeof(GNSTScript));
	GNAnimRemove(m->anim, m->spawnner);
	m->spawnner = GNAnimAdd(m->anim, m->cscript.spawntimer, Yes, No);
	m->enemykilled = 0;
	m->bosscount = 0;
	
	if (m->cscript.isboss) {
		int i;
		for (i = 0; i < kMapMaxEnemies; i++) {
			GNSTEnemyRelease(m->enem[i]);
			m->enem[i] = NULL;
		}
	}
}

void	GNSTMapSetInfoView(GNSTMap* m, const GNSTInfoView* iv)
{
	if (!m) return;
	m->infov = (GNSTInfoView*)iv;
	GNSTInfoViewSetHighScorePoint(m->infov, m->highscorep);
}

void	GNSTMapSetHighScore(GNSTMap* m, long v)
{
	m->highscorep = v;
	GNSTInfoViewSetHighScorePoint(m->infov, m->highscorep);
}

void	GNSTMapStepFrame(GNSTMap* m)
{
	if (!m) return;
	
#pragma mark Process enemies
	int i;
	for (i = 0; i < kMapMaxEnemies; i++) {
		if (!m->enem[i]) continue;
		
		GNSTEnemy* en = m->enem[i];
		GNPoint enep = GNSTCharaGetCurrentPos((GNSTChara*)en);
		
		// Check enemy killed by player
		if (GNSTCharaAlive((GNSTChara*)en) == No) {
			m->enemykilled++;
			m->totalp += GNSTCharaGetInfo((GNSTChara*)en).maxlife;
			m->playerlevup += GNSTCharaGetInfo((GNSTChara*)en).maxlife*kMapPlayerLevUpBias;
//			printf("enemy killed %d times\n", m->enemykilled);
		}
		
		if (!m->cscript.isboss) {
			// Kill enemy out of map
			if (enep.y <= m->frame.o.y) {
				printf("kill enemy by system\n");
				en->chara.alive = No;
			} else if ((enep.x <= m->frame.o.x || enep.x >= m->frame.o.x+m->frame.s.w) &&
					   enep.y <= m->frame.o.y+m->frame.s.h*0.5) {
				printf("kill enemy in lare by system\n");
				en->chara.alive = No;
			}
		}
		
		// Send motion
		GNSTEnemyCalcMotion(en);
		
		if (GNSTCharaAlive((GNSTChara*)en) == No) {
			GNSTEnemyRelease(en);
			//#ifdef DEBUG
			//printf("ENEMY REMOVED %d\n",i);
			//#endif
			m->enem[i] = NULL;
		}
	}
#pragma mark Process Player
	// Clean up player
	// Player killed
	if (GNSTCharaAlive((GNSTChara*)m->player) == No) {
		m->playerkilled++;
		if (m->playerkilled > kMapPlayerDeadAllow) {
			m->playerkilled = 0;
			m->totalp = 0;
		}
		int currentbulletlevel = GNSTPlayerGetBulletLevel(m->player);
		printf("player REMOVED, killed %d times\n", m->playerkilled);
		GNSTInfoViewShowMoreInfo(m->infov);
		GNSTPlayerRelease(m->player);
		m->player = GNSTPlayerCreateWithAnim(GNSTCharaInfo[GNSTCharaStylePlayer].size, GNPointCreate(xrandFloat(-1.0, 1.0), -0.5), m->frame, m->anim);
		GNSTPlayerSetBulletLevel(m->player, currentbulletlevel-kMapDecreasePlayerLevAfterDead, No);
	}
	
	
	// Animation
	GNAnimStepFrame(m->anim);
	
	// Calc collision
	_GNSTMapCalcCol(m);
	
#pragma mark Spawn enemies
	int scf, stf;
	GNAnimGetFrame(m->anim, m->spawnner, &scf, &stf);
	if (scf == stf) {
		for (i = 0; i < m->cscript.enemymax; i++) {
			if (m->enem[i] == NULL) {
#ifdef DEBUG
				printf("enemy create %d %d %d\n", i, scf, stf);
#endif
				GNPoint newpos;
				if (m->cscript.isboss) {
					// Create boss
					newpos = GNPointCreate(xrandFloat(-1.2, 1.2), kMaxHeight+GNSTCharaInfo[GNSTEnemyBossLev[m->cscript.enemylevel].chara].size.h);
					m->bosscount++;
				} else {
					newpos = GNPointCreate(xrandFloat(-1.2, 1.2), kMaxHeight+GNSTCharaInfo[GNSTEnemyLev[m->cscript.enemylevel].chara].size.h);
				}
				m->enem[i] = GNSTEnemyCreateWithAnim(newpos, m->enemyframe, m->anim,m->cscript.enemylevel, m->cscript.isboss);
				if (!m->cscript.isboss) {
					GNSTEnemySetMotion(m->enem[i], m->cscript.enemymotion, Yes, m->cscript.speed, GNSTCharaGetCurrentPos((GNSTChara*)m->player));
				}
				break;
			}
		}
		
		// Spawn a boss while enemymax
		if (m->cscript.isboss && m->cscript.enemymax <= m->bosscount) {
			GNAnimRemove(m->anim, m->spawnner);
			m->spawnner = 0;
		}
	}
	
#pragma mark Update information view
	if (m->infov) {
		// Update information view
		GNSTInfoViewSetTotalPoint(m->infov, m->totalp);
		if (m->totalp > m->highscorep) {
			m->highscorep = m->totalp;
			GNSTInfoViewSetHighScorePoint(m->infov, m->highscorep);
		}
		GNSTInfoViewSetCountPlayerDead(m->infov, m->playerkilled);
		GNSTInfoViewSetCountEnemyKilled(m->infov, m->enemykilled);
		GNSTInfoViewSetPlayerLife(m->infov, GNSTCharaGetLife((GNSTChara*)m->player), GNSTCharaInfo[GNSTCharaStylePlayer].maxlife);
		
		// Player level up process
		if (m->playerlevup >= 1.0) {
			m->playerlevup = 0;
			GNSTPlayerSetBulletLevel(m->player, 1, Yes);
		}
		GNSTInfoViewSetPlayerLevUpProgress(m->infov, m->playerlevup);
		
		// Set boss life
		if (m->cscript.isboss) {
			// calc boss life
			int maxlife = 0;
			int curlife = 0;
			for (i = 0; i < m->cscript.enemymax; i++) {
				if (!m->enem[i]) continue;
				curlife += GNSTCharaGetLife((GNSTChara*)m->enem[i]);
				maxlife += GNSTCharaGetInfo((GNSTChara*)m->enem[i]).maxlife;
			}
			GNSTInfoViewSetBossLife(m->infov, curlife, maxlife);
			if (curlife <= 0 && maxlife != 0) {
				m->enemykilled = 99999;
			}
		} else {
			GNSTInfoViewSetBossLife(m->infov, 0, 0);
		}

	}
}


void	GNSTMapDraw(GNSTMap* m)
{
	if (!m) return;
	// Draw enemies
	int i;
	for (i = 0; i < kMapMaxEnemies; i++) {
		if (!m->enem[i]) continue;
		// Check enemy alive
		//if (GNSTCharaAlive((GNSTChara*)m->enem[i]) == No) continue;
		
		GNSTCharaDraw((GNSTChara*)m->enem[i]);
	}
	
	// Draw player
	GNSTCharaDraw((GNSTChara*)m->player);
}


void	GNSTMapIdle(GNSTMap* m)

{
	
}


void	GNSTMapRelease(GNSTMap* m)
{
	if (!m) return;
	GNAnimRemove(m->anim, m->spawnner);
	GNSTPlayerRelease(m->player);
	GNAnimRelease(m->anim);
	int i;
	for (i = 0; i < kMapMaxEnemies; i++) {
		GNSTEnemyRelease(m->enem[i]);
	}
	free(m);
}


void _GNSTMapCalcCol(GNSTMap* m)
{
	
	int bi;
	
	int i;
	GNRect bulletr;
	
	GNSTChara* pc = (GNSTChara*)m->player;
	GNRect	prect = GNSTCharaGetCharaFrame(pc);
	GNSTChara* ec;
	
	for (bi = 0; bi < kCharaBulletMaxPerChar+kCharaBulletMax; bi++) {
		if(pc->blts[bi].valid == 0) continue;
		// Remove bullet if out of frame
		if (pc->blts[bi].curo.y > m->frame.o.y+m->frame.s.h) {
			_GNSTCharaBulletRemove(pc, &pc->blts[bi]);
			continue;
		}

		
		bulletr = pc->blts[bi].area;
		for (i = 0; i < kMapMaxEnemies; i++) {
			if (!m->enem[i]) continue;
			ec = (GNSTChara*)m->enem[i];
			if (GNSTCharaGetLife(ec) <= 0) {
				continue;
			}
			if (GNRectIsOverlap(GNSTCharaGetCharaFrame(ec), bulletr) == Yes) {
				// Hit!
				m->totalp ++;
#ifdef DEBUG2
				printf("hit enemy %d\n", i);
#endif
				// Remove bullet
				GNSTBulletType bultstyle = pc->blts[bi].kind;
				if (!(bultstyle >= GNSTBulletTypeBeam1 && bultstyle <= GNSTBulletTypeBeam2)) {
					_GNSTCharaBulletRemove(pc, &pc->blts[bi]);
				}
				GNSTCharaSetLife(ec, -1*(GNSTBulletInfo[bultstyle].maxlife), Yes);
				GNSTCharaSetStatus(ec, GNSTCharaStatusDamaged);
			}
		}
	}
	
	// Collision detect enemy bullet with player
	for (i = 0; i < kMapMaxEnemies; i++) {
		if (!m->enem[i]) continue;
		ec = (GNSTChara*)m->enem[i];
		if (GNSTCharaGetLife(ec) <= 0) {
			continue;
		}
		
		for (bi = 0; bi < kCharaBulletMaxPerChar+kCharaBulletMax; bi++) {
			if(ec->blts[bi].valid == 0 || ec->status == GNSTCharaStatusDead) continue;
			bulletr = ec->blts[bi].area;
			
			//printf("blt %d\n", bi);
			if (GNRectIsOverlap(bulletr, prect) == Yes) {
				// Remove bullet
				_GNSTCharaBulletRemove(ec, &ec->blts[bi]);
				
				GNSTBulletType bultstyle = ec->blts[bi].kind;
				GNSTCharaSetLife(pc, -1*(GNSTBulletInfo[bultstyle].maxlife), Yes);
				GNSTCharaSetStatus(pc, GNSTCharaStatusDamaged);
				
				//printf("life;%d\n", pc->life);
			}
		}
	}
	
	if (GNSTCharaGetLife(pc) > 0) {
		// Collision detect player with enemy
		for (i = 0; i < kMapMaxEnemies; i++) {
			if (!m->enem[i]) continue;
			ec = (GNSTChara*)m->enem[i];
			if (GNRectIsOverlap(GNSTCharaGetCharaFrame(ec), prect) == Yes) {
			//	printf("COL PLAYER AND ENEMY\n");
				
				GNSTCharaSetLife(ec, -1*(GNSTCharaInfo[pc->style].maxlife)*0.1, Yes);
				GNSTCharaSetStatus(ec, GNSTCharaStatusDamaged);
				GNSTCharaSetLife(pc, -1*(GNSTCharaInfo[ec->style].maxlife)*0.1, Yes);
				GNSTCharaSetStatus(pc, GNSTCharaStatusDamaged);
			}
		}
	}
}
