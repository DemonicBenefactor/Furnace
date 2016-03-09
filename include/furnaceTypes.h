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

#ifndef __furnaceTypes__
#define __furnaceTypes__

typedef enum {
	Demonic,
	Zoe,
	Angelic,
	Character4,
	Character5,
	Character6,
	Character7,
	Character8,
	Character9
} character;

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
	slowest = 120,
	slow = 100,
	normal = 80,
	fast = 60,
	fastest = 40
} speed;

typedef enum {
	closest,
	close,
	mid,
	far,
	furthest
} distance;


#endif //furnaceTypes
