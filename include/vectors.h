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

#ifndef __vector2d__
#define __vector2d__

#include <math.h>
 
typedef struct {
	int x;
	int y;
} vector2D;

typedef struct {
	int x;
	int y;
	int z;
} vector3D;

typedef struct {
	int x;
	int y;
	int z;
	int w;
} vector4D;

int FUR_lengthVector2D( vector2D v);
void FUR_norVector2D( vector2D *v );
vector2D FUR_addVector2D( vector2D v1, vector2D v2 );
vector2D FUR_subVector2D( vector2D v1, vector2D v2 );
vector2D FUR_mulVector2D( vector2D v1, int scalar );
vector2D FUR_divVector2D( vector2D v1, int scalar );


#endif // __vector2d__
