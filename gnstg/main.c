#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#ifdef SysOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "GNSTGlobal.h"

struct ga_s {
	GNAnim* anim;
	GNSTMap* map;
	GNSTBackg* bg;
	int bulletreg;
	GNBool up,down,left,right,fire;
	GNSTInfoView* iv;
	int currentstage;
	int curstyle;
	int teststage;
	GNBool debug;
};
typedef struct ga_s STG;

void _GNSTMainChangeStage(void);
void GNSTGReshape(int w, int h);
void GNSTGDisplay(void);
void GNSTGTimer(int t);
void GNSTGIdle(void);
long _GNSTMainReadHighScore(void);
void _GNSTMainWriteHighScore(long p);
void _GNSTGWillExit(void);

static STG* ga;
static const GNRect GNSTMainFrame = {{-1, -kMaxHeight}, {2,kMaxHeight*2}};


const static GNSTScript GNSTMainScript[] = {
/* enemylevel */ /* enemymotion; */ /*spawntimer */ /*enemymax*/ /* boss */
{0, GNMotionTypeLine, 6.0, 0.5, 30, No},
{0, GNMotionTypeSine, 6.0, 0.05, 50, No},
{1, GNMotionTypeLine, 5.0, 0.2, 50, No},

{2, GNMotionTypeLine, 6.0, 0.4, 50, No},
{3, GNMotionTypeLine, 5.0, 0.3, 50, No},

{4, GNMotionTypeSine, 5.0, 0.3, 30, No},
{5, GNMotionTypeLine, 5.0, 0.3, 40, No},

{6, GNMotionTypeLine, 7.0, 0.3, 40, No},
{7, GNMotionTypeLine, 7.0, 0.3, 40, No},

{8, GNMotionTypeLine, 8.0, 0.3, 40, No},
{9, GNMotionTypeLine, 8.0, 0.3, 40, No},


{0,					0, 5.0, 0.2, 4, Yes},
};

struct gnst_stage {
	GNSTBackgStyle backgs;
	GNSTBackgMotion backgm;
	int				requirekill;
	int				scriptid;
};


const static struct gnst_stage GNSTMainStageData[] = {
/* backg style */		/* backg motion */			/* killed enemy to move stage */ /* script id in GNSTMainScript */ 
{GNSTBackgStyleNormal,GNSTBackgMotionMoveDownRight, 100, 0},
{GNSTBackgStyleDark1,GNSTBackgMotionMoveDownRight, 300, 1},
{GNSTBackgStyleDark2,GNSTBackgMotionMoveDownRight,  100, 2},
{GNSTBackgStyleDark3,GNSTBackgMotionMoveDownRight, 120, 3},
{GNSTBackgStyleBlack1,GNSTBackgMotionMoveDownRight,  100, 4},
{GNSTBackgStyleBlack2,GNSTBackgMotionMoveDownRight, 120, 5},
{GNSTBackgStyleBlack3,GNSTBackgMotionMoveDownRight, 120, 6},
{GNSTBackgStyleBlack2,GNSTBackgMotionMoveDownRight, 120, 7},
{GNSTBackgStyleDark1,GNSTBackgMotionMoveDownRight, 120, 8},
{GNSTBackgStyleDark2,GNSTBackgMotionMoveDownRight, 120, 9},
{GNSTBackgStyleDark1,GNSTBackgMotionMoveDownRight, 120, 10},
{GNSTBackgStyleDark3, GNSTBackgMotionMoveDownRightFaster, 4, 11},
};


#define kMainStageMax (sizeof(GNSTMainStageData)/sizeof(struct gnst_stage) -1)


void GNSTGTimer(int t)
{
	glutPostRedisplay();
	
	GNAnimStepFrame(ga->anim);
	GNSTMapStepFrame(ga->map);
	GNSTBackgStemFrame(ga->bg);
	
	
	// If player life more than zero
	if (GNSTCharaGetLife((GNSTChara*)GNSTMapGetPlayerChara(ga->map)) > 0) {
		GNPoint pp = GNSTCharaGetCurrentPos(GNSTMapGetPlayerChara(ga->map));
		
		if (ga->up) {
			pp.y += kPlayerSense;
		}
		if (ga->down) {
			pp.y -= kPlayerSense;
		}
		if (ga->left) {
			pp.x -= kPlayerSense;
		}
		if (ga->right) {
			pp.x += kPlayerSense;
		}
		
		if (ga->fire) {
			if (ga->bulletreg % 2 == 0) {
				GNSTPlayerFireBullet(ga->map->player);
			}
		} else {
			GNSTCharaRemoveBulletBeam(GNSTMapGetPlayerChara(ga->map));
		}
		GNSTCharaSetPos(GNSTMapGetPlayerChara(ga->map), pp);
	}
	
	ga->bulletreg++;
	
	glutTimerFunc(1000/(float)kFPS, GNSTGTimer, 0);
	glutPostRedisplay();
	
	if (GNSTMainStageData[ga->currentstage].requirekill <= GNSTMapGetCountEnemyKilled(ga->map)) {
		ga->currentstage++;
		_GNSTMainChangeStage();
	}
}


void _GNSTMainChangeStage(void)
{
	
	if (ga->currentstage > kMainStageMax) {
		ga->currentstage = 0;
	}
	
	printf("move to stage %d\n", ga->currentstage);
	struct gnst_stage nextstage = GNSTMainStageData[ga->currentstage];
	GNSTMapSetScript(ga->map, &GNSTMainScript[nextstage.scriptid]);
	GNSTInfoViewSetStageNum(ga->iv, ga->currentstage+1);
	GNSTBackgSetStyle(ga->bg, nextstage.backgs);
	GNSTBackgSetMotion(ga->bg, nextstage.backgm);
}

void GNSTGIdle(void)
{
	//  glutPostRedisplay();
}

void GNSTGKeyup(unsigned char key, int x, int y) 
{
	if (key == 'w') {
		ga->up = No;
	}
	if (key == 's') {
		ga->down = No;
	}
	if (key == 'a') {
		ga->left = No;
	}
	if (key == 'd') {
		ga->right = No;
	}
	
	if (key == 'k') {
		ga->fire = No;
	}
	
	if (key == '9') {
		_GNSTGWillExit();
		exit(0);
	}
}

void GNSTGKey(unsigned char key, int x, int y)
{
	
	if (key == 'w') {
		ga->up = Yes;
	}
	if (key == 's') {
		ga->down = Yes;
	}
	if (key == 'a') {
		ga->left = Yes;
	}
	if (key == 'd') {
		ga->right = Yes;
	}
	if (key == 'k') {
		ga->fire =Yes;
	}
	
	// Debug function
	if (ga->debug) {
		if (key == 'o') {
			GNSTPlayerSetBulletLevel(ga->map->player, 1, Yes);
		}
		
		if (key == 'p') {
			GNSTPlayerSetBulletLevel(ga->map->player, -1, Yes);
		}
		
		if (key =='t') {
			ga->currentstage++;
			_GNSTMainChangeStage();
		}
		if (key == 'y') {
			ga->currentstage--;
			_GNSTMainChangeStage();
		}
	}
}

int main (int argc, char** argv)
{
	GNBool debug = No;
	if (argc == 2 && strncmp(argv[1], "-d", 4) == 0) {
		debug = Yes;
	}
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutCreateWindow(kWindowTitleText);
	glutDisplayFunc(GNSTGDisplay);
	glutReshapeFunc(GNSTGReshape);
	glutTimerFunc(1000, GNSTGTimer, 0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardUpFunc(GNSTGKeyup);
	glutKeyboardFunc(GNSTGKey);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	// Create main game structure
	ga = malloc(sizeof(STG));
	memset(ga, 0, sizeof(STG));
	
	// Create game stage
	ga->map = GNSTMapCreate(GNSTMainFrame);
	if (!ga->map) {
		exit(EXIT_FAILURE);
	}
	GNSTMapSetHighScore(ga->map, _GNSTMainReadHighScore());
	
	ga->debug = debug;
	
	ga->bg = GNSTBackgCreate(GNSTMainFrame);
	if (!ga->bg) {
		exit(EXIT_FAILURE);
	}
	
	ga->anim = GNAnimCreateWithFPS(kFPS);
	if (!ga->anim) {
		exit(EXIT_FAILURE);
	}
	
	ga->curstyle = 1;
	GNSTBackgSetStyle(ga->bg, 1);
	GNSTBackgSetMotion(ga->bg, GNSTBackgMotionMoveDownRight);
	
	ga->iv = GNSTInfoViewCreateWithAnim(ga->anim, GNSTMainFrame);
	GNSTMapSetInfoView(ga->map, ga->iv);
	
	ga->currentstage = 0;
	_GNSTMainChangeStage();
	
	// Create GLUT main loop
	glutMainLoop();
	
	return 0;
}

void GNSTGReshape(int w, int h)
{
	glViewport(0, 0, kWindowWidth, kWindowHeight);
	//
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	//	glFrustum(-kMaxWidth, kMaxWidth, -kMaxHeight, kMaxHeight, 1.0, 2.0);
	
	gluPerspective(30.0, (double)w / (double)h, 1.0f, 10.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	glTranslatef(0.0f, 0.0f, -4.5f);
	
	gluLookAt(0, 0, 1.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); 
}

// Redraw function
void GNSTGDisplay(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	GNSTBackgDraw(ga->bg);
	
	GNSTMapDraw(ga->map);
	
	
	/*
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.95,-(kMaxHeight - 0.05));
	glVertex2d(-0.95, (kMaxHeight - 0.05));
	glVertex2d(0.95, (kMaxHeight - 0.05));
	glVertex2d(0.95, -(kMaxHeight - 0.05));
	glVertex2d(-0.95, -(kMaxHeight - 0.05));
	glEnd();
	 */
	
	GNSTInfoViewDraw(ga->iv);
	
	glFlush();
 	glutSwapBuffers();
}

void _GNSTGWillExit(void)
{
	_GNSTMainWriteHighScore(GNSTMapGetHighScore(ga->map));
}

long _GNSTMainReadHighScore(void)
{
	FILE *fp;
	char s[256];
	if ((fp = fopen("highscore", "r")) == NULL) {
		return 0;
	}
	long score = 0;
	while (fgets(s, 256, fp) != NULL) {
		sscanf(s, "%d",&score);
		break;
	}
	fclose(fp);
	printf("readed score %ld\n", score);
	return score;
}

void _GNSTMainWriteHighScore(long p)
{
	FILE *fp;
	if ((fp = fopen("highscore", "w")) == NULL) {
		return;
	}
	printf("wrote score %ld\n", p);
	fprintf(fp, "%d", p);
	fclose(fp);
}
	
