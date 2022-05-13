#include "physics.h"
Object **objects;	//하나는 class pointer, 하나는 배열 
int numOfObjects;

void init()
{
	numOfObjects=1;
	objects=new Object[numOfObjects];
	
}	

void update(Object **everything,Objejct *o){
     Vector impact,gravity,distancesquare,electroforce;
     impact=gravity=distancesquare=electroforce={0,0,0,0};
     
     for(int i=0;i<MAX_OBJECTS;i++){                                                //모든 알짜힘 계산 
             if(everything[i]==NULL)
                     continue;
             distancesquare=*Calc_distance_square(everything[i],o);
             impact=*calc_impact(everything[i],o,distancesquare);
             gravity=*calc_gravity(everything[i],o,distancesquare);
             electroforce=*calc_electroforce(everything[i],o,distancesquare);
             AddVector(&(o->f_net),impact);
             AddVector(&(o->f_net),gravity);
             AddVector(&(o->f_net),electroforce);
             SubVector(&(everything[i]->f_net),impact);
             SubVector(&(everything[i]->f_net),gravity);
             SubVector(&(everything[i]->f_net),electroforce);
     }
     AddVector(&(o->acceleration),DivVectorNum(&(o->f_net),o->mass));              //F=ma 
     AddVector(&(o->velocity),MulVectorNum(&(o->acceleration),timer_interval));    //적분
     (o->x)+=(o->velocity.x)*timer_interval;
     (o->y)+=(o->velocity.y)*timer_interval;
     (o->z)+=(o->velocity.z)*timer_interval;
     return;
}
     
             
     
BOOL KillObject(int i){
     if(objects[i]!=NULL)
     {
             free(objects[i]);
             objects[i]=NULL;
             return TRUE;
     }
     return FALSE;
}

BOOL KillAll(){
     for(int i=0;i<MAX_OBJECTS;i++){
             KillObject(i);
     }
}

Object *AllocObject(unsigned double mass,double charge, int x, int y, int z, unsigned int xsize, unsigned int ysize, unsigned int zsize, double vx,double vy, double vz,double elasticity,ObjectType type){
       Object *o=new object();
       if(o!=NULL){
                   for(int i=0;i<numofobjects;i++){
                           if(objects[i]==NULL){
                                                objects[i]=o;
                                                goto success;
                           }
                   }
                   numofobjects++;
                   
                   objects[numofobjects]=o;
                   
       success:
                   o->mass=mass;
                   o->charge=charge;
                   o->x=x;
                   o->y=y;
                   o->z=z;
                   o->xsize=xsize;
                   o->ysize=ysize;
                   o->zsize=zsize;
                   o->velocity.x=vx;
                   o->velocity.y=vy;
                   o->velocity.z=vz;
                   o->elasticity=elastacity;
                   o->type=type;
                   return o;
       }
       return NULL;
}
                   
