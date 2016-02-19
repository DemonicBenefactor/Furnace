#ifndef __gameObject__
#define __gameObject__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "textureManager.h"


typedef enum {
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
	bool attack;
	bool block;
	speed jumpSpeed;
	speed walkSpeed;
	distance jumpDistance;	
	direction axis;
} player;

player* a_players[1];

int FUR_initPlayers();
void FUR_updatePlayer();
void FUR_cleanPlayer();

#endif //  __gameObject__
