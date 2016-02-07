#ifndef __vector2d__
#define __vector2d__

#include <math.h>
 
typedef struct {
	float x;
	float y;
} vector2D;

typedef struct {
	float x;
	float y;
	float z;
} vector3D;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vector4D;

float FUR_lengthVector2D( vector2D v);
void FUR_norVector2D( vector2D *v );
vector2D FUR_addVector2D( vector2D v1, vector2D v2 );
vector2D FUR_subVector2D( vector2D v1, vector2D v2 );
vector2D FUR_mulVector2D( vector2D v1, float scalar );
vector2D FUR_divVector2D( vector2D v1, float scalar );


#endif // __vector2d__
