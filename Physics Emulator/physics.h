/*물리엔진 by 양현서. C 2015.6.6*/
/*일단 중력 상호작용과 전자기적 상호 작용부터.
  컴퓨터 그래픽으로  빛의 속도로 움직이는 광자를 보여 줄 수 없으므로 매개입자는 추후에 고려한다.
*/
//뉴턴역학 버전. 일단은 강체 고체로 가정한다(회전과 토크 무시)

/*ver 0.1.0*/

#include <Windows.h>
#include <math.h>
///////////////////////////////벡터 영역///////////////////////////////////// 
#include  "vector.h"
///////////////////////////////벡터 영역 끝//////////////////////////////////
///////////////////////////////물체 영역/////////////////////////////////////


enum ObjectState {SOLID,LIQUID,GAS,PLASMA,QWARK_PLASMA};   //추후 업데이트 
class ObjectType {
        enum ObjectState state;                            //추후 업데이트 
};

ObjectType NORMAL={SOLID};

class Object{
        double charge, elasticity;
        double mass;
        ObjectType type;
        int x, y, z;                //직각 좌표계. 좌표 변환은 나중에 한다 일단은 원점은 화면 좌하단. 부피가 있으므로 
                                    //x,y,z는 중심 좌표이다.
        unsigned int xsize,ysize,zsize,size;
        Vector velocity,acceleration;
        Vector f_net;               //알짜 힘
};

extern int numofobjects;	//number of objects existing
extern Object **objects;	//class pointer, array 

void update(Object ** everything,Object *o);	//called for updating objects' states
BOOL KillObject(int i);							//free memory of a specific object
//allocate new object
Object * AllocObject(double mass,double charge, int x, int y, int z, unsigned int xsize, unsigned int ysize, unsigned int zsize, double vx,double vy, double vz,double elasticity,ObjectType type);
BOOL KillAll();									//free all objects' memeory
void init();

////////////////////////////////UI 영역/////////////////////////////////////////// 


void CALLBACK Handle_Timer(HWND,UINT,UINT,DWORD); //called for pre-processng objects(kill nulls, call OnUpdate())
extern double timer_interval;					  //specificity
extern BOOL bDo;								  //stop or not
#define SIZE_X 500								  //size of world x
#define SIZE_Y 500							      //size of world y
#define SIZE_Z 500							      //size of world z


/////////////////////////////////물리 영역//////////////////////////////////////// 
#define GRAVITATIONAL_CONSTANT  (9e-10))
#define ELECTROFORCE_CONSTANT (9e+9))

Vector * Calc_distance_square(Object *a,Object *b);
Vector * Calc_gravity(Object *a, Object *b,Vector * distance);
Vector * Calc_electroforce(Object *a, Object *b,Vector * distance);
Vector * Calc_impact(Object *a, Object *b,Vector * distance);

