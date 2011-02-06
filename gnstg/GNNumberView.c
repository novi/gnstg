/*
 *  GNSTNumberView.c
 *  gnstg
 *
 *  Created by ito on 2009/02/22.
 *  Copyright 2009 Ito. All rights reserved.
 *
 */

#include "GNNumberView.h"


GNNumberView* GNNumberViewCreateWithAnim(GNAnim* anim, GNPoint p, GNFloat size, int maxdigit)
{
	if (!anim) return NULL;
	GNNumberView* nv = calloc(1, sizeof(GNNumberView));
	if (!nv) return NULL;

	nv->value = calloc(maxdigit+1, sizeof(char));
	if (!nv->value) {
		free(nv);
		return NULL;
	}
	memset(nv->value, '0', maxdigit);
	memcpy(nv->printfc, "%0", 2);
	char digit[10];
	sprintf(digit, "%d", maxdigit);
	strncpy(nv->printfc+2, digit, 9);
	memcpy(nv->printfc+2+strlen(digit), "d\0", 2);
	
	//printf("%s\n", nv->printfc);
	
	nv->anim = anim;
	nv->orig = p;
	nv->size = size;
	nv->digit = maxdigit;
	
	
	
	return nv;
}

void			GNNumberViewSetValue(GNNumberView* nv, long v)
{
	if (!nv) {
		return;
	}
	
	int i;
	for (i = 0; i < nv->digit; i++) {
		sprintf(nv->value, nv->printfc, v);
	}
}

void			GNNumberViewRelease(GNNumberView* nv)
{
	free(nv);
}

void			GNNumberViewDraw(GNNumberView* nv)
{

	GNFontDrawAtPoint(nv->orig, nv->size, 0.03, nv->value);
	
}