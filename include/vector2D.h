#ifndef __vector2d__
#define __vector2d__

#include <math.h>
 
typedef struct {
	float x;
	float y;
} vector2D;

float FUR_lengthVector2D( vector2D v);
void FUR_norVector2D( vector2D *v );
vector2D FUR_addVector2D( vector2D v1, vector2D v2 );
vector2D FUR_subVector2D( vector2D v1, vector2D v2 );
vector2D FUR_mulVector2D( vector2D v1, vector2D v2 );
vector2D FUR_divVector2D( vector2D v1, vector2D v2 );


#endif // __vector2d__