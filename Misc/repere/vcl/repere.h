//---------------------------------------------------------------------------
#ifndef repereH
#define repereH
#include <vcl.h>
#include "box.h"
//---------------------------------------------------------------------------
class repere
{   public:
	interval	interval_y;
	interval	interval_x;
    TImage *image;
    repere ();
    repere (TImage*,reel,reel,reel,reel);
    void DrawBox (box&,TColor,TColor,TBrushStyle) ;
    void DrawBox (box&,TColor,TColor,TBrushStyle,int,int);
    void DrawCadre (box&,TColor,TPenStyle);
    void DrawCadre (box&,TColor,TPenStyle,int);
    void DrawCadre (box&,TColor,TPenStyle,int,int,int);
    void DrawData (box& Y,box& t,TColor couleur,reel);
    void DrawLine (reel,reel,reel,reel,TColor,TPenStyle,int);
    void DrawGrid (TColor, TPenStyle, int, double,bool);
    void DrawCircle (reel x,reel y, reel r, TColor, TColor, int);
    void DrawCircle(reel x, reel y, reel r, TColor couleurout, int epais = 1);
    void DrawEllipse (reel x,reel y,reel rx,reel ry,TColor couleurin,TColor couleurout,int epais);
    void DrawPoint (reel x1,reel y1,TColor couleur,double epais);
    void DrawPoint2 (reel x1,reel y1,TColor couleur,int epais);
    void DrawPointCadre (reel x,reel y,TColor couleur,double,double);
    void DrawPolygon(reel*,reel*,int,int, TColor);
    void Clean();
    void DrawText (double x,double y,const AnsiString Text);
    void ChangementRepere(int x_pixel,int y_pixel,double* x, double* y);
    void DrawWordFrame (box& P,TColor couleur,TPenStyle crayon,int epais=1);
    void DrawWordFrame (box& P,TColor couleur,TPenStyle crayon);
};

#endif
