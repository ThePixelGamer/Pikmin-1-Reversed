#ifndef RECTAREA_H
#define RECTAREA_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

class SYSCORE_API RectArea {
private:
    int x;
    int y;
    int w;
    int h;

public:
    RectArea();
    RectArea(int, int, int, int);

    int 

};

#endif

/*



int 0;
int 1;
int 2;
int 3;

height = 3 - 1;
width = 2 - 0;





 */