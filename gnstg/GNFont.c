

#include "GNFont.h"

struct gn_font_line {
	int pointcount;
	const GNPoint* points;
};

struct gn_font_info {
	float	aspect;
	int		linecount;
	const struct gn_font_line* lines;
};

static const GNPoint _GNFontDataC0p[] = {{0, 0}, {0, 1.0}, {1.0, 1.0}, {1.0, 0}, {0, 0}, {1.0, 1.0}};
static const struct gn_font_line _GNFontDataC0[] = {{6, _GNFontDataC0p}};

static const GNPoint _GNFontDataC1p[] = {{0, 1.0}, {0.5, 1.0}, {0.5, 0}};
static const struct gn_font_line _GNFontDataC1[] = {{3, _GNFontDataC1p}};

static const GNPoint _GNFontDataC2p[] = {{0, 1.0}, {1.0, 1.0}, {1.0, 0.5}, {0, 0.5}, {0, 0}, {1.0, 0}};
static const struct gn_font_line _GNFontDataC2[] = {{6, _GNFontDataC2p}};

static const GNPoint _GNFontDataC3p[] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}};
static const GNPoint _GNFontDataC3p2[] = {{0.2, 0.5}, {1, 0.5}};
static const struct gn_font_line _GNFontDataC3[] = {{4, _GNFontDataC3p}, {2, _GNFontDataC3p2}};

static const GNPoint _GNFontDataC4p[] = {{0, 1}, {0, 0.5}, {1, 0.5}};
static const GNPoint _GNFontDataC4p2[] = {{1, 1}, {1, 0}};
static const struct gn_font_line _GNFontDataC4[] = {{3, _GNFontDataC4p}, {2, _GNFontDataC4p2}};

static const GNPoint _GNFontDataC5p[] = {{1, 1}, {0, 1}, {0, 0.5}, {1, 0.5}, {1, 0}, {0, 0}};
static const struct gn_font_line _GNFontDataC5[] = {{6, _GNFontDataC5p}};

static const GNPoint _GNFontDataC6p[] = {{0, 1}, {0, 0}, {1, 0}, {1, 0.5}, {0, 0.5}};
static const struct gn_font_line _GNFontDataC6[] = {{5, _GNFontDataC6p}};

static const GNPoint _GNFontDataC7p[] = {{0, 0.5}, {0, 1}, {1, 1}, {1, 0}};
static const struct gn_font_line _GNFontDataC7[] = {{4, _GNFontDataC7p}};

static const GNPoint _GNFontDataC8p[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}};
static const GNPoint _GNFontDataC8p2[] = {{0, 0.5}, {1, 0.5}};
static const struct gn_font_line _GNFontDataC8[] = {{5, _GNFontDataC8p}, {2, _GNFontDataC8p2}};

static const GNPoint _GNFontDataC9p[] = {{1, 0.5}, {0, 0.5}, {0, 1}, {1, 1}, {1, 0}};
static const struct gn_font_line _GNFontDataC9[] = {{5, _GNFontDataC9p}};

// A
static const GNPoint _GNFontDataCAp[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
static const GNPoint _GNFontDataCAp2[] = {{0, 0.5}, {1, 0.5}};
static const struct gn_font_line _GNFontDataCA[] = {{4, _GNFontDataCAp}, {2, _GNFontDataCAp2}};

static const GNPoint _GNFontDataCBp[] = {{0, 0}, {0, 1}, {1, 1}, {0.5, 0.5}, {1, 0}, {0, 0}};
static const GNPoint _GNFontDataCBp2[] = {{0, 0.5}, {0.5, 0.5}};
static const struct gn_font_line _GNFontDataCB[] = {{6, _GNFontDataCBp}, {2, _GNFontDataCBp2}};

static const GNPoint _GNFontDataCCp[] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}};
static const struct gn_font_line _GNFontDataCC[] = {{4, _GNFontDataCCp}};

static const GNPoint _GNFontDataCDp[] = {{0, 0}, {0, 1}, {1, 0.75}, {1, 0.25}, {0, 0}};
static const struct gn_font_line _GNFontDataCD[] = {{5, _GNFontDataCDp}};

static const GNPoint _GNFontDataCEp[] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}};
static const GNPoint _GNFontDataCEp2[] = {{0, 0.5}, {1, 0.5}};
static const struct gn_font_line _GNFontDataCE[] = {{4, _GNFontDataCEp}, {2, _GNFontDataCEp2}};

static const GNPoint _GNFontDataCFp[] = {{1, 1}, {0, 1}, {0, 0}};
static const GNPoint _GNFontDataCFp2[] = {{0, 0.5}, {1, 0.5}};
static const struct gn_font_line _GNFontDataCF[] = {{3, _GNFontDataCFp}, {2, _GNFontDataCFp2}};

static const GNPoint _GNFontDataCGp[] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, 0.5}, {0.5, 0.5}};
static const struct gn_font_line _GNFontDataCG[] = {{6, _GNFontDataCGp}};

// H

static const GNPoint _GNFontDataCHp[] = {{0, 0}, {0, 1}};
static const GNPoint _GNFontDataCHp2[] = {{1, 1}, {1, 0}};
static const GNPoint _GNFontDataCHp3[] = {{0, 0.5}, {1, 0.5}};
static const struct gn_font_line _GNFontDataCH[] = {{2, _GNFontDataCHp}, {2, _GNFontDataCHp2}, {2, _GNFontDataCHp3}};

static const GNPoint _GNFontDataCIp[] = {{0.5, 1}, {0.5, 0}};
static const struct gn_font_line _GNFontDataCI[] = {{2, _GNFontDataCIp}};

static const GNPoint _GNFontDataCJp[] = {{1, 1}, {1, 0}, {0, 0}, {0, 0.5}};
static const struct gn_font_line _GNFontDataCJ[] = {{4, _GNFontDataCJp}};

static const GNPoint _GNFontDataCKp[] = {{1, 1}, {0, 0.5}, {1, 0}};
static const GNPoint _GNFontDataCKp2[] = {{0, 0}, {0, 1}};
static const struct gn_font_line _GNFontDataCK[] = {{3, _GNFontDataCKp}, {2, _GNFontDataCKp2}};

static const GNPoint _GNFontDataCLp[] = {{0, 1}, {0, 0}, {1, 0}};
static const struct gn_font_line _GNFontDataCL[] = {{3, _GNFontDataCLp}};

static const GNPoint _GNFontDataCMp[] = {{0, 0}, {0, 1}, {0.5, 0.5}, {1, 1}, {1, 0}};
static const struct gn_font_line _GNFontDataCM[] = {{5, _GNFontDataCMp}};

static const GNPoint _GNFontDataCNp[] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
static const struct gn_font_line _GNFontDataCN[] = {{4, _GNFontDataCNp}};

//O
static const GNPoint _GNFontDataCOp[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}};
static const struct gn_font_line _GNFontDataCO[] = {{5, _GNFontDataCOp}};

static const GNPoint _GNFontDataCPp[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0.5}, {0, 0.5}};
static const struct gn_font_line _GNFontDataCP[] = {{5, _GNFontDataCPp}};

static const GNPoint _GNFontDataCQp[] = {{1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0.5, 0.5}};
static const struct gn_font_line _GNFontDataCQ[] = {{6, _GNFontDataCQp}};

static const GNPoint _GNFontDataCRp[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0.5}, {0, 0.5}};
static const GNPoint _GNFontDataCRp2[] = {{0.5, 0.5}, {1, 0}};
static const struct gn_font_line _GNFontDataCR[] = {{5, _GNFontDataCRp}, {2, _GNFontDataCRp2}};

static const GNPoint _GNFontDataCSp[] = {{1, 0.75}, {1, 1}, {0, 1}, {0, 0.5}, {1, 0.5}, {1, 0}, {0, 0}, {0, 0.25}};
static const struct gn_font_line _GNFontDataCS[] = {{8, _GNFontDataCSp}};

static const GNPoint _GNFontDataCTp[] = {{0, 1}, {1, 1}};
static const GNPoint _GNFontDataCTp2[] = {{0.5, 1}, {0.5, 0}};
static const struct gn_font_line _GNFontDataCT[] = {{2, _GNFontDataCTp}, {2, _GNFontDataCTp2}};

static const GNPoint _GNFontDataCUp[] = {{0, 1}, {0, 0}, {1, 0}, {1, 1}};
static const struct gn_font_line _GNFontDataCU[] = {{4, _GNFontDataCUp}};

// V
static const GNPoint _GNFontDataCVp[] = {{0, 1}, {0.5, 0}, {1, 1}};
static const struct gn_font_line _GNFontDataCV[] = {{3, _GNFontDataCVp}};

static const GNPoint _GNFontDataCWp[] = {{0, 1}, {0.25, 0}, {0.5, 1}, {0.75, 0}, {1, 1}};
static const struct gn_font_line _GNFontDataCW[] = {{5, _GNFontDataCWp}};

static const GNPoint _GNFontDataCXp[] = {{0, 1}, {1, 0}};
static const GNPoint _GNFontDataCXp2[] = {{1, 1}, {0, 0}};
static const struct gn_font_line _GNFontDataCX[] = {{2, _GNFontDataCXp}, {2, _GNFontDataCXp2}};

static const GNPoint _GNFontDataCYp[] = {{0, 1}, {0.5, 0.5}};
static const GNPoint _GNFontDataCYp2[] = {{1, 1}, {0.5, 0.5}, {0.5, 0}};
static const struct gn_font_line _GNFontDataCY[] = {{2, _GNFontDataCYp}, {3, _GNFontDataCYp2}};

static const GNPoint _GNFontDataCZp[] = {{0, 1}, {1, 1}, {0, 0}, {1, 0}};
static const struct gn_font_line _GNFontDataCZ[] = {{4, _GNFontDataCZp}};

static const struct gn_font_info GNFontData[] = {
{0.6, 10, NULL},
//0
{0.6, 1, _GNFontDataC0},
{0.2, 1, _GNFontDataC1},
{0.6, 1, _GNFontDataC2},
{0.6, 2, _GNFontDataC3},
{0.5, 2, _GNFontDataC4},
//5
{0.6, 1, _GNFontDataC5},
{0.6, 1, _GNFontDataC6},
{0.5, 1, _GNFontDataC7},
{0.6, 2, _GNFontDataC8},
{0.6, 1, _GNFontDataC9},

//A
{0.6, 2, _GNFontDataCA},
{0.6, 2, _GNFontDataCB},
{0.6, 1, _GNFontDataCC},
{0.6, 1, _GNFontDataCD},
{0.6, 2, _GNFontDataCE},
{0.6, 2, _GNFontDataCF},
{0.6, 1, _GNFontDataCG},

//H
{0.6, 3, _GNFontDataCH},
{0.2, 1, _GNFontDataCI},
{0.6, 1, _GNFontDataCJ},
{0.75, 2, _GNFontDataCK},
{0.6, 1, _GNFontDataCL},
{0.75, 1, _GNFontDataCM},
{0.6, 1, _GNFontDataCN},

// O
{0.75, 1, _GNFontDataCO},
{0.6, 1, _GNFontDataCP},
{0.75, 1, _GNFontDataCQ},
{0.75, 2, _GNFontDataCR},
{0.6, 1, _GNFontDataCS},
{0.75, 2, _GNFontDataCT},
{0.6, 1, _GNFontDataCU},
// V
{0.6, 1, _GNFontDataCV},
{0.8, 1, _GNFontDataCW},
{0.6, 2, _GNFontDataCX},
{0.6, 2, _GNFontDataCY},
{0.6, 1, _GNFontDataCZ},
};

void _GNFontDrawChar(GNRect r, int fontindex);


void GNFontDrawAtPoint(GNPoint p, GNFloat size, GNFloat spacing, const char* str)
{
	
	
	int i;
	GNPoint stp = p;
	for (i = 0; i < strlen(str); i++) {
		char c = str[i];
		int index = 0;
		if (48 <= c && 57 >= c) {
			index = c - 47;
		}
		if (65 <= c && 90 >= c) {
			index = c - 65 +1+10;
		}
		
		GNRect fontr = GNRectCreate(stp.x, stp.y, size*GNFontData[index].aspect, size);
		_GNFontDrawChar(fontr, index);
		stp.x += spacing+fontr.s.w;
	}
}

float GNFontDrawCharAtPoint(GNPoint p, GNFloat size, char c)
{
	int index = 0;
	if (48 <= c && 57 >= c) {
		index = c - 47;
	}
	if (65 <= c && 90 >= c) {
		index = c - 65 +1+10;
	}
	
	GNRect fontr = GNRectCreate(p.x, p.y, size*GNFontData[index].aspect, size);
	_GNFontDrawChar(fontr, index);
	
	return fontr.s.w;
}
	
void _GNFontDrawChar(GNRect r, int fontindex)
{
	glPushMatrix();
	glLineWidth(1.0);
	glTranslatef(r.o.x, r.o.y, 0.0);
	glScalef(r.s.w, r.s.h, 0);
	int li, pi;
	for (li = 0; li < GNFontData[fontindex].linecount; li++) {
		glBegin(GL_LINE_STRIP);
		for (pi = 0; pi < GNFontData[fontindex].lines[li].pointcount; pi++) {
			glVertex2d(GNFontData[fontindex].lines[li].points[pi].x, GNFontData[fontindex].lines[li].points[pi].y);
		}
		glEnd();
	}
	glPopMatrix();
}