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

#include "characters.h"
#include "game.h"

int FUR_initCharacter( player *pPlayer )
{
    int i, success;
    const char* a_texturesDemonic[] =
    {   
	"images/biped.png",
	"images/biped.png"
    };
	
    const char* a_texturesZoe[] = 
    {
	"images/zoe.png",
	"images/zoe.png"
    };

    switch ( pPlayer->who )
    {
	case Demonic:
		// Instead of using strcpy, use strncpy, where you specify the size of the destination character array.
		// The reason for doing this - if the source string ("Demonic" in this case) is longer than the destination array,
		// strncpy will only copy NAME_LENGTH characters, instead of illegally overwriting memory with more characters than can
		// be stored in the available memory. strcpy does not check the size so can (and often does) cause memory overwrites.
		// I defined NAME_LENGTH for this purpose, which is used to declare the array, and when copying.
		// Also note that strncpy will not automatically append a '\0' to the destination array if the source array is too long,
		// so it's good practice to automatically append this yourself when copying. Worst case scenario - the last character is chopped
		// off, but then the string will be properly terminated.

		// The Microsoft compiler will still complain that strncpy is unsafe because they made their own versions where you specify the length of the source *and* destination array to allow proper termination.
		// strncpy, however, is a standard C function...

		// You can make the same change to the other player names below...

	    strncpy( pPlayer->name, "Demonic", Name_Length);
		pPlayer->name[Name_Length - 1] = 0; // Note that 0 is the same as '\0'
	    pPlayer->position.y = 230;
	    pPlayer->health = 100;
	    pPlayer->guardBreak = 100;
	    pPlayer->jumpSpeed = normal;
	    pPlayer->walkSpeed = normal;
	    pPlayer->jumpDistance = mid;
	    pPlayer->meter = 4;
	    //Time to load the character textures
	    for ( i = 0; i < 2; i++ )
	    {
		success = FUR_textureLoad( a_texturesDemonic[i], i, 
				    pPlayer->textures.idle, pRenderer );
		if ( success == 0 )
		{
		    printf ("texture load failed");
		    return 0;
		}
	    }
		
	    break;

	case Zoe:
	    strcpy( pPlayer->name, "Zoe" );
	    pPlayer->position.y = 230;
	    pPlayer->health = 80;
	    pPlayer->guardBreak = 80;
	    pPlayer->jumpSpeed = normal;
	    pPlayer->walkSpeed = normal;
	    pPlayer->jumpDistance = mid;
	    pPlayer->meter = 4;
	    //Time to load the character textures
	    for ( i = 0; i < 2; i++ )
	    {
		success = FUR_textureLoad( a_texturesZoe[i], i, 
				    pPlayer->textures.idle, pRenderer );
		if ( success == 0 )
		{
		    printf ("texture load failed");
		    return 0;
		}
	    }		
	    break;

	case Angelic:

		break;
	case Character4:

		break;
	case Character5:

		break;
	case Character6:

		break;
	case Character7:

		break;
	case Character8:

		break;
	case Character9:

		break;
    }

    return 1;
}

