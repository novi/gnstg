#include "GNShape.h"

void GNShapeDrawBox(GNBool fill, GNRect r, GNFloat angle)
{
	GNShapeDrawBoxWithZ(fill, r, angle, 0);
}


void GNShapeDrawBoxWithZ(GNBool fill, GNRect r, GNFloat angle, GNFloat zpos)
{
	glPushMatrix();
	GNPoint o = GNCalcOriginByRect(r);
	//GNPoint to = GNConvertToOriginByRect(r);
	
	glTranslatef(r.o.x, r.o.y, zpos);
	glRotatef(angle, 0.0, 0.0, 1.0);
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex2d(o.x,o.y);
	glVertex2d(o.x+r.s.w, o.y);
	glVertex2d(o.x+r.s.w, o.y+r.s.h);
	glVertex2d(o.x, o.y+r.s.h);
	glVertex2d(o.x, o.y);
	
	glEnd();
	
	glPopMatrix();
}

void GNShapeDrawProgressBar(GNRect r, float progress, GLfloat* color4bar, GLfloat* color4back, GNFloat angle)
{
	glPushMatrix();
	
	glTranslatef(r.o.x, r.o.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	
	glLineWidth(1.0);
	
	glColor4fv(color4bar);
	glBegin(GL_QUADS);
	glVertex2d(0, 0);
	glVertex2d(r.s.w*progress, 0);
	glVertex2d(r.s.w*progress, r.s.h);
	glVertex2d(0, r.s.h);
	glEnd();
	
	glColor4fv(color4back);
	glBegin(GL_LINE_STRIP);
	glVertex2d(0, 0);
	glVertex2d(r.s.w, 0);
	glVertex2d(r.s.w, r.s.h);
	glVertex2d(0, r.s.h);
	glVertex2d(0, 0);
	glEnd();
	
	
	
	glPopMatrix();
}


void GNShapeDrawFreak(GNBool fill, GNRect r, GNFloat* f4)
{
	GNPoint o = GNCalcOriginByRect(r);
	if (fill) {
		glBegin(GL_QUADS);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex2d(o.x,o.y+r.s.h*f4[0]);
	glVertex2d(o.x+r.s.w*f4[1], o.y+r.s.h);
	glVertex2d(o.x+r.s.w, o.y+r.s.h*f4[2]);
	glVertex2d(o.x+r.s.w*f4[3], o.y);
	
	glEnd();
}

void GNShapeDrawHex(GNBool fill, GNRect r, GNFloat angle)
{
	glPushMatrix();
	//GNPoint o = GNCalcOriginByRect(r);
//	GNPoint to = GNConvertToOriginByRect(r);
	
	glTranslatef(r.o.x, r.o.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	
	glBegin(GL_LINE_LOOP);
	int i;
	GNPoint p;
	for (i = 0; i < 6; i++) {
		p = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, i*(M_PI/3.0)));
		glVertex2d(p.x, p.y);
	}
	glEnd();
	
	glPopMatrix();
}


void GNShapeDrawBox3D(GNBool fill, GNRect r, GNRotation a, GNFloat zsize)
{
	glPushMatrix();
	GNPoint o = GNCalcOriginByRect(r);
	
	glTranslatef(r.o.x, r.o.y, 0);
	
	glRotatef(a.ax, 1.0, 0.0, 0.0);
	glRotatef(a.ay, 0.0, 1.0, 0.0);
	glRotatef(a.az, 0.0, 0.0, 1.0);
	
	
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex3d(o.x,o.y, zsize*0.5);
	glVertex3d(o.x+r.s.w, o.y, zsize*0.5);
	glVertex3d(o.x+r.s.w, o.y+r.s.h, zsize*0.5);
	glVertex3d(o.x, o.y+r.s.h, zsize*0.5);
	glVertex3d(o.x, o.y, zsize*0.5);
	glEnd();
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex3d(o.x, o.y, zsize*0.5);
	glVertex3d(o.x, o.y, -zsize*0.5);
	glEnd();
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex3d(o.x+r.s.w, o.y, zsize*0.5);
	glVertex3d(o.x+r.s.w, o.y, -zsize*0.5);
	glEnd();
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex3d(o.x, o.y+r.s.h, zsize*0.5);
	glVertex3d(o.x, o.y+r.s.h, -zsize*0.5);
	glEnd();
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex3d(o.x+r.s.w, o.y+r.s.h, zsize*0.5);
	glVertex3d(o.x+r.s.w, o.y+r.s.h, -zsize*0.5);
	glEnd();
	
	if (fill) {
		glBegin(GL_TRIANGLE_STRIP);
	} else {
		glBegin(GL_LINE_STRIP);
	}
	glVertex3d(o.x,o.y, -zsize*0.5);
	glVertex3d(o.x+r.s.w, o.y, -zsize*0.5);
	glVertex3d(o.x+r.s.w, o.y+r.s.h, -zsize*0.5);
	glVertex3d(o.x, o.y+r.s.h, -zsize*0.5);
	glVertex3d(o.x, o.y, -zsize*0.5);
	glEnd();
	
	glPopMatrix();
	
}

void GNShapeDrawHex3D(GNBool fill, GNRect r, GNRotation a, GNFloat zsize)
{
	glPushMatrix();
	glTranslatef(r.o.x, r.o.y, zsize);
	glRotatef(a.ax, 1.0, 0.0, 0.0);
	glRotatef(a.ay, 0.0, 1.0, 0.0);
	glRotatef(a.az, 0.0, 0.0, 1.0);
	
	
	int i;
	GNPoint p, p2;
	
	if (fill) {
		for (i = 0; i < 6; i++) {
			p = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, i*(M_PI/3.0)));
			if (i == 5) {
				p2 = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, 0));
			} else {
				p2 = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, (i-1)*(M_PI/3.0)));
			}
			glBegin(GL_TRIANGLES);
			glVertex3d(p.x, p.y, zsize*0.5);
			glVertex3d(p2.x, p2.y, zsize*0.5);
			glVertex3d(0, 0, zsize*0.5);
			glVertex3d(p.x, p.y, -zsize*0.5);
			glVertex3d(p2.x, p2.y, -zsize*0.5);
			glVertex3d(0, 0, -zsize*0.5);
			glEnd();
			
			glBegin(GL_QUADS);
			glVertex3d(p.x, p.y, zsize*0.5);
			glVertex3d(p.x, p.y, -zsize*0.5);
			glVertex3d(p2.x, p2.y, -zsize*0.5);
			glVertex3d(p2.x, p2.y, zsize*0.5);
			glEnd();
		}

		
		
	} else {
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 6; i++) {
			p = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, i*(M_PI/3.0)));
			glVertex3d(p.x, p.y, zsize*0.5);
		}
		glEnd();
		
		
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 6; i++) {
			p = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, i*(M_PI/3.0)));
			glVertex3d(p.x, p.y, -zsize*0.5);
			//glVertex3d(p.x, p.y, 0);
		}
		glEnd();
		
		for (i = 0; i < 6; i++) {
			glBegin(GL_LINE_STRIP);
			p = GNPointCreateByPolar(GNPolarCreate(r.s.w*0.5, i*(M_PI/3.0)));
			glVertex3d(p.x, p.y, zsize*0.5);
			glVertex3d(p.x, p.y, -zsize*0.5);
			glEnd();
		}
	}

	
	
	glPopMatrix();

}



