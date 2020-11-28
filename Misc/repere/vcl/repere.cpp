//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "repere.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


repere::repere ()
{};
//---------------------------------------------------------------------------
repere::repere (TImage* f,reel xmin,reel xmax,reel ymin,reel ymax)
{       if (xmin==xmax)    xmax=2*xmin; //code faux temporaire
        if (ymin==ymax)    ymax=2*ymin; //code faux temporaire
        interval_x=interval(xmin,xmax);
        interval_y=interval(ymin,ymax);
	image=f;
};
//---------------------------------------------------------------------------
void repere::Clean()
{  image->Canvas->Brush->Color=clWhite;
   image->Canvas->Pen->Color=clWhite;
   image->Canvas->Rectangle (0,0,image->ClientWidth,image->ClientHeight);
}
//---------------------------------------------------------------------------
void repere::DrawBox (box& P,TColor couleurin,TColor couleurout,TBrushStyle pinceau)
{  if (P.IsEmpty()) return;
   image->Canvas->Brush->Style=pinceau;
   image->Canvas->Brush->Color=couleurin;
   image->Canvas->Pen->Color=couleurout;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   image->Canvas->Rectangle (ax*P[1].inf+bx,ay*P[2].inf+by,
                            ax*P[1].sup+bx+1,ay*P[2].sup+by-1);
   //image->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon,int epais=1)
{  if (P.IsEmpty()) return;
   DrawLine(P[1].inf,P[2].inf,P[1].inf,P[2].sup,couleur,crayon,epais);
   DrawLine(P[1].inf,P[2].inf,P[1].sup,P[2].inf,couleur,crayon,epais);
   DrawLine(P[1].sup,P[2].sup,P[1].inf,P[2].sup,couleur,crayon,epais);
   DrawLine(P[1].sup,P[2].sup,P[1].sup,P[2].inf,couleur,crayon,epais);
   image->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon)
{  DrawCadre (P,couleur,crayon,1);
}
//---------------------------------------------------------------------------
void repere::DrawCircle (reel x,reel y,reel r,TColor couleurin,TColor couleurout,int epais=1)
{  image->Canvas->Pen->Color=couleurout;
   image->Canvas->Brush->Color=couleurin;
   image->Canvas->Pen->Width=epais;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
//   image->Canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
   //image->Canvas->Brush->Style = bsDiagCross;
   image->Canvas->Ellipse(ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by);
}
//---------------------------------------------------------------------------
void repere::DrawCircle (reel x,reel y,reel r,TColor couleurout,int epais=1)
{  image->Canvas->Pen->Color=couleurout;
   //image->Canvas->Brush->Color=clWhite;
   image->Canvas->Pen->Width=epais;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
//   image->Canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
   //image->Canvas->Ellipse(ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by);
   image->Canvas->Arc(ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by,ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by);
   image->Canvas->Arc(ax*(x+r)+bx,ay*(y+r)+by,ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by,ax*(x-r)+bx,ay*(y-r)+by);
}
//---------------------------------------------------------------------------
void repere::DrawEllipse (reel x,reel y,reel rx,reel ry,TColor couleurin,TColor couleurout,int epais=1)
{  image->Canvas->Pen->Color=couleurout;
   image->Canvas->Brush->Color=couleurin;
   image->Canvas->Pen->Width=1;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   image->Canvas->Ellipse(ax*(x-rx)+bx,ay*(y-ry)+by,ax*(x+rx)+bx,ay*(y+ry)+by);
}
//---------------------------------------------------------------------------
void repere::DrawEllipse2 (reel xc,reel yc,reel rx,reel ry, double theta,TColor couleur)
{  image->Canvas->Pen->Color=couleur;
   image->Canvas->Pen->Width=1;
   double t,x1,x2,x3,y1,y2,y3;
   for (t=0;t<=6.28;t=t+0.01)
   {   x1=cos(t);y1=sin(t);
       x2=rx*x1; y2=ry*y1;
       x3=cos(theta)*x2-sin(theta)*y2+xc;
       y3=sin(theta)*x2+cos(theta)*y2+yc;
       DrawPoint (x3,y3,couleur,1);
   }
}
//---------------------------------------------------------------------------
void repere::DrawPoint (reel x,reel y,TColor couleur,double epais)
{  image->Canvas->Pen->Color=couleur;
   image->Canvas->Brush->Color=couleur;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   image->Canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
}
//---------------------------------------------------------------------------
void repere::DrawPoint2 (reel x,reel y,TColor couleur,int taille)
{  image->Canvas->Pen->Color=couleur;
   image->Canvas->Pen->Width=taille;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   image->Canvas->MoveTo (ax*x+bx,ay*y+by);
   image->Canvas->LineTo (ax*x+bx+1,ay*y+by+1);
}

//---------------------------------------------------------------------------
void repere::DrawPointCadre (reel x,reel y,TColor couleur,double taillex,double tailley)
{  box B(2);
   B[1]=interval(x-taillex,x+taillex);
   B[2]=interval(y-tailley,y+tailley);
   DrawCadre (B,couleur,psSolid,1);
}


//---------------------------------------------------------------------------
void repere::DrawLine (reel x1,reel y1,reel x2, reel y2,TColor couleur,
                       TPenStyle crayon,int taille)
{  image->Canvas->Pen->Color=couleur;
   image->Canvas->Pen->Style=crayon;
   image->Canvas->Pen->Width=taille;
   float ax=image->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=image->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   image->Canvas->MoveTo (ax*x1+bx,ay*y1+by);
   if (fabs(ax*x2+bx)+fabs(ay*y2+by)<10000)
   {
      image->Canvas->LineTo (ax*x2+bx,ay*y2+by);
   };
   image->Canvas->Pen->Width=1;
}
//---------------------------------------------------------------------------
void repere::DrawPolygon(reel* xa,reel* ya,int imin,int imax, TColor c)
{   POINT points[14];
    float ax=image->ClientWidth/(Width(interval_x));
    float bx=-ax*interval_x.inf;
    float ay=image->ClientHeight/(-Width(interval_y));
    float by=-ay*interval_y.sup;
    for (int i=0; i<=imax-imin;i++)
    {   reel x1=xa[i+imin];
        reel y1=ya[i+imin];
        points[i] = Point(ax*x1+bx,ay*y1+by);
    }
    //for (int i=imax-imin+1;i<=100-1;i++)
    //{   reel xai=xa[i+imin];
    //    reel yai=ya[i+imin];
    //    points[i] = Point(xa[imin],ya[imin]);}
    image->Canvas->Brush->Color = c;
    image->Canvas->Pen->Color = clBlack;
    //image->Canvas->Polygon(points,13);
}
//---------------------------------------------------------------------------
void repere::DrawGrid (TColor couleur, TPenStyle crayon=psDash , int epais=1, double da=1.0, bool texte=false)
{  int a=da*INT(interval_x.inf/da);
   while (a<interval_x.sup)
    { DrawLine(a,interval_y.inf,a,interval_y.sup,couleur,crayon,epais);
      if (texte) DrawText (a,interval_y.sup,IntToStr(a));
      a=a+da;
    };
   a=da*INT(interval_y.inf/da);
   while (a<interval_y.sup)
    {  DrawLine(interval_x.inf,a,interval_x.sup,a,couleur,crayon,epais);
       if (texte) DrawText (interval_x.inf,a,IntToStr(a));
       a=a+da;
    };
};
//---------------------------------------------------------------------------
void repere::DrawBox (box& P,TColor couleurin,TColor couleurout,TBrushStyle pinceau,int i1,int i2)
{ if (P.IsEmpty()) return;
  box Q(2);  Q[1]=P[i1];  Q[2]=P[i2];
  DrawBox (Q,couleurin,couleurout,pinceau);
}
//---------------------------------------------------------------------------
void repere::DrawData (box& Y,box& t,TColor couleur,reel epais)
{ if (Y.IsEmpty()||t.IsEmpty()) return;
  box Q(2);
  for (int j=1;j<=Y.dim;j++)
  {  Q[1]=t[j];  Q[2]=Y[j];
     Q=Inflate(Q,epais);
     DrawBox (Q,couleur,couleur,bsSolid);
  }
  DrawLine(interval_x.inf,0,interval_x.sup,0,clBlack,psSolid,1);
  DrawLine(0,interval_y.inf,0,interval_y.sup,clBlack,psSolid,1);
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon,int i1,int i2,int epais=1)
{ if (P.IsEmpty()) return;
  box Q(2);
  Q[1]=P[i1]; Q[2]=P[i2];  DrawCadre (Q,couleur,crayon,epais);
}
//---------------------------------------------------------------------------
void repere::DrawText (double x,double y,const AnsiString Text)
{   float ax=image->ClientWidth/(Width(interval_x));
    float bx=-ax*interval_x.inf;
    float ay=image->ClientHeight/(-Width(interval_y));
    float by=-ay*interval_y.sup;
    image->Canvas->Brush->Color=clWhite;
    image->Canvas->Font->Color = clBlue;
    //image->Canvas->Font->Size=20;
    image->Canvas->TextOut(ax*x+bx,ay*y+by, Text);
}
//---------------------------------------------------------------------------
void repere::ChangementRepere(int x_pixel,int y_pixel,double* x, double* y)
{       *x = interval_x.inf + ((double)x_pixel/(image->ClientWidth))*(Width(interval_x));
        *y = interval_y.sup - ((double)y_pixel/(image->ClientHeight))*(Width(interval_y));
}
//---------------------------------------------------------------------------
void repere::DrawWordFrame (box& P,TColor couleur,TPenStyle crayon,int epais=1)
{  if (P.IsEmpty()) return;
   DrawLine(P[1].inf,0,P[1].sup,0,couleur,crayon,epais);
   DrawLine(0,P[2].inf,0,P[2].sup,couleur,crayon,epais);
   image->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawWordFrame (box& P,TColor couleur,TPenStyle crayon)
{  DrawWordFrame (P,couleur,crayon,1);
}
//----------------------------------------------------------------------------
