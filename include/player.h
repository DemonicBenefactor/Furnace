#ifndef __player__
#define __player__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "vectors.h"
#include "configuration.h"
#include "gameObject.h"
#include "textureManager.h"
#include "characters.h"
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

typedef struct {
	character who;
	char name[16];
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
} player;



player* a_players[2];

int FUR_initPlayers( SDL_Renderer* pRenderer, character P1, character P2 );
void FUR_renderPlayers( SDL_Renderer *pRenderer, player *pPlayer1, player *pPlayer2 );
void FUR_updatePlayers();
void FUR_cleanPlayer();

void FUR_playerJump( player* pPlayer );
#endif //player
