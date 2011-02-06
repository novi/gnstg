#include "GNSTPlayer.h"


GNSTPlayer* GNSTPlayerCreateWithAnim(GNSize size, GNPoint defOrig, GNRect frame, GNAnim* anim)
{
	GNSTPlayer* pl = malloc(sizeof(GNSTPlayer));
	if (!pl) return NULL;
	
	pl->bulletlevel = 0;
	
	GNSTCharaInitWithAnim(&pl->chara, size, defOrig, frame, anim);
	GNSTCharaSetStyle(&pl->chara, GNSTCharaStylePlayer);
	GNSTCharaSetStatus(&pl->chara, GNSTCharaStatusNormal);
	
	
	return pl;
}


void		GNSTPlayerFireBullet(GNSTPlayer* pl)
{
	if (!pl) return;
	GNSTCharaAddBullet(&pl->chara, GNSTPlayerLev[pl->bulletlevel].bullet, GNSTPlayerLev[pl->bulletlevel].count, No, NULL);
}

void		GNSTPlayerSetBulletLevel(GNSTPlayer* pl, int lev, GNBool delta)
{
	if (!pl) return;
	
	if (delta) {
		pl->bulletlevel += lev;
	} else {
		pl->bulletlevel = lev;
	}
	
	if (pl->bulletlevel > (int)kPlayerMaxLevel) {
		pl->bulletlevel = (int)kPlayerMaxLevel;
	} else if (pl->bulletlevel < 0) {
		pl->bulletlevel = 0;
	}
	
	
	GNSTCharaRemoveBulletBeam(&pl->chara);
}


void		GNSTPlayerRelease(GNSTPlayer* pl)
{
	if (!pl) return;
	GNSTCharaRelease(&pl->chara);
	free(pl);
}


