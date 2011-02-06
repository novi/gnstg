/*
 *  GNSTBackg.c
 *  gnstg
 *
 *  Created by ito on 2009/02/16.
 *  Copyright 2009 Ito. All rights reserved.
 *
 */

#include "GNSTBackg.h"
#include "GNSTParam.h"

const static float _GNSTBackgBaseColor[][4] = {
{0.051, 0.0, 0.082, 1.0},
{0.051, 0.0, 0.082, 1.0},

{0.051, 0.0, 0.082, 1.0},
{0.051, 0.0, 0.082, 1.0},
{0.051, 0.0, 0.082, 1.0},

{0.086, 0.086, 0.055, 1.0},
{0.086, 0.086, 0.055, 1.0},
{0.086, 0.086, 0.055, 1.0},
};

const static float _GNSTBackgMainColor[][4] = {
{0.973, 0.984, 0.973, 1.0},
{0.349, 0.345, 0.341, 1.0},

{0.0, 0.267, 0.294, 1.0},
{0.0, 0.204, 0.243, 1.0},
{0.357, 0.333, 0.294, 1.0},

{0.0, 0.267, 0.294, 1.0},
{0.329, 0.118, 0.271, 1.0},
{0.357, 0.333, 0.294, 1.0},

};

const static float _GNSTBackgSubColor[][4] = {
{0.973, 0.984, 0.973, 1.0},
{0.349, 0.345, 0.341, 0.5},

{0.0, 0.267, 0.294, 0.5},
{0.165, 0.200, 0.380, 0.5},
{0.282, 0.302, 0.263, 0.5},

{0.0, 0.267, 0.294, 0.5},
{0.231, 0.110, 0.290, 0.5},
{0.282, 0.302, 0.263, 0.5},

};




GNSTBackg*		GNSTBackgCreate(GNRect frame)
{
	GNSTBackg* bg = malloc(sizeof(GNSTBackg));
	if (!bg) return NULL;
	
	bg->anim = GNAnimCreateWithFPS(kFPS);
	if (!bg->anim) {
		free(bg);
		return NULL;
	}
	
	bg->frame = frame;
	bg->style = GNSTBackgStyleNone;
	bg->motion = GNSTBackgMotionStable;
	
	memset(bg->animid, 0, sizeof(bg->animid));
	
	return bg;
}

void			GNSTBackgSetStyle(GNSTBackg* bg, GNSTBackgStyle style)
{
	if (!bg) return;
	
	bg->style = style;
	printf("bg style %d\n", bg->style);
	
}

void			GNSTBackgSetMotion(GNSTBackg* bg, GNSTBackgMotion motion)
{
	bg->motion = motion;
	GNAnimRemove(bg->anim, bg->animid[0]);
	
	if (bg->motion == GNSTBackgMotionMoveDownRight) {
		bg->animid[0] = GNAnimAdd(bg->anim, 4.0, Yes, No);
	}
	if (bg->motion == GNSTBackgMotionMoveDownRightFaster) {
		bg->animid[0] = GNAnimAdd(bg->anim, 2.0, Yes, No);
	}
}

void			GNSTBackgRelease(GNSTBackg* bg)
{
	if (!bg) return;
	GNAnimRelease(bg->anim);
	free(bg);
}

void			GNSTBackgStemFrame(GNSTBackg* bg)
{
	if (!bg) return;
	GNAnimStepFrame(bg->anim);
}


void			_GNSTBackgDrawBase(GNSTBackg* bg)
{
	
		//glColor4f(0.7, 0.6, 0.0, 0.4);
	glColor4fv(&_GNSTBackgBaseColor[bg->style][0]);
	glPushMatrix();
	glTranslatef(bg->frame.o.x, bg->frame.o.y, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, bg->frame.s.h);
	glVertex2f(bg->frame.s.w, bg->frame.s.h);
	glVertex2f(bg->frame.s.w, 0);
	glEnd();
	glPopMatrix();
}

void			GNSTBackgDraw(GNSTBackg* bg)
{
	if (!bg) return;
	
	_GNSTBackgDrawBase(bg);
	
	if (bg->motion == GNSTBackgMotionMoveDownRight || bg->motion == GNSTBackgMotionMoveDownRightFaster) {
		
		const float speed[][4] = {{},{},{0.25, 1, 0.2, 0.4},{0.25, 1, 0.2, 0.4},
			{0.75, 1.5, 0.4, 0.8}};
		
		
		int cf, tf;
		GNAnimGetFrame(bg->anim, bg->animid[0], &cf, &tf);
		float progress = cf/(float)tf;
		
		glColor4fv(&_GNSTBackgMainColor[bg->style][0]);
		
		glPushMatrix();
		glTranslatef(bg->frame.o.x+(speed[bg->motion][0]*progress), 0, 0);
		int i;
		for (i = 0; i < 11; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f(0.25*i, bg->frame.o.y);
			glVertex2f(0.25*i, bg->frame.s.h);
			glEnd();
		}
		glPopMatrix();
		
		
		
		glPushMatrix();
		glTranslatef(0, bg->frame.o.y-(speed[bg->motion][1]*progress), 0);
		for (i = 0; i < 15; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f(bg->frame.o.x, (0.25)*i);
			glVertex2f(bg->frame.s.w, (0.25)*i);
			glEnd();
		}
		glPopMatrix();
		
		
		glColor4fv(&_GNSTBackgSubColor[bg->style][0]);
		glPushMatrix();
		glTranslatef(bg->frame.o.x+(speed[bg->motion][2]*progress), 0, 0);
		for (i = 0; i < 11; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f(0.2*i, bg->frame.o.y);
			glVertex2f(0.2*i, bg->frame.s.h);
			glEnd();
		}
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, bg->frame.o.y-(speed[bg->motion][3]*progress), 0);
		for (i = 0; i < 15; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f(bg->frame.o.x, (0.2)*i);
			glVertex2f(bg->frame.s.w, (0.2)*i);
			glEnd();
		}
		glPopMatrix();
		
	}
}

//void			_GNSTBackgDrawMesh(gnrect 

