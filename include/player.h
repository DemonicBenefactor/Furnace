/*
    Furnace
    Copyright (C) 2015-2016 Demonic Benefactor <demonic@tutanota.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __player__
#define __player__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vectors.h"
#include "configuration.h"
#include "textureManager.h"
#include "furnaceTypes.h"

typedef struct {
	SDL_Texture* idle[64]; //also contains standing block
	SDL_Texture* walk[64];
	SDL_Texture* back[64];
	SDL_Texture* crouch[64]; //also contains crouching block
	SDL_Texture* jump[64];
	SDL_Texture* lightPunch[64]; //also the specials on contained herein
	SDL_Texture* mediumPunch[64];
	SDL_Texture* hardPunch[64];
	SDL_Texture* lightKick[64];
	SDL_Texture* mediumKick[64];
	SDL_Texture* hardKick[64];
	SDL_Texture* damage[64];
} playerTextures;


// You could use a define:
//#define Name_Length 16

// #defines are OK, but fairly old school since it's just substitution by the preprocessor, and not an actual explicit type, which can be checked by the compiler.

// In more modern code, we'd probably make a constant definition somewhere, or define an enum value that we include, something like this:
enum {Name_Length = 16};

typedef struct {
	character who;
	char name[Name_Length];
	float jumpTimer;
	float currentTime;
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
	vector2D position;
	playerTextures textures;
	SDL_RendererFlip flip;
} player;



player* a_players[2];

int FUR_initPlayers( SDL_Renderer* pRenderer, character P1, character P2 );
void FUR_renderPlayers( SDL_Renderer *pRenderer, player *pP1, player *pP2 );
void FUR_updatePlayers();
void FUR_cleanPlayer();

void FUR_playerJump( player* pPlayer );
#endif //player
