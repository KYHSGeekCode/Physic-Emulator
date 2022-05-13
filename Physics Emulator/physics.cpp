#include "physics.h"

Vector* Calc_distance_square(Object *a,Object *b){
        //total=dsitancesquare,x,y,z는 방향코사인
        double distancesquare,dx,dy,dz,distance;
        static Vector ret;
        dx=(a->x)-(b->x);
        dy=(a->y)-(b->y);
        dz=(a->z)-(b->z);
        distancesquare=dx*dx+dy*dy+dz*dz;
        distance=sqrt(distancesquare);
        ret.total=distancesquare;
        ret.x=dx/distance;
        ret.y=dy/distance;
        ret.z=dz/distance;
        return &ret;
}


Vector* Calc_gravity(Object *a, Object *b,Vector * distance){
        static Vector ret={0,0,0,0};
        ret.total=GRAVITATIONAL_CONSTANT*(a->mass)*(b->mass)/(distance->total);
        ret.x=(ret->total)*(distance->x);
        ret.y=(ret->total)*(distance->y);
        ret.z=(ret->total)*(distance->z);
        return ret;
}

Vector* Calc_electroforce(Object *a, Object *b,Vector * distance){
        static Vector ret={0,0,0,0};
        ret.total=ELECTROFORCE_CONSTANT*(a->charge)*(b->charge)/(distance->total);
        ret.x=(ret->total)*(distance->x);
        ret.y=(ret->total)*(distance->y);
        ret.z=(ret->total)*(distance->z);
        return ret;
}

Vector* Calc_impact(Object *a, Object *b,Vector * distance){
        double mtotal,mmul,e,dvx,dvy,dvz,quotient;
        static Vector I={0,0,0,0}; 
        if(distance->total<=(a->size)+(b->size))                                  //충돌 
        {
                  //if(a->type is conductor&&b->type is condoctor){
                  //             a->charge=b->charge=(a->charge+b->charge)/2;
                  //}
                  
                  //운동량 보존법칙과 반발계수의 정의를 이용
                   mtotal=a->mass+b->mass;
                   mmul=(a->mass)*(b->mass);
                   e=(a->elasticity)*(b->elasticity);
                   dvx=(b->velocity.x)-(a->velocity.x);
                   dvy=(b->velocity.y)-(a->velocity.y);
                   dvz=(b->velocity.z)-(a->velocity.z);
                   quotient=mmul*(e+1)/mtotal;
                   I.x=quotient*dsx;
                   I.y=quotient*dsy;
                   I.z=quotient*dsz;
                   return Normalize(I);
        }
}
