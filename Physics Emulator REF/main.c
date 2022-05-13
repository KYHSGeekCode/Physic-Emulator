#include <windows.h>
#include "physics.h"
double timer_interval;
BOOL bDo;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Windows App",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN MyPen,OldPen;
    HPEN MyBrush,OldBrush;
    double mq,dsx,dsz,dy;
    int i;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
             SetTimer(hwnd,1,timer_interval*1000,Handle_Timer);
             return 0;
        case WM_DESTROY:
             KillTimer(hwnd,1);
             KillAll();
             PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
             break;
        case WM_LBUTTONDOWN:
             bDo=!bDo;
             return 0;
        case WM_RBUTTONDOWN:
             AllocObject(rand()%50,(rand()%30-15)/10,rand()%SIZE_X,rand()%SIZE_Y,rand()%SIZE_Z,rand()%5+1,rand()%5+1,rand()%5+1,rand()%10,rand()%10,rand()%10,rand()/32767,NORMAL);
             return 0;
        case WM_PAINT:
             hdc=BeginPaint(hwnd,&ps);
             MyBrush=(HBRUSH)CreateSolidBrush(RGB(0,255,0));
             OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
             MyPen=CreatePen(PS_SOLID,5,RGB(0,0,255));
             OldPen=(HPEN)SelectObject(hdc,MyPen);
             for(i=0;i<MAX_OBJECTS;i++){
                     mq=(objects[i]->y)*(objects[i]->y);
                     dsx=(objects[i]->x)/mq;
                     dsz=(objects[i]->z)/mq;
                     dy=SIZE_Y-(objects[i]->z);
                     Rectangle(hdc, objects[i]->x-dsx/2,dy-dsz/2,(objects[i]->x)+dsx/2,(objects[i]->y)+dsz/2);
             }
             SelectObject(hdc,OldBrush);
             SelectObject(hdc,OldPen);
             DeleteObject(MyBrush);
             DeleteObject(MyPen);
             EndPaint(hwnd,&ps);
             return 0;
             
        default:                      /* for messages that we don't deal with */
             return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

VOID CALLBACK Handle_Timer(HWND hwnd,UINT uMSG,UINT iEvent,DWORD dwtime){
     int i,j;
      switch(iEvent){
                     case 1:
                          //죽은 물체를 찾는다.
                          for(i=0;i<MAX_OBJECTS;i++){
                                  if((objects[i]->x>100000)||(objects[i]->y>100000)||(objects[i]->z>100000)||(objects[i]->x<-10000)||(objects[i]->y<-10000)||(objects[i]->z<-10000)){
                                               KillObject(i);
                                               continue;
                                  }
                                  //objects[i]->f_net= {0,0,0,0};
                          }
                          for(j=0;j<MAX_OBJECTS;j++){
                                  update(objects,objects[j]);
                          }
                          //계산량이 n^2에서 1/2n(n+1)로 줄음
                          return;
                     default:
                             break;
      }
}
