#ifndef __player__
#define __player__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vectors.h"
#include "configuration.h"
#include "gameObject.h"
#include "textureManager.h"


typedef enum {
	center,
	up,
	down,
	left,
	right,
	upLeft,
	upRight,
	downLeft,
	downRight
} direction;

typedef enum {
	slow,
	normal,
	fast
} speed;

typedef enum {
	close,
	mid,
	far
} distance;

typedef struct {
	int health;
	int meter;
	int guardBreak;
	int armor;
	bool jumping;
	bool crouching;
	bool attack;
	bool block;
	bool lightPunch;
	bool mediumPunch;
	bool hardPunch;
	bool lightKick;
	bool mediumKick;
	bool hardKick;
	speed jumpSpeed;
	speed walkSpeed;
	distance jumpDistance;	
	direction axis;
} player;

player* a_players[2];

int FUR_initPlayers();
void FUR_updatePlayers();
void FUR_cleanPlayer();

#endif //  __gameObject__
