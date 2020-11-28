//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "repere.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


repere::repere ()
{};
//---------------------------------------------------------------------------
repere::repere (TCanvas* img,double xmin,double xmax,double ymin,double ymax)
{       
	if (xmin==xmax)    xmax=2*xmin; //code faux temporaire
        if (ymin==ymax)    ymax=2*ymin; //code faux temporaire


        interval_x = interval(xmin,xmax);
        interval_y = interval(ymin,ymax);
		canvas = img;
		width = canvas->ClipRect.Width();
		height = canvas->ClipRect.Height();

		ax = canvas->ClipRect.Width()/(interval_x.width());
		bx = -ax*interval_x.getInf();
		ay = canvas->ClipRect.Height()/(-interval_y.width());
		by = -ay*interval_y.getSup();
};
//---------------------------------------------------------------------------
void repere::XYCS2IJImg(double x, double y, unsigned int& I, unsigned int& J)
{
//	I = (unsigned int)((y - interval_y.getSup()) * IYRatio);
//	J = (unsigned int)((x - interval_x.getInf()) * JXRatio);
	I = (unsigned int)(ay*y+by);
	J = (unsigned int)(ax*x+bx);
}
//---------------------------------------------------------------------------
void repere::IJImg2XYCS(unsigned int i, unsigned int j, double& X, double& Y)
{
//	X = XJRatio * (double)j + interval_x.getInf();
//	Y = YIRatio * (double)i + interval_y.getSup();
	X = (1.0/ax) * (double)j + interval_x.getInf();
	Y = (1.0/ay) * (double)i + interval_y.getSup();
}
//---------------------------------------------------------------------------
void repere::GetCSPixelSize(double& sizeX, double& sizeY)
{
	sizeX = fabs(1.0/ax);
	sizeY = fabs(1.0/ay);
}
//---------------------------------------------------------------------------
unsigned int repere::XCS2JImg(double x)
{
	return (unsigned int)(ax*x+bx);
}
//---------------------------------------------------------------------------
unsigned int repere::YCS2IImg(double y)
{
	return (unsigned int)(ay*y+by);
}
//---------------------------------------------------------------------------
double repere::IImg2YCS(unsigned int i)
{
	return (1.0/ay) * (double)i + interval_y.getSup();
}
//---------------------------------------------------------------------------
double repere::JImg2XCS(unsigned int j)
{
	return (1.0/ax) * (double)j + interval_x.getInf();
}
//---------------------------------------------------------------------------
double repere::GetCSPixelSizeX(void)
{
	return fabs(1.0/ax);
}
//---------------------------------------------------------------------------
double repere::GetCSPixelSizeY(void)
{
	return fabs(1.0/ay);
}
//---------------------------------------------------------------------------
void repere::Clean()
{  canvas->Brush->Color=clWhite;
   canvas->Pen->Color=clWhite;
   canvas->Rectangle (0,0,width-1,height-1);
}
//---------------------------------------------------------------------------
void repere::DrawBox (box& P,TColor couleurin,TColor couleurout,TBrushStyle pinceau)
{  if (P.isEmpty()) return;
   canvas->Brush->Style=pinceau;
   canvas->Brush->Color=couleurin;
   canvas->Pen->Color=couleurout;
   canvas->Rectangle((int)(ax*P[1].getInf()+bx)-1,(int)(ay*P[2].getInf()+by)+1,
							(int)(ax*P[1].getSup()+bx)+1,(int)(ay*P[2].getSup()+by)-1);
   //canvas->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon,int epais=1)
{  if (P.isEmpty()) return;
   DrawLine(P[1].getInf(),P[2].getInf(),P[1].getInf(),P[2].getSup(),couleur,crayon,epais);
   DrawLine(P[1].getInf(),P[2].getInf(),P[1].getSup(),P[2].getInf(),couleur,crayon,epais);
   DrawLine(P[1].getSup(),P[2].getSup(),P[1].getInf(),P[2].getSup(),couleur,crayon,epais);
   DrawLine(P[1].getSup(),P[2].getSup(),P[1].getSup(),P[2].getInf(),couleur,crayon,epais);
   canvas->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon)
{  DrawCadre (P,couleur,crayon,1);
}
//---------------------------------------------------------------------------
void repere::DrawCircle (double x,double y,double r,TColor couleurin,TColor couleurout,int epais=1)
{  canvas->Pen->Color=couleurout;
   canvas->Brush->Color=couleurin;
   canvas->Pen->Width=epais;
//   canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
   canvas->Ellipse(ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by);
}
//---------------------------------------------------------------------------
void repere::DrawEllipse (double x,double y,double rx,double ry,TColor couleurin,TColor couleurout,int epais=1)
{  canvas->Pen->Color=couleurout;
   canvas->Brush->Color=couleurin;
   canvas->Pen->Width=1;
   canvas->Ellipse(ax*(x-rx)+bx,ay*(y-ry)+by,ax*(x+rx)+bx,ay*(y+ry)+by);
}
//---------------------------------------------------------------------------
void repere::DrawPixel (double x,double y,TColor couleur)
{
   canvas->Pixels[(unsigned int)(ax*x+bx)][(unsigned int)(ay*y+by)] = couleur;
}
//---------------------------------------------------------------------------
void repere::DrawPoint (double x,double y,TColor couleur,double epais)
{  canvas->Pen->Color=couleur;
   canvas->Brush->Color=couleur;
   canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
}
//---------------------------------------------------------------------------
void repere::DrawPoint2 (double x,double y,TColor couleur,int taille)
{  canvas->Pen->Color=couleur;
   canvas->Pen->Width=taille;
   canvas->MoveTo (ax*x+bx,ay*y+by);
   canvas->LineTo (ax*x+bx+1,ay*y+by+1);
}

//---------------------------------------------------------------------------
void repere::DrawPointCadre (double x,double y,TColor couleur,double taillex,double tailley)
{  box B(2);
   B[1]=interval(x-taillex,x+taillex);
   B[2]=interval(y-tailley,y+tailley);
   DrawCadre (B,couleur,psSolid,1);
}


//---------------------------------------------------------------------------
void repere::DrawLine (double x1,double y1,double x2, double y2,TColor couleur,
                       TPenStyle crayon,int taille)
{  canvas->Pen->Color=couleur;
   canvas->Pen->Style=crayon;
   canvas->Pen->Width=taille;
   canvas->MoveTo (ax*x1+bx,ay*y1+by);
   if (fabs(ax*x2+bx)+fabs(ay*y2+by)<10000)
   {
      canvas->LineTo (ax*x2+bx,ay*y2+by);
   }
   canvas->Pen->Width=1;
}
//---------------------------------------------------------------------------
void repere::DrawPolygon(double* xa,double* ya,int imin,int imax, TColor c)
{   POINT points[14];
    for (int i=0; i<=imax-imin;i++)
    {   double x1=xa[i+imin];
        double y1=ya[i+imin];
        points[i] = Point(ax*x1+bx,ay*y1+by);
    }
    //for (int i=imax-imin+1;i<=100-1;i++)
    //{   double xai=xa[i+imin];
    //    double yai=ya[i+imin];
    //    points[i] = Point(xa[imin],ya[imin]);}
    canvas->Brush->Color = c;
    canvas->Pen->Color = clBlack;
    //canvas->Polygon(points,13);
}
//---------------------------------------------------------------------------
void repere::DrawGrid (TColor couleur, TPenStyle crayon=psDash , int epais=1, double da=1.0, bool texte=false)
{  int a=INT(interval_x.getInf());
   while (a<interval_x.getSup())
    { DrawLine(a,interval_y.getInf(),a,interval_y.getSup(),couleur,crayon,epais);
      if (texte) DrawText (a,interval_y.getSup(),IntToStr(a));
      a=a+da;
    };
   a=INT(interval_y.getInf());
   while (a<interval_y.getSup())
    {  DrawLine(interval_x.getInf(),a,interval_x.getSup(),a,couleur,crayon,epais);
       if (texte) DrawText (interval_x.getInf(),a,IntToStr(a));
       a=a+da;
    };
};
//---------------------------------------------------------------------------
void repere::DrawBox (box& P,TColor couleurin,TColor couleurout,TBrushStyle pinceau,int i1,int i2)
{ if (P.isEmpty()) return;
  box Q(2);  Q[1]=P[i1];  Q[2]=P[i2];
  DrawBox (Q,couleurin,couleurout,pinceau);
}
//---------------------------------------------------------------------------
void repere::DrawData (box& Y,box& t,TColor couleur,double epais)
{ if (Y.isEmpty()||t.isEmpty()) return;
  box Q(2);
  for (int j=1;j<=Y.getDim();j++)
  {  Q[1]=t[j];  Q[2]=Y[j];
     Q=Inflate(Q,epais);
     DrawBox (Q,couleur,couleur,bsSolid);
  }
  DrawLine(interval_x.getInf(),0,interval_x.getSup(),0,clBlack,psSolid,1);
  DrawLine(0,interval_y.getInf(),0,interval_y.getSup(),clBlack,psSolid,1);
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon,int i1,int i2,int epais=1)
{ if (P.isEmpty()) return;
  box Q(2);
  Q[1]=P[i1]; Q[2]=P[i2];  DrawCadre (Q,couleur,crayon,epais);
}
//---------------------------------------------------------------------------
void repere::DrawText (double x,double y,const AnsiString Text)
{    canvas->Brush->Color=clWhite;
    canvas->Font->Color = clBlue;
    canvas->TextOut(ax*x+bx,ay*y+by, Text);
}
//---------------------------------------------------------------------------


