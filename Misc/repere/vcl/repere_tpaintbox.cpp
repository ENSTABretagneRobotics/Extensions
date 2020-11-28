//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "repere.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


repere::repere ()
{};
//---------------------------------------------------------------------------
repere::repere (TPaintBox* f,reel xmin,reel xmax,reel ymin,reel ymax)
{       if (xmin==xmax)    xmax=2*xmin; //code faux temporaire
        if (ymin==ymax)    ymax=2*ymin; //code faux temporaire
        interval_x=interval(xmin,xmax);
        interval_y=interval(ymin,ymax);
	paintBox=f;
};
//---------------------------------------------------------------------------
void repere::Clean()
{  paintBox->Canvas->Brush->Color=clWhite;
   paintBox->Canvas->Pen->Color=clWhite;
   paintBox->Canvas->Rectangle (0,0,paintBox->ClientWidth,paintBox->ClientHeight);
}
//---------------------------------------------------------------------------
void repere::DrawBox (box& P,TColor couleurin,TColor couleurout,TBrushStyle pinceau)
{  if (P.IsEmpty()) return;
   paintBox->Canvas->Brush->Style=pinceau;
   paintBox->Canvas->Brush->Color=couleurin;
   paintBox->Canvas->Pen->Color=couleurout;
   float ax=paintBox->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=paintBox->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   paintBox->Canvas->Rectangle((int)(ax*P[1].inf+bx)-1,(int)(ay*P[2].inf+by)+1,
							(int)(ax*P[1].sup+bx)+1,(int)(ay*P[2].sup+by)-1);
   //paintBox->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon,int epais=1)
{  if (P.IsEmpty()) return;
   DrawLine(P[1].inf,P[2].inf,P[1].inf,P[2].sup,couleur,crayon,epais);
   DrawLine(P[1].inf,P[2].inf,P[1].sup,P[2].inf,couleur,crayon,epais);
   DrawLine(P[1].sup,P[2].sup,P[1].inf,P[2].sup,couleur,crayon,epais);
   DrawLine(P[1].sup,P[2].sup,P[1].sup,P[2].inf,couleur,crayon,epais);
   paintBox->Refresh();
}
//---------------------------------------------------------------------------
void repere::DrawCadre (box& P,TColor couleur,TPenStyle crayon)
{  DrawCadre (P,couleur,crayon,1);
}
//---------------------------------------------------------------------------
void repere::DrawCircle (reel x,reel y,reel r,TColor couleurin,TColor couleurout,int epais=1)
{  paintBox->Canvas->Pen->Color=couleurout;
   paintBox->Canvas->Brush->Color=couleurin;
   paintBox->Canvas->Pen->Width=epais;
   float ax=paintBox->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=paintBox->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
//   paintBox->Canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
   paintBox->Canvas->Ellipse(ax*(x-r)+bx,ay*(y-r)+by,ax*(x+r)+bx,ay*(y+r)+by);
}
//---------------------------------------------------------------------------
void repere::DrawEllipse (reel x,reel y,reel rx,reel ry,TColor couleurin,TColor couleurout,int epais=1)
{  paintBox->Canvas->Pen->Color=couleurout;
   paintBox->Canvas->Brush->Color=couleurin;
   paintBox->Canvas->Pen->Width=1;
   float ax=paintBox->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=paintBox->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   paintBox->Canvas->Ellipse(ax*(x-rx)+bx,ay*(y-ry)+by,ax*(x+rx)+bx,ay*(y+ry)+by);
}
//---------------------------------------------------------------------------
void repere::DrawPoint (reel x,reel y,TColor couleur,double epais)
{  paintBox->Canvas->Pen->Color=couleur;
   paintBox->Canvas->Brush->Color=couleur;
   float ax=paintBox->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=paintBox->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   paintBox->Canvas->Ellipse(ax*x+bx-epais,ay*y+by-epais,ax*x+bx+epais,ay*y+by+epais);
}
//---------------------------------------------------------------------------
void repere::DrawPoint2 (reel x,reel y,TColor couleur,int taille)
{  paintBox->Canvas->Pen->Color=couleur;
   paintBox->Canvas->Pen->Width=taille;
   float ax=paintBox->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=paintBox->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   paintBox->Canvas->MoveTo (ax*x+bx,ay*y+by);
   paintBox->Canvas->LineTo (ax*x+bx+1,ay*y+by+1);
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
{  paintBox->Canvas->Pen->Color=couleur;
   paintBox->Canvas->Pen->Style=crayon;
   paintBox->Canvas->Pen->Width=taille;
   float ax=paintBox->ClientWidth/(Width(interval_x));
   float bx=-ax*interval_x.inf;
   float ay=paintBox->ClientHeight/(-Width(interval_y));
   float by=-ay*interval_y.sup;
   paintBox->Canvas->MoveTo (ax*x1+bx,ay*y1+by);
   if (fabs(ax*x2+bx)+fabs(ay*y2+by)<10000)
   {
      paintBox->Canvas->LineTo (ax*x2+bx,ay*y2+by);
   };
   paintBox->Canvas->Pen->Width=1;
}
//---------------------------------------------------------------------------
void repere::DrawPolygon(reel* xa,reel* ya,int imin,int imax, TColor c)
{   POINT points[14];
    float ax=paintBox->ClientWidth/(Width(interval_x));
    float bx=-ax*interval_x.inf;
    float ay=paintBox->ClientHeight/(-Width(interval_y));
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
    paintBox->Canvas->Brush->Color = c;
    paintBox->Canvas->Pen->Color = clBlack;
    //paintBox->Canvas->Polygon(points,13);
}
//---------------------------------------------------------------------------
void repere::DrawGrid (TColor couleur, TPenStyle crayon=psDash , int epais=1, double da=1.0, bool texte=false)
{  int a=INT(interval_x.inf);
   while (a<interval_x.sup)
    { DrawLine(a,interval_y.inf,a,interval_y.sup,couleur,crayon,epais);
      if (texte) DrawText (a,interval_y.sup,IntToStr(a));
      a=a+da;
    };
   a=INT(interval_y.inf);
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
{   float ax=paintBox->ClientWidth/(Width(interval_x));
    float bx=-ax*interval_x.inf;
    float ay=paintBox->ClientHeight/(-Width(interval_y));
    float by=-ay*interval_y.sup;
    paintBox->Canvas->Brush->Color=clWhite;
    paintBox->Canvas->Font->Color = clBlue;
    paintBox->Canvas->TextOut(ax*x+bx,ay*y+by, Text);
}
//---------------------------------------------------------------------------
