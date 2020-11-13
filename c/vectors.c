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

#include "vectors.h"


int FUR_lengthVector2D( vector2D v)
{
	return sqrt( v.x * v.x + v.y * v.y );
}

vector2D FUR_addVector2D( vector2D v1, vector2D v2 )
{
	vector2D vect;
	vect.x = v1.x + v2.x;
	vect.y = v1.y + v2.y;
	return vect;
}

vector2D FUR_subVector2D( vector2D v1, vector2D v2 )
{
	vector2D vect;
	vect.x = v1.x - v2.x;
	vect.y = v1.y - v2.y;
	return vect;
}

vector2D FUR_mulVector2D( vector2D v1, int scalar )
{
	vector2D vect;
	vect.x = v1.x * scalar;
	vect.y = v1.y * scalar;
	return vect;
}

vector2D FUR_divVector2D( vector2D v1, int scalar )
{
	vector2D vect;
	vect.x = v1.x / scalar;
	vect.y = v1.y / scalar;
	return vect;
}

void FUR_norVector2D( vector2D *v )
{
	int len;
	vector2D result;

	len = FUR_lengthVector2D( *v );
	if ( len > 0 )
	{
		result = FUR_mulVector2D( *v, 1 / len );
		v = &result;
	}
}
