#include "GNAnim.h"


GNAnim*	GNAnimCreateWithFPS(int fps)
{
	GNAnim* anim = malloc(sizeof(GNAnim));
	if (!anim) {
		return NULL;
	}
	anim->framespeed = 1/(float)fps;
	anim->animcount = 0;
	anim->latestid = 1;
	anim->storesize = GN_ANIM_STORE;
	anim->store = calloc(GN_ANIM_STORE, sizeof(_GNAnimOne));
	if (!anim->store) {
		free(anim);
		return NULL;
	}
	anim->storetable = calloc(GN_ANIM_STORE, sizeof(int));
	if (!anim->storetable) {
		free(anim->store);
		free(anim);
		return NULL;
	}
	
	return anim;
}
	
GNAnimID				GNAnimAdd(GNAnim* anim, GNFloat sec, GNBool repeat, GNBool removeWhenDone)
{
	if (!anim) return 0;
	
	if (sec <= 0) {
		return 0;
	}
	GNAnimID id = 0;
	int i;
	if (anim->animcount+GN_ANIM_STORE/10 >= anim->storesize) {
		printf("anim buffer will allocate, animcount %d stores %d\n", anim->animcount, anim->storesize);
		anim->store = realloc(anim->store, sizeof(_GNAnimOne)*(anim->storesize+GN_ANIM_STORE));
		anim->storetable = realloc(anim->storetable, sizeof(int)*(anim->storesize+GN_ANIM_STORE));
		if (!anim->store || !anim->storetable) {
			return 0;
		}
		memset(anim->store+anim->storesize, 0, sizeof(_GNAnimOne)*GN_ANIM_STORE);
		memset(anim->storetable+anim->storesize, 0, sizeof(int)*GN_ANIM_STORE);
		anim->storesize += GN_ANIM_STORE;
	}

	int debgMissed = 0;
	int indexid = 0;
	if (!anim->storetable[anim->latestid]) {
		id = anim->latestid;
		anim->storetable[id] = anim->animcount+1;
		indexid = anim->storetable[id];
	} else {
		for (i = anim->latestid; i < anim->storesize; i++) {
			// Find empty buffer
			if (!anim->storetable[i]) {
				// Found one
				id = i;
				anim->storetable[id] = anim->animcount+1;
				indexid = anim->storetable[id];
				anim->latestid++;
				break;
			} else {
				debgMissed++;
			}
		}	
		//printf("missed %d\n", debgMissed);
	}

	
	
	
	if (!id || !indexid) {
		printf("FAILED to add anim\n");
		printf("STORESIZE %d anim cnt %d\n", anim->storesize, anim->animcount);
		return 0;
	}
	
	_GNAnimOne* ao = &anim->store[indexid];
	
	ao->removewd = removeWhenDone;
	ao->repeat = repeat;
	ao->curframe = 0;
	ao->maxframe = sec/anim->framespeed;
	ao->id = id;
	
	anim->animcount++;
	
	return id;
}

int				GNAnimCount(GNAnim* anim)
{
	if (!anim) return 0;
	return anim->animcount;
}

void			GNAnimGetFrame(GNAnim* anim, GNAnimID id, int* rcur, int* rmax)
{
	if (!anim) return;
	int indexid = anim->storetable[id];
	_GNAnimOne* ao = &anim->store[indexid];
	if (!indexid) {
		*rcur = -1; *rmax = 0;
		return;
	}

	*rcur = ao->curframe;
	*rmax = ao->maxframe;
}

void			GNAnimRemove(GNAnim* anim, GNAnimID id)
{
	if (!anim) return;
	if (!id) return;
	

	int indexid = anim->storetable[id];
	
	// Copy anim_one to removed anim_one from latest anim_one in store
	if (indexid < anim->animcount) {
		memcpy(&anim->store[indexid], &anim->store[anim->animcount], sizeof(_GNAnimOne));
		anim->storetable[anim->store[anim->animcount].id] = indexid;
	}
		anim->storetable[id] = 0;
		anim->animcount--;
	
	if (anim->latestid > id) {
		anim->latestid = id;
	}
}

void			GNAnimStepFrame(GNAnim* anim)
{
	if (!anim) return;	
	//int debgMissed = 0;
	int i;
	for (i = 1; i <= anim->animcount; i++) {
	//	if (anim->store[i].valid) {
			_GNAnimOne* one = &anim->store[i];
			
			if (one->maxframe <= one->curframe) {
				if (one->repeat) {
					one->curframe = 0;
					continue;
				} else if (one->removewd) {
					GNAnimRemove(anim, i);
					continue;
				} else {
				// Repeat no, rwd no
					continue;
				}
			}
			one->curframe++;
	}
}

void			GNAnimRelease(GNAnim* anim)
{
	if (!anim) return;
	free(anim->storetable);
	free(anim->store);
	free(anim);
}
