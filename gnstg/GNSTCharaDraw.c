#include "GNSTChara.h"


void _GNSTCharaDraw(GNSTChara* c)
{
	GNSTChara* ch = c;
	GNPoint orig = GNPointCreate(ch->curo.x - ch->size.w*0.5, ch->curo.y - ch->size.h*0.5);
	GNSize s = ch->size;
	
	glLineWidth(1.0);
	
	float progress = 0;
	int ccf = -1;
	int ctf = 0;
	if (c->canimid) {
		GNAnimGetFrame(c->ani, c->canimid, &ccf, &ctf);
		progress = ccf/(float)ctf;
	}
	
	int scf = -1;
	int stf = 0;
	float sprogress = 0;
	if (c->sanimid) {
		GNAnimGetFrame(ch->ani, ch->sanimid, &scf, &stf);
		sprogress = (scf)/(float)stf;
	}
	
	
	if(ch->style == GNSTCharaStyleUnknown) {
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(orig.x, orig.y);
		glVertex2f(orig.x+s.w*0.5, orig.y+ s.h);
		glVertex2f(orig.x+s.w, orig.y);
		glEnd();
	}
	else if (ch->style == GNSTCharaStylePlayer) {
		if (scf % 20 >= 4) {
			//	return;
		}
		if (ch->status == GNSTCharaStatusDead) {
			glColor4f(0.902, 0.0, 0.2, 0.3);
			if (sprogress <= 0.2) {
				GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, (sprogress/0.2)*0.5, (sprogress/0.2)*0.5);
				GNFloat sa = (sprogress/0.2)*(1+rand()%180)+rand()%180;
				GNShapeDrawBox(Yes, sr, sa);
				sa = (sprogress/0.2)*(1+rand()%180)+rand()%180;
				glColor4f(0.902, 0.0, 0.2, 1.0);
				GNShapeDrawBox(No, sr, sa);
			} 
			
			if (sprogress > 0.2 && sprogress < 0.8) {
				GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, 0.5, 0.5);
				GNFloat sa = (sprogress/0.2)*(1+rand()%180)+rand()%180;
				GNShapeDrawBox(Yes, sr, sa);
				sa = (sprogress/0.2)*(1+rand()%180)+rand()%180;
				glColor4f(0.902, 0.0, 0.2, 1.0);
				GNShapeDrawBox(No, sr, sa);
				
			}
			if (sprogress >= 0.8) {
				GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, (1-(sprogress/0.8))*0.5, (1-(sprogress/0.8))*0.5);
				GNFloat sa = (sprogress/0.2)*(1+rand()%180)+rand()%180;
				GNShapeDrawBox(Yes, sr, sa);
				sa = (sprogress/0.2)*(1+rand()%180)+rand()%180;
				glColor4f(0.902, 0.0, 0.2, 1.0);
				GNShapeDrawBox(No, sr, sa);
				
			}
			
		}
		if (ch->status == GNSTCharaStatusDamaged) {
			glColor4f(0.953, 0.953, 0.949, 1.0);
		}
		
		
		
		if (ch->status == GNSTCharaStatusNormal) {
			glColor4f(1.000, 0.851, 0.0, 1.0);
		}
		GNShapeDrawBox3D(No, GNRectCreate(ch->curo.x, ch->curo.y,s.w*0.1, s.w*0.9),
						 GNRotationCreate(0, 0, 0), s.w*0.1);
		if (ch->status == GNSTCharaStatusNormal) {
			glColor4f(0.925, 0.427, 0.443, 0.8);
			GNShapeDrawHex3D(Yes, GNRectCreate(ch->curo.x, ch->curo.y, s.w*0.4, s.h*0.4),
							 GNRotationCreate(360*progress+60, 360*progress, 360*progress+30), s.w*0.1);
		}		
		if (ch->status == GNSTCharaStatusNormal) {
			glColor4f(0.0, 0.333, 0.180, 0.8);
		}
		glBegin(GL_LINE_LOOP);
		glVertex2f(orig.x, orig.y);
		glVertex2f(orig.x+s.w*0.3, orig.y);
		glVertex2f(orig.x+s.w*0.3, orig.y+s.h*0.75);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(orig.x+s.w*0.7, orig.y);
		glVertex2f(orig.x+s.w, orig.y);
		glVertex2f(orig.x+s.w*0.7, orig.y+s.h*0.75);
		glEnd();
		
		
		
		
		if (ch->status == GNSTCharaStatusNormal) {
			glColor4f(0.667, 0.812, 0.325, 1.0);
		}
		glBegin(GL_LINE_LOOP);
		glVertex2f(orig.x, orig.y);
		glVertex2f(orig.x+s.w*0.3, orig.y);
		glVertex2f(orig.x+s.w*0.3, orig.y+s.h*0.75);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(orig.x+s.w*0.7, orig.y);
		glVertex2f(orig.x+s.w, orig.y);
		glVertex2f(orig.x+s.w*0.7, orig.y+s.h*0.75);
		glEnd();
		
		if (ch->status == GNSTCharaStatusNormal) {
			glColor4f(0.667, 0.812, 0.325, 0.8);
			GNRect r = GNSTCharaGetCharaFrame(ch);
			GNPoint o = GNCalcOriginByRect(r);
			
			glPushMatrix();
			glTranslatef(r.o.x+r.s.w*0.5, r.o.y+r.s.h*0.5, -0.1);
			glRotatef(360*progress, 0.0, 1.0, 0);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(o.x, o.y);
			glVertex2f(o.x+s.w*0.3, o.y);
			glVertex2f(o.x+s.w*0.3, o.y+s.h*0.75);
			glVertex2f(o.x, o.y);
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(o.x+s.w*0.7, o.y);
			glVertex2f(o.x+s.w, o.y);
			glVertex2f(o.x+s.w*0.7, o.y+s.h*0.75);
			glVertex2f(o.x+s.w*0.7, o.y);
			glEnd();
		}
		
		
		glPopMatrix();
		
		
		
		
	}
	
	else if (ch->style == GNSTCharaStyleEnemy1) {
		if (ch->status == GNSTCharaStatusDead) {
			glColor4f(0.902, 0.0, 0.2, 0.3);
			GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, sprogress*0.2, sprogress*0.2);
			GNFloat sa = sprogress*(1+rand()%180)+rand()%180;
			GNShapeDrawBox(Yes, sr, sa);
			glColor4f(0.902, 0.0, 0.2, 1.0);
			GNShapeDrawBox(No, sr, sa);
			GNShapeDrawBox3D(No, GNRectCreate(ch->curo.x, ch->curo.y, s.w*(2-sprogress), s.h *(2-sprogress)),
							 GNRotationCreate(360*sprogress+60, 360*sprogress, 360*sprogress+30),  s.w*(2-sprogress));			
		} else if (ch->status == GNSTCharaStatusDamaged) {
			if (scf % 3 == 0) {
				glColor4f(1.000, 0.851, 0.0, 1.0);
			} else {
				glColor3f(0.929, 0.894, 0.804);
			}
		} else {
			glColor3f(0.929, 0.894, 0.804);
			
		}
		GNShapeDrawBox3D(No, GNRectCreate(ch->curo.x, ch->curo.y, s.w, s.h),
						 GNRotationCreate(360*progress+60, 360*progress, 360*progress+30), s.w);		
	}
	
	else if (ch->style == GNSTCharaStyleEnemy2) {
		if (ch->status == GNSTCharaStatusDead) {
			glColor4f(0.902, 0.0, 0.2, 0.3);
			GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, sprogress*c->size.w*2, sprogress*c->size.w*2);
			GNFloat sa = sprogress*(1+rand()%180)+rand()%180;
			GNShapeDrawBox(Yes, sr, sa);
			glColor4f(0.902, 0.0, 0.2, 1.0);
			GNShapeDrawBox(No, sr, sa);			
		} else if (ch->status == GNSTCharaStatusDamaged) {
			if (scf % 3 == 0) {
				glColor4f(1.000, 0.851, 0.0, 1.0);
			} else {
				glColor3f(0.929, 0.894, 0.804);
			}
		} else {
			glColor3f(0.929, 0.894, 0.804);
			
		}
		GNShapeDrawHex(No, GNRectCreate(c->curo.x, c->curo.y, c->size.w, c->size.h), 360*progress);
		
	}
	
	else if (ch->style == GNSTCharaStyleEnemy3) {
		if (ch->status == GNSTCharaStatusDead) {
			glColor4f(0.902, 0.0, 0.2, 0.3);
			GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, sprogress*c->size.w*2, sprogress*c->size.w*2);
			GNFloat sa = sprogress*(1+rand()%180)+rand()%180;
			GNShapeDrawBox(Yes, sr, sa);
			glColor4f(0.902, 0.0, 0.2, 1.0);
			GNShapeDrawBox(No, sr, sa);			
		} else if (ch->status == GNSTCharaStatusDamaged) {
			if (scf % 3 == 0) {
				glColor4f(1.000, 0.851, 0.0, 1.0);
			} else {
				glColor3f(0.929, 0.894, 0.804);
			}
		} else {
			// Normal color
			glColor3f(0.788, 0.459, 0.525);
		}
		glPushMatrix();
		s.h *= 0.5;
		s.w *= 0.5;
		glTranslatef(c->curo.x, c->curo.y, 0);
		glRotatef(c->angle*180/M_PI, 0.0, 0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 0);
		glVertex2f(-s.w, s.h);
		glVertex2f(s.w, s.h);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(s.w*0.2, 0);
		glVertex2f(s.w, s.h*0.8);
		glVertex2f(s.w, -s.h*0.8);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(-s.w*0.2, 0);
		glVertex2f(-s.w, s.h*0.8);
		glVertex2f(-s.w,-s.h*0.8);
		glEnd();
		glPopMatrix();
		if (c->status == GNSTCharaStatusNormal) {
			glColor3f(0.945, 0.749, 0.600);
		}
		GNShapeDrawBox(Yes, GNRectCreate(c->curo.x, c->curo.y, c->size.w*0.5, c->size.h*0.5), 360*progress);
		
	}
	
	else if (ch->style == GNSTCharaStyleEnemy4) {
		if (ch->status == GNSTCharaStatusDead) {
			glColor4f(0.902, 0.0, 0.2, 0.3);
			GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, sprogress*c->size.w*2, sprogress*c->size.w*2);
			GNFloat sa = sprogress*(1+rand()%180)+rand()%180;
			GNShapeDrawBox(Yes, sr, sa);
			glColor4f(0.902, 0.0, 0.2, 1.0);
			GNShapeDrawBox(No, sr, sa);			
		} else if (ch->status == GNSTCharaStatusDamaged) {
			if (scf % 3 == 0) {
				glColor4f(1.000, 0.851, 0.0, 1.0);
			} else {
				glColor3f(0.929, 0.894, 0.804);
			}
		} else {
			// Normal color
			glColor3f(0.788, 0.459, 0.525);
		}
		GNFloat angle = c->angle*180/M_PI;
		GNRect rc;
		glPushMatrix();
		glTranslatef(c->curo.x, c->curo.y, 0);
		glRotatef(angle, 0.0, 0, 1.0);
		int i;
		for (i = 0; i < 6; i++) {
			rc = GNRectCreate(0+c->size.w*0.5*cosf(progress*2*M_PI+M_PI/3.0*i), 0, c->size.w*0.1, c->size.h*0.9);
			GNShapeDrawBoxWithZ(No, rc, 0, -c->size.h*0.5+c->size.h*sinf(progress*2*M_PI+M_PI/3.0*i));
		}
		
		if (c->status == GNSTCharaStatusNormal) {
			glColor3f(0.945, 0.749, 0.600);
		}
		rc = GNRectCreate(0, 0, c->size.w*0.3, c->size.h*0.7);
		GNShapeDrawBox(Yes, rc, 0);
		glPopMatrix();
	}
	
	else if (ch->style == GNSTCharaStyleEnemy5) {
		if (ch->status == GNSTCharaStatusDead) {
			glColor4f(0.902, 0.0, 0.2, 0.3);
			GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, sprogress*c->size.w*2, sprogress*c->size.w*2);
			GNFloat sa = sprogress*(1+rand()%180)+rand()%180;
			GNShapeDrawBox(Yes, sr, sa);
			glColor4f(0.902, 0.0, 0.2, 1.0);
			GNShapeDrawBox(No, sr, sa);			
		} else if (ch->status == GNSTCharaStatusDamaged) {
			if (scf % 3 == 0) {
				glColor4f(1.000, 0.851, 0.0, 1.0);
			} else {
				glColor3f(0.929, 0.894, 0.804);
			}
		} else {
			// Normal color
			glColor3f(0.788, 0.459, 0.525);
		}
		glPushMatrix();
		s.h *= 0.5;
		s.w *= 0.5;
		glTranslatef(c->curo.x, c->curo.y, 0);
		glRotatef(c->angle*180/M_PI, 0.0, 0, 1.0);
		if (c->status == GNSTCharaStatusNormal) {
			glColor3f(0.545, 0.588, 0.553);
		}
		glBegin(GL_LINE_STRIP);
		glVertex2f(-s.w*0.8, -s.h);
		glVertex2f(-s.w, -s.h*0.8);
		glVertex2f(-s.w, s.h*0.8);
		glVertex2f(-s.w*0.8, s.h);
		glVertex2f(s.w*0.8, s.h);
		glVertex2f(s.w, s.h*0.8);
		glVertex2f(s.w, -s.h*0.8);
		glVertex2f(s.w*0.8, -s.h);
		glEnd();
		
		if (c->status == GNSTCharaStatusNormal) {
			glColor3f(0.922, 0.847, 0.259);
		}
		glBegin(GL_LINE_LOOP);
		glVertex2f(-s.w*0.4, -s.h*0.8);
		glVertex2f(-s.w*0.4, s.h*0.5);
		glVertex2f(-s.w*0.6, s.h*0.5);
		glVertex2f(-s.w*0.6, -s.h*0.3);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(s.w*0.4, -s.h*0.8);
		glVertex2f(s.w*0.4, s.h*0.5);
		glVertex2f(s.w*0.6, s.h*0.5);
		glVertex2f(s.w*0.6, -s.h*0.3);
		glEnd();
		
		
		if (c->status == GNSTCharaStatusNormal) {
			glColor3f(0.910, 0.224, 0.161);
		}
		GNShapeDrawBox(Yes, GNRectCreate(0, 0, c->size.w*0.15, c->size.h*0.15), progress*360);
		glPopMatrix();
	}
		else if (ch->style == GNSTCharaStyleBoss1) {
		glColor3f(0.925, 0.408, 0.0);
		if (ch->status == GNSTCharaStatusDead) {
			glColor3f(1, 0.851, 0.0);
			GNShapeDrawHex3D(No, GNRectCreate(c->curo.x, c->curo.y, c->size.w*(1-sprogress*0.5), c->size.h*(1-sprogress*0.5)),
							 GNRotationCreate(0, 0, sprogress*(rand()%180)), c->size.w);
			GNRect sr = GNRectCreate(ch->curo.x, ch->curo.y, sprogress*1.5*c->size.w, sprogress*1.5*c->size.h);
			GNFloat sa = sprogress*(1+rand()%180);
			glColor4f(1, 0.918, 0.0, 0.6);
			GNShapeDrawBox(Yes, sr, sa);
			sa = sprogress*(1+rand()%180);
			glColor4f(1, 0.918, 0.0, 0.3);
			GNShapeDrawBox(Yes, sr, sa);
			return;
		} else if (ch->status == GNSTCharaStatusDamaged) {
			if (scf % 4 == 0) {
				glColor4f(0.7, 0.7, 0.6, 1.0);
			}
		} 
		GNShapeDrawHex3D(No, GNRectCreate(c->curo.x, c->curo.y, c->size.w, c->size.h),
						 GNRotationCreate(0, 0, progress*360), c->size.w)	;
	}
	
}

void _GNSTCharaBulletBeamDraw(GNSTChara* c, _GNSTBulletOne* blt)
{
	//	GNPoint oldpos = blt->curo;
	blt->curo = GNPointCreate(c->curo.x+GNSTCharaInfo[c->style].bulOffset[0].x, c->curo.y+GNSTCharaInfo[c->style].bulOffset[0].y);
	
	
	// Calc beam anim
	int cf, tf;
	GNAnimGetFrame(c->ani, blt->animid, &cf, &tf);
	float progress = cf/(float)tf*2 - 1;
	float angle = sinf(progress*M_PI*2)*0.5+1;
	
	// Draw beam
	if (blt->kind == GNSTBulletTypeBeam1) {		
		
		glPushMatrix();
		glTranslatef(blt->curo.x, blt->curo.y, 0);
		
		glLineWidth(3.0);
		glColor4f(0.0, 0.584, 0.851, 1.0);
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glColor4f(0.0, 0.584, 0.851, 0.4);
		glVertex2f(0, GNSTBulletInfo[blt->kind].size.h);
		glEnd();
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x, blt->curo.y, GNSTBulletInfo[blt->kind].size.w, GNSTBulletInfo[blt->kind].size.h);
	} 
	else if (blt->kind == GNSTBulletTypeBeam2) {
		
		float w = GNSTBulletInfo[blt->kind].size.w;
		float h = GNSTBulletInfo[blt->kind].size.h;
		
		glPushMatrix();
		glLineWidth(1.0);
		glTranslatef(blt->curo.x-w*0.5, blt->curo.y, 0);
		
		glColor4f(0.765, 0.847, 0.145, 1.0-angle*0.2);
		
		glBegin(GL_POLYGON);
		glVertex2f(0, h*0.025);
		
		glColor4f(0.765, 0.847, 0.145,  0.4);
		glVertex2f(0, h);
		glVertex2f(w, h);
		
		glColor4f(0.765, 0.847, 0.145, 1.0-angle*0.2);
		glVertex2f(w, h*0.025);
		glVertex2f(w*0.5, 0);
		glVertex2f(0, h*0.025);
		glEnd();
		
		glColor4f(1.0, 1.0, 1.0, 0.7);
		float f4[4];
		f4[0] = xrandFloat(0, 1);
		f4[2] = f4[0]*angle;
		f4[1] = f4[0]*(angle-1);
		f4[3] = f4[0]*angle;
		
		GNShapeDrawFreak(Yes, GNRectCreate(blt->curo.x, blt->curo.y, w*2, w*2), f4);
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x-w*0.5, blt->curo.y, GNSTBulletInfo[blt->kind].size.w, GNSTBulletInfo[blt->kind].size.h);
	}
	
	
}

void _GNSTCharaBulletDraw(GNAnim* anim, _GNSTBulletOne* blt)
{
	int cf, tf;
	GNAnimGetFrame(anim, blt->animid, &cf, &tf);
	
	float angle = 0;
	// Calc nextpos
	blt->curo = GNPointCreate(blt->orig.x+blt->target.x*(cf/(float)tf), blt->orig.y+(cf/(float)tf)*blt->target.y);
	
	GNPoint deltapos;
	deltapos.x = blt->orig.x - blt->curo.x; deltapos.y = blt->orig.y - blt->curo.y;
	// Calc Bullet angle
	angle = 180*(atan2f(deltapos.y, deltapos.x))/M_PI;
	if (angle < 1) {
		// fix zero
		angle = -90;
	}
	
	// Draw bullet by kind
	if (blt->kind == GNSTBulletTypeNormal) {
		
		glPushMatrix();
		glTranslatef(blt->curo.x, blt->curo.y, 0);
		glRotatef(angle+90, 0, 0, 1);
		
		glLineWidth(1.0);
		glColor3f(0.243, 0.384, 0.678);
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, GNSTBulletInfo[blt->kind].size.h);
		
		glEnd();
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x, blt->curo.y, 0, GNSTBulletInfo[blt->kind].size.h);
	}
	else if (blt->kind == GNSTBulletTypeNormal2) {
		
		glPushMatrix();
		glTranslatef(blt->curo.x, blt->curo.y, 0);
		glRotatef(angle+90, 0, 0, 1);
		
		glLineWidth(1.5);
		glColor3f(0.914, 0.322, 0.584);
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, 0+GNSTBulletInfo[GNSTBulletTypeNormal2].size.h);
		glEnd();
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x, blt->curo.y, 0, GNSTBulletInfo[GNSTBulletTypeNormal2].size.h);
	}
	
	else if (blt->kind == GNSTBulletTypeTwin) {
		
		glLineWidth(2.0);
		glColor3f(0.863, 0.796, 0.94);
		
		glPushMatrix();
		glTranslatef(blt->curo.x-GNSTBulletInfo[GNSTBulletTypeTwin].size.w*0.5, blt->curo.y, 0);
		glRotatef(angle+90, 0, 0, 1);
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, 0+GNSTBulletInfo[GNSTBulletTypeTwin].size.h);
		glEnd();
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0+GNSTBulletInfo[GNSTBulletTypeTwin].size.w, 0);
		glVertex2f(0+GNSTBulletInfo[GNSTBulletTypeTwin].size.w, GNSTBulletInfo[GNSTBulletTypeTwin].size.h);
		glEnd();
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x-GNSTBulletInfo[GNSTBulletTypeTwin].size.w*0.5, blt->curo.y, GNSTBulletInfo[GNSTBulletTypeTwin].size.w, GNSTBulletInfo[GNSTBulletTypeTwin].size.h);
	}
	
	else if (blt->kind == GNSTBulletTypeHex1) {
	
		glPushMatrix();
		glTranslatef(blt->curo.x, blt->curo.y, 0);
		glRotatef(angle+90, 0, 0, 1);
		
		glLineWidth(4.0);
		glColor4f(0.773, 0.773, 0.416, 1.0);
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, GNSTBulletInfo[blt->kind].size.h*0.5);
		glEnd();
		
		glLineWidth(1.0);
		glColor4f(0.78, 0.863, 0.408, 1.0);
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, 0+GNSTBulletInfo[blt->kind].size.h);	
		glEnd();
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x, blt->curo.y, GNSTBulletInfo[blt->kind].size.w, GNSTBulletInfo[blt->kind].size.h);
	}
	
	else if (blt->kind == GNSTBulletTypeHex2) {
		float w = GNSTBulletInfo[blt->kind].size.w;
		float h = GNSTBulletInfo[blt->kind].size.h;
		
		glPushMatrix();
		glTranslatef(blt->curo.x-w*0.5, blt->curo.y, 0);
		glRotatef(angle+90, 0, 0, 1);
		
		glLineWidth(1.0);
		glColor4f(0.78, 0.863, 0.408, 1.0);		
		
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, h*0.25);
		glVertex2f(w*0.5, h);
		glVertex2f(w, h*0.25);
		glVertex2f(w*0.5, 0);
		glEnd();
		
		glPopMatrix();
		
		blt->area = GNRectCreate(blt->curo.x-w*0.5, blt->curo.y, GNSTBulletInfo[blt->kind].size.w, GNSTBulletInfo[blt->kind].size.h);
	}
}