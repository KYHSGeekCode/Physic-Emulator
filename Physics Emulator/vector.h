#include <math.h>

///////////////////////////////º¤ÅÍ ¿µ¿ª///////////////////////////////////// 
class Vector{
        double x, y, z, total;
        
};

#define SubVector(a,b) AddVector(a,NegateVector(b))

Vector *AddVector(Vector *a, Vector* b);
Vector *MulVectorNum(Vector *a, double num);
Vector *DivVectorNum(Vector *a, double num);
Vector *NegateVector(Vector *a);
Vector *Normalize(Vector *v);
