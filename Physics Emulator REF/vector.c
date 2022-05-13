#include "physics.h"

Vector *AddVector(Vector* a, Vector* b){
       (a->x)+=(b->x);
       (a->y)+=(b->y);
       (a->z)+=(b->z);
       return Normalize(a);
}

Vector *MulVectorNum(Vector *a, double num){
       (a->x)*=num;
       (a->y)*=num;
       (a->z)*=num;
       (a->total)*=num;
       return a;
}
       
Vector *DivVectorNum(Vector *a, double num){
       if(num==0)
                 return a;
       (a->x)/=num;
       (a->y)/=num;
       (a->z)/=num;
       (a->total)/=num;
       return a;       
}

Vector *NegateVector(Vector *a){
       (a->x)*=-1;
       (a->y)*=-1;
       (a->z)*=-1;
       (a->total)*=-1;
       return a;
}

Vector *Normalize(Vector *v){
       v->total=sqrt((v->x)*(v->x)+(v->y)*(v->y)+(v->z)*(v->z));
       return v;
}

