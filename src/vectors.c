
#include "vectors.h"


float FUR_lengthVector2D( vector2D v)
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

vector2D FUR_mulVector2D( vector2D v1, float scalar )
{
	vector2D vect;
	vect.x = v1.x * scalar;
	vect.y = v1.y * scalar;
	return vect;
}

vector2D FUR_divVector2D( vector2D v1, float scalar )
{
	vector2D vect;
	vect.x = v1.x / scalar;
	vect.y = v1.y / scalar;
	return vect;
}

void FUR_norVector2D( vector2D *v )
{
	float len;
	vector2D result;

	len = FUR_lengthVector2D( *v );
	if ( len > 0 )
	{
		result = FUR_mulVector2D( *v, 1 / len );
		v = &result;
	}
}