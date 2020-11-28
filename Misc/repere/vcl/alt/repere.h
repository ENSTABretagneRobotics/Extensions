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
    TCanvas* canvas;
	UINT width;
	UINT height;
	double ax, ay, bx, by;
    repere ();
    repere (TCanvas*,double,double,double,double);
    void DrawBox (box&,TColor,TColor,TBrushStyle) ;
    void DrawBox (box&,TColor,TColor,TBrushStyle,int,int);
    void DrawCadre (box&,TColor,TPenStyle);
    void DrawCadre (box&,TColor,TPenStyle,int);
    void DrawCadre (box&,TColor,TPenStyle,int,int,int);
    void DrawData (box& Y,box& t,TColor couleur,double);
    void DrawLine (double,double,double,double,TColor,TPenStyle,int);
    void DrawGrid (TColor, TPenStyle, int, double,bool);
    void DrawCircle (double x,double y, double r, TColor, TColor, int);
    void DrawEllipse (double x,double y,double rx,double ry,TColor couleurin,TColor couleurout,int epais);
	void DrawPixel (double x,double y,TColor couleur);
	void DrawPoint (double x1,double y1,TColor couleur,double epais);
    void DrawPoint2 (double x1,double y1,TColor couleur,int epais);
    void DrawPointCadre (double x,double y,TColor couleur,double,double);
    void DrawPolygon(double*,double*,int,int, TColor);
    void Clean();
    void DrawText (double x,double y,const AnsiString Text);
	void XYCS2IJImg(double x, double y, unsigned int& I, unsigned int& J);
	void IJImg2XYCS(unsigned int i, unsigned int j, double& X, double& Y);
	void GetCSPixelSize(double& sizeX, double& sizeY);
	unsigned int XCS2JImg(double x);
	unsigned int YCS2IImg(double y);
	double JImg2XCS(unsigned int j);
	double IImg2YCS(unsigned int i);
	double GetCSPixelSizeX(void);
	double GetCSPixelSizeY(void);
};

#endif
