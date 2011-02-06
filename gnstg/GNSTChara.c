#include "GNSTChara.h"

void _GNSTCharaBulletDraw(GNAnim* anim, _GNSTBulletOne* blt);
void _GNSTCharaBulletRemove(GNSTChara* c, _GNSTBulletOne* blt);
void _GNSTCharaBulletBeamDraw(GNSTChara* c, _GNSTBulletOne* blt);
void _GNSTCharaDraw(GNSTChara* c);

int		GNSTCharaInitWithAnim(GNSTChara* c, GNSize size, GNPoint defOrig, GNRect frame, GNAnim* ani)
{
	//GNSTChara* c = calloc(sizeof(GNSTChara), 1);
	memset(c, 0, sizeof(GNSTChara));
	if (!c) return GNInitFailure;
	
	if (!ani) {
		c->ani = GNAnimCreateWithFPS(kFPS);
		if (!c->ani) {
			//			free(c);
			return GNInitFailure;
		}
	} else {
		c->ani = ani;
	}
	
	c->size = size;
	c->curo = defOrig;
	c->frame = frame;
	c->alive = Yes;
	c->life = 10;
	c->sanimid = 0;
	c->status = GNSTCharaStatusNormal;
	c->style = GNSTCharaStyleUnknown;
	c->canimid  = 0;
	//sc->borntime = time(NULL);
	c->bulletcount = 0;
	c->angle = 0;
	
	// Clear bullet store
	int i;
	for (i = 0; i < kCharaBulletMaxPerChar; i++) {
		c->blts[i].valid = 0;
	}
	for (i = 0; i < kCharaBulletMax; i++) {
		c->beams[i].valid = 0;
	}
	return 0;
}

void		GNSTCharaRemoveBulletBeam(GNSTChara* c)
{
	if (!c) return;
	int i;
	for (i = 0; i < kCharaBulletMax; i++) {
		if (c->beams[i].valid) {
			GNAnimRemove(c->ani, c->beams[i].animid);
			c->beams[i].valid = 0;
		}
	}
}

void		GNSTCharaAddBullet(GNSTChara* c, GNSTBulletType bul, int count, GNBool targeted, GNPoint* target)
{
	if (!c) return;
	int i;
	int bulcnt = 0;
	
	// Fix count
	if (count > kCharaBulletMax) {
		count = kCharaBulletMax;
	}
	
	// Beam 
	if ((bul >= GNSTBulletTypeBeam1 && bul <= GNSTBulletTypeBeam2)) {
		
		if (c->beams[0].valid) {
			return;
		}
		
		for (i = 0; i < count; i++) {
			c->beams[i].curo = GNPointZero;
			c->beams[i].orig = c->beams[i].curo;
			c->beams[i].kind = bul;
			c->beams[i].valid = Yes;
			c->beams[i].randbase = random();
			if (targeted) {
				float angle = atan2f(target[0].y - c->curo.y, target[0].x - c->curo.x);
				c-> beams[i].target.x = angle;
				c-> beams[i].target.y = angle;
			} else {
				c-> beams[i].target.x = GNSTBulletInfo[bul].target[i].x; // Offset
				c-> beams[i].target.y = GNSTBulletInfo[bul].target[i].y; // Offset
			}
			c-> beams[i].animid = GNAnimAdd(c->ani, GNSTBulletInfo[bul].animsec, Yes, No);
			//printf("created beam %f,%f %f,%f\n", c->curo.x, c->curo.y, c->beams[i].target.x, c->beams[i].target.y);
		}
		
		return;
	}
	
	//Not beam
	for(i = 0; i < kCharaBulletMaxPerChar; i++) {
		if (c->blts[i].valid == 0) {
			
			if (bulcnt >= count) {
				break;
			}
			
			// Create bullet one
			c->blts[i].curo = GNPointCreate(c->curo.x+GNSTCharaInfo[c->style].bulOffset[bulcnt].x, c->curo.y+GNSTCharaInfo[c->style].bulOffset[bulcnt].y);
			c->blts[i].orig = c->blts[i].curo;
			c->blts[i].kind = bul;
			c->blts[i].valid = Yes;
			c->blts[i].area = GNRectCreate(100, 100, 100, 100);
			//GNPointCreate(c->blts[bltidx].curo.x + GNSTBulletInfo[bul].target[0].x, c->blts[bltidx].curo.y + GNSTBulletInfo[bul].target[0].y);
			if (targeted) {
				float angle = atan2f(target[bulcnt].y - c->curo.y, target[bulcnt].x - c->curo.x);
				c->blts[i].target.x = (c->frame.s.w) * cosf(angle);
				c->blts[i].target.y = (c->frame.s.w) * sinf(angle);
				//c->blts[i].target.x = target.x - c->curo.x;
				//c->blts[i].target.y = target.y - c->curo.y;
			} else {
				c->blts[i].target = GNSTBulletInfo[bul].target[bulcnt];
			}
			
			float speedbase = xrandFloat(-GNSTBulletInfo[bul].animsec*0.04, GNSTBulletInfo[bul].animsec*0.04);
			c->blts[i].animid = GNAnimAdd(c->ani, GNSTBulletInfo[bul].animsec+speedbase, No, Yes);
			//printf("created bullet %f,%f %f,%f\n", c->curo.x, c->curo.y, c-> blts[i].target.x, c-> blts[i].target.y);
			bulcnt++;
		}
	}
}	



/*
 GNPoint 	GNSTCharaGetCurrentPos(GNSTChara* c)
 {
 return c->curo;
 }
 */


void		GNSTCharaSetAngle(GNSTChara* c, GNFloat angle)
{
	c->angle = angle+M_PI/2.0;
}

void		GNSTCharaSetPos(GNSTChara* c, GNPoint pos)
{
	if (!c) return;
	GNPoint newo;
	// Create max frame pos
	GNPoint maxpos = GNPointCreate(c->frame.o.x+c->frame.s.w, c->frame.o.y+c->frame.s.h);
	
	// If out of character frame
	if (pos.x < c->frame.o.x ) {
		newo.x = c->frame.o.x;
	} else if (pos.x > maxpos.x) {
		newo.x = maxpos.x;
	} else {
		newo.x = pos.x;
	}
	
	if (pos.y < c->frame.o.y ) {
		newo.y = c->frame.o.y;
	} else if (pos.y > maxpos.y) {
		newo.y = maxpos.y;
	} else {
		newo.y = pos.y;
	}
	
	// Set as current pos
	c->curo = newo;
}

void _GNSTCharaBulletRemove(GNSTChara* c, _GNSTBulletOne* blt)
{
	blt->valid = 0;
	GNAnimRemove(c->ani, blt->animid);
	blt->animid = 0;
	c->bulletcount--;
}


void		GNSTCharaDraw(GNSTChara* ch)
{
	if (!ch) return;
	int i;
	
	if (ch->alive == No) return;
	
	
	int dcf, dtf;
	// Dead anim
	if (ch->status == GNSTCharaStatusDead) {
		GNAnimGetFrame(ch->ani, ch->sanimid, &dcf, &dtf);
		//	printf("is dead ? %d %d\n", dcf, dtf);
		if (dcf == dtf) {
#ifdef DEBUG
			printf("character NO more ALIVE\n");
#endif
			ch->alive = No;
			GNAnimRemove(ch->ani, ch->sanimid);
			ch->sanimid = 0;
			return;
		}
	} else if (ch->status == GNSTCharaStatusDamaged && ch->sanimid) {
		GNAnimGetFrame(ch->ani, ch->sanimid, &dcf, &dtf);	
		// Damage anim is over
		// Remove anim and set status normal
		if (dcf == dtf) { 
			//	printf("REMOVE damage status \n");
			ch->status = GNSTCharaStatusNormal;
			GNAnimRemove(ch->ani, ch->sanimid);
			ch->sanimid = 0;
		}
	}
	
	// Draw beams
	for (i = 0; i < kCharaBulletMax; i++) {
		if (ch->beams[i].valid) {
			_GNSTCharaBulletBeamDraw(ch, &(ch->beams[i]));
		}
	}
	
	// Draw bullet
	for (i = 0; i < kCharaBulletMaxPerChar; i++) {
		if (ch->blts[i].valid) {
			int cf, tf;
			GNAnimGetFrame(ch->ani, ch->blts[i].animid, &cf, &tf);
			
			// Not valid anim, Remove this bullet
			if(tf == cf) {
				_GNSTCharaBulletRemove(ch, &(ch->blts[i]));
				continue;
			}
		//	printf("drawblt");
			//if (!(ch->blts[i].kind >= GNSTBulletTypeBeam1 && ch->blts[i].kind <= GNSTBulletTypeBeam3)) {
			_GNSTCharaBulletDraw(ch->ani, &(ch->blts[i]));
			//}
		}
	}
	
	
	
	// Draw main obj
	_GNSTCharaDraw(ch);
}


void		GNSTCharaSetLife(GNSTChara* c, int life, GNBool delta)
{
	if (!c) return;
	if ((int)c->life <= 0) return;
	
	if (delta) {
		c->life += life;
	} else {
		c->life = life;
	}
	if ((int)c->life <= 0) {
		c->life = 0;
	}
	
	//printf("life %d -> %d\n", life, c->life);
	
	if ((int)c->life <= 0) {
#ifdef DEBUG
		printf("----------chara dead----------\n");
#endif
		GNSTCharaRemoveBulletBeam(c);
		GNSTCharaSetStatus(c, GNSTCharaStatusDead);
	}
	
}


GNRect		GNSTCharaGetCharaFrame(GNSTChara* c)
{
	if (!c) return GNRectZero;
	GNRect r;
	r.o = GNPointCreate(c->curo.x - c->size.w*0.5, c->curo.y - c->size.h*0.5);
	r.s = c->size;
	return r;
}


void		GNSTCharaSetStyle(GNSTChara* c, GNSTCharaStyle s)
{
	if (!c) return;
	// Remove current anim
	GNAnimRemove(c->ani, c->canimid);
	
	c->style = s;
	c->size = GNSTCharaInfo[c->style].size;
	
	
	// Create new anim for the style
	c->canimid = GNAnimAdd(c->ani, GNSTCharaInfo[c->style].motionanimsec, Yes, No);
	GNSTCharaSetLife(c, GNSTCharaInfo[s].maxlife, No);
}

void		GNSTCharaSetStatus(GNSTChara* c, GNSTCharaStatus st)
{
	if (!c) return;
	
	// Already status is dead
	if (c->status == GNSTCharaStatusDead) return;
	
	c->status = st;
	
	// Remove current anim
	if (c->sanimid) {
		GNAnimRemove(c->ani, c->sanimid);
	}
	
	// Create anim for status
	if (c->status == GNSTCharaStatusDead) {
#ifdef DEBUG
		printf("dead anim set\n");
#endif
		c->sanimid = GNAnimAdd(c->ani, GNSTCharaInfo[c->style].deadanimsec, No, No);
	} else if (c->status == GNSTCharaStatusDamaged) {
		c->sanimid = GNAnimAdd(c->ani, GNSTCharaInfo[c->style].damageanimsec, No, No);
	}
}



void		GNSTCharaRelease(GNSTChara* c)
{
	if (!c) return;
	
	GNAnimRemove(c->ani, c->sanimid);
	GNAnimRemove(c->ani, c->canimid);
	
	//printf("bullet remain %d\n", c->bulletcount);
	// Remove all of bullets
	int i;
	for(i = 0; i < kCharaBulletMaxPerChar; i++) {
		if (c->blts[i].valid) {
			GNAnimRemove(c->ani, c->blts[i].animid);
		}
	}
	// Remove all of beams 
	for(i = 0; i < kCharaBulletMax; i++) {
		if (c->beams[i].valid) {
			GNAnimRemove(c->ani, c->beams[i].animid);
		}
	}
	
	//free(c);
}
