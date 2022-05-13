/*�������� by ������. C 2015.6.6*/
/*�ϴ� �߷� ��ȣ�ۿ�� ���ڱ��� ��ȣ �ۿ����.
  ��ǻ�� �׷�������  ���� �ӵ��� �����̴� ���ڸ� ���� �� �� �����Ƿ� �Ű����ڴ� ���Ŀ� ����Ѵ�.
*/
//���Ͽ��� ����. �ϴ��� ��ü ��ü�� �����Ѵ�(ȸ���� ��ũ ����)

/*ver 0.1.0*/

#include <Windows.h>
#include <math.h>

///////////////////////////////���� ����///////////////////////////////////// 
typedef struct{
        double x, y, z, total;
} Vector;

#define SubVector(a,b) AddVector(a,NegateVector(b))

Vector *AddVector(Vector* a, Vector* b);
Vector *MulVectorNum(Vector *a, double num);
Vector *DivVectorNum(Vector *a, double num);
Vector *NegateVector(Vector *a);
Vector *Normalize(Vector *v);

///////////////////////////////���� ���� ��//////////////////////////////////
///////////////////////////////��ü ����/////////////////////////////////////
 

enum ObjectState {SOLID,LIQUID,GAS,PLASMA,QWARK_PLASMA};   //���� ������Ʈ 

typedef struct {
        enum ObjectState state;                                    //���� ������Ʈ 
} ObjectType;


#define NORMAL (ObjectType){SOLID}

typedef struct{
        double charge, elasticity;
        double mass;
        ObjectType type;
        int x, y, z;                //���� ��ǥ��. ��ǥ ��ȯ�� ���߿� �Ѵ� �ϴ��� ������ ȭ�� ���ϴ�. ���ǰ� �����Ƿ� 
                                    //x,y,z�� �߽� ��ǥ�̴�.
        unsigned int xsize,ysize,zsize,size;
        Vector velocity,acceleration;
        Vector f_net;               //��¥ ��
} Object;

extern int numofobjects;
#define MAX_OBJECTS 10
extern Object *objects[MAX_OBJECTS];

void update(Object * everything,Object *o);
BOOL KillObject(int i);
Object * AllocObject(double mass,double charge, int x, int y, int z, unsigned int xsize, unsigned int ysize, unsigned int zsize, double vx,double vy, double vz,double elasticity,ObjectType type);
BOOL KillAll();

////////////////////////////////UI ����/////////////////////////////////////////// 


void CALLBACK Handle_Timer(HWND,UINT,UINT,DWORD); 
extern double timer_interval;
extern BOOL bDo;
#define SIZE_X 500
#define SIZE_Y 500
#define SIZE_Z 500


/////////////////////////////////���� ����//////////////////////////////////////// 
#define GRAVITATIONAL_CONSTANT 9
#define ELECTROFORCE_CONSTANT 9e+9



Vector * Calc_distance_square(Object *a,Object *b);
Vector * Calc_gravity(Object *a, Object *b,Vector * distance);
Vector * Calc_electroforce(Object *a, Object *b,Vector * distance);
Vector * Calc_impact(Object *a, Object *b,Vector * distance);



