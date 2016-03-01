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
