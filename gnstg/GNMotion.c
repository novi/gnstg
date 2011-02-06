/*
 *  GNMotion.c
 *  gnstg
 *
 *  Created by ito on 2009/02/12.
 *  Copyright 2009 Ito. All rights reserved.
 *
 */

#include "GNMotion.h"


GNMotion*	GNMotionCreateWithAnim(GNAnim* anim, GNPoint origpoint, GNPoint target, GNBool overrun, GNMotionType type, GNFloat speed)
{
	if (!anim) return NULL;
	
	// Create object
	GNMotion* m = calloc(sizeof(GNMotion), 1);
	if (!m) return NULL;
	
	// Set initial value
	m->type = type;
	m->oldpos = origpoint;
	m->orig = origpoint;
	m->anim = anim;
	m->speed = speed;
		m->targetpos = target;
	m->appedframe = 0;
	m->overrun = overrun;
	
	GNBool repeat = No;
	if (type == GNMotionTypeCycle) {
		repeat = Yes;
	}
	
	m->motionanimid = GNAnimAdd(m->anim, speed, repeat, No);
	if (!m->motionanimid) {
		GNMotionRelease(m);
		return NULL;
	}
	
	int cf, tf;
	GNAnimGetFrame(m->anim, m->motionanimid, &cf, &tf);
	m->movedelta.x =  (m->targetpos.x - m->orig.x)/(float)tf;
	m->movedelta.y =  (m->targetpos.y - m->orig.y)/(float)tf;
	m->angle = atan2f(m->movedelta.y, m->movedelta.x);
	
	return m;
}

GNBool		GNMotionGetCurPos(GNMotion* m, GNPoint* curpos, GNFloat* angle)
{
	if (!m) return No;
	// Motion is over
	if (!m->motionanimid) return No;
	
	int cf, tf;
	GNAnimGetFrame(m->anim, m->motionanimid, &cf, &tf);
	// Motion is over
	if (cf == tf) {
		
		GNAnimRemove(m->anim, m->motionanimid);
		if (m->overrun) {
			m->motionanimid = 0;
			return No;
		} else {
			// Create motion anim again
			m->motionanimid = GNAnimAdd(m->anim, m->speed, No, No);
			int cf, tf;
			GNAnimGetFrame(m->anim, m->motionanimid, &cf, &tf);
			m->appedframe += tf;
			return Yes;
		}
	}
	
	float progress = (float)cf/(float)tf;
	
	
	curpos->x = m->orig.x;
	curpos->y = m->orig.y;	
	if (m->type == GNMotionTypeLine) {
		curpos->x = m->orig.x + m->movedelta.x*(cf+m->appedframe);
		curpos->y = m->orig.y + m->movedelta.y*(cf+m->appedframe);
		*angle = m->angle;
	}
	else if (m->type == GNMotionTypeSine) {
		
		curpos->x = m->orig.x + m->movedelta.x*(cf+m->appedframe)*sinf(progress*M_PI);
		curpos->y = m->orig.y + m->movedelta.y*(cf+m->appedframe);
		*angle = atan2f(curpos->x - m->oldpos.x, curpos->y - m->oldpos.y)+M_PI/2.0;
	}
	else if (m->type == GNMotionTypeCycle) {
		curpos->x = m->orig.x + m->movedelta.x*cosf(progress*2*M_PI);
		curpos->y = m->orig.y +  m->movedelta.x*sinf(progress*2*M_PI);
		
	}
	
	m->oldpos = *curpos;
	
	
		return Yes;
}

void		GNMotionRelease(GNMotion* m)
{
	if (!m) return;
	// Remove anim to motion
	GNAnimRemove(m->anim, m->motionanimid);
	free(m);
}
