/*�������� by ������. C 2015.6.6*/
/*�ϴ� �߷� ��ȣ�ۿ�� ���ڱ��� ��ȣ �ۿ����.
  ��ǻ�� �׷�������  ���� �ӵ��� �����̴� ���ڸ� ���� �� �� �����Ƿ� �Ű����ڴ� ���Ŀ� ����Ѵ�.
*/
//���Ͽ��� ����. �ϴ��� ��ü ��ü�� �����Ѵ�(ȸ���� ��ũ ����)

/*ver 0.1.0*/

#include <Windows.h>
#include <math.h>
///////////////////////////////���� ����///////////////////////////////////// 
#include  "vector.h"
///////////////////////////////���� ���� ��//////////////////////////////////
///////////////////////////////��ü ����/////////////////////////////////////


enum ObjectState {SOLID,LIQUID,GAS,PLASMA,QWARK_PLASMA};   //���� ������Ʈ 
class ObjectType {
        enum ObjectState state;                            //���� ������Ʈ 
};

ObjectType NORMAL={SOLID};

class Object{
        double charge, elasticity;
        double mass;
        ObjectType type;
        int x, y, z;                //���� ��ǥ��. ��ǥ ��ȯ�� ���߿� �Ѵ� �ϴ��� ������ ȭ�� ���ϴ�. ���ǰ� �����Ƿ� 
                                    //x,y,z�� �߽� ��ǥ�̴�.
        unsigned int xsize,ysize,zsize,size;
        Vector velocity,acceleration;
        Vector f_net;               //��¥ ��
};

extern int numofobjects;	//number of objects existing
extern Object **objects;	//class pointer, array 

void update(Object ** everything,Object *o);	//called for updating objects' states
BOOL KillObject(int i);							//free memory of a specific object
//allocate new object
Object * AllocObject(double mass,double charge, int x, int y, int z, unsigned int xsize, unsigned int ysize, unsigned int zsize, double vx,double vy, double vz,double elasticity,ObjectType type);
BOOL KillAll();									//free all objects' memeory
void init();

////////////////////////////////UI ����/////////////////////////////////////////// 


void CALLBACK Handle_Timer(HWND,UINT,UINT,DWORD); //called for pre-processng objects(kill nulls, call OnUpdate())
extern double timer_interval;					  //specificity
extern BOOL bDo;								  //stop or not
#define SIZE_X 500								  //size of world x
#define SIZE_Y 500							      //size of world y
#define SIZE_Z 500							      //size of world z


/////////////////////////////////���� ����//////////////////////////////////////// 
#define GRAVITATIONAL_CONSTANT  (9e-10))
#define ELECTROFORCE_CONSTANT (9e+9))

Vector * Calc_distance_square(Object *a,Object *b);
Vector * Calc_gravity(Object *a, Object *b,Vector * distance);
Vector * Calc_electroforce(Object *a, Object *b,Vector * distance);
Vector * Calc_impact(Object *a, Object *b,Vector * distance);

