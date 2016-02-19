
#include "player.h"

int FUR_initPlayer()
{	
	int i;
	for (i = 0; i < 2; i++)
	{
		player* p;
		p = malloc(sizeof(player));
		a_players[i] = p;
	}
	return 1;
}


void FUR_updatePlayer()
{

}

void FUR_cleanPlayer()
{

}

