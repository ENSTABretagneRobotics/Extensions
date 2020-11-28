#include "repere.h"
#include <QDebug>

using namespace std;

repere::repere(QObject *parent) :
    QObject(parent)
{
}
//--------------------------------------------------------------------------------------------------
repere::repere(QObject *parent,QGraphicsView* G,double xmin1, double xmax1,double ymin1, double ymax1) :
    QObject(parent)
{    Scene=new QGraphicsScene(this);
     G->setScene(Scene);
     xmin=xmin1; xmax=xmax1; ymin=ymin1; ymax=ymax1;
     Scene->setSceneRect(0,0,G->geometry().width()-3,G->geometry().height()-3);
     DrawBox(xmin,xmax,ymin,ymax,QPen(Qt::red),QBrush(Qt::NoBrush));
}
//--------------------------------------------------------------------------------------------------
double repere::xToPix(double x)
{   double echx = Scene->width()/(xmax-xmin);
    return (x-xmin)*echx;
}
//--------------------------------------------------------------------------------------------------
double repere::yToPix(double y)
{
    double echy = Scene->height()/(ymax-ymin);
    return Scene->height()-(y-ymin)*echy;
}
//--------------------------------------------------------------------------------------------------
void repere::Center(double x1,double y1)
{   double Rx=(xmax-xmin)/2.0;
    double Ry=(ymax-ymin)/2.0;
    xmin=x1-Rx;    xmax=x1+Rx;
    ymin=y1-Ry;    ymax=y1+Ry;
}
//--------------------------------------------------------------------------------------------------
void repere::Zoom(double z)
{   double rx=(xmax-xmin)/2.0;
    double ry=(ymax-ymin)/2.0;
    double cx=(xmax+xmin)/2.0;
    double cy=(ymax+ymin)/2.0;
    xmin=cx-rx*z;    xmax=cx+rx*z;
    ymin=cy-ry*z;    ymax=cy+ry*z;
}
//--------------------------------------------------------------------------------------------------
void repere::Clean()
{
    Scene->clear();
}
//--------------------------------------------------------------------------------------------------
void repere::DrawBox(double xmin,double xmax,double ymin,double ymax, QPen pen1, QBrush brush1)
{       if (isnan(xmin)||isnan(xmax)||isnan(ymin)||isnan(ymax)) return;
        QPolygonF box1;
        box1 << QPointF(xToPix(xmin),yToPix(ymin))<< QPointF(xToPix(xmax),yToPix(ymin))
             << QPointF(xToPix(xmax),yToPix(ymax))<< QPointF(xToPix(xmin),yToPix(ymax));
        pen1.setWidth(1);
        Scene->addPolygon(box1,pen1,brush1);
        Scene->update();
}
//--------------------------------------------------------------------------------------------------
void repere::DrawBoxDiff(double xmin,double xmax,double ymin,double ymax,double amin,double amax,double bmin,double bmax, QPen pen1, QBrush brush1)
{       if (isnan(amin)||isnan(amax)||isnan(bmin)||isnan(bmax))
              {DrawBox(xmin,xmax,ymin,ymax, pen1, brush1); return;}
        QPolygonF box1,box2;
        box1 << QPointF(xToPix(xmin),yToPix(ymin))<< QPointF(xToPix(xmax),yToPix(ymin))
             << QPointF(xToPix(amax),yToPix(bmin))<< QPointF(xToPix(amin),yToPix(bmin))
             << QPointF(xToPix(amin),yToPix(bmax))<< QPointF(xToPix(amax),yToPix(bmax))
             << QPointF(xToPix(amax),yToPix(bmin))<< QPointF(xToPix(xmax),yToPix(ymin))
             << QPointF(xToPix(xmax),yToPix(ymax))<< QPointF(xToPix(xmin),yToPix(ymax));
        Scene->addPolygon(box1,QPen(Qt::NoPen),brush1);//QPen(Qt::blue),QBrush(Qt::darkBlue)
        pen1.setWidth(1);
        box2 << QPointF(xToPix(xmin),yToPix(ymin))<< QPointF(xToPix(xmax),yToPix(ymin))
             << QPointF(xToPix(xmax),yToPix(ymax))<< QPointF(xToPix(xmin),yToPix(ymax));
        Scene->addPolygon(box2,pen1,QBrush(Qt::NoBrush));
        Scene->update();
 }
//--------------------------------------------------------------------------------------------------
void repere::DrawArrow(double x1,double y1,double dx,double dy, double r, QPen pen1)
{       double x2=x1+dx;
        double y2=y1+dy;
        double a=3.14-(3.14/4);
        double pixx1=xToPix(x1);
        double pixy1=yToPix(y1);
        double pixx2=xToPix(x2);
        double pixy2=yToPix(y2);
        double pixdx=pixx2-pixx1;
        double pixdy=pixy2-pixy1;
        double px=pixx2+r*(cos(a)*pixdx-sin(a)*pixdy);    // coté de pointe
        double py=pixy2+r*(sin(a)*pixdx+cos(a)*pixdy);
        double qx=pixx2+r*(cos(-a)*pixdx-sin(-a)*pixdy);  // autre coté de pointe
        double qy=pixy2+r*(sin(-a)*pixdx+cos(-a)*pixdy);
        Scene->addLine(pixx1,pixy1,pixx2,pixy2,pen1);
        Scene->addLine(pixx2,pixy2,px,py,pen1);
        Scene->addLine(pixx2,pixy2,qx,qy,pen1);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawAxis(QPen pen1)
{   double x1=xmin;
    double y1=ymin;
    double dx=xmax-xmin;
    double dy=ymax-ymin;
    DrawArrow(x1,0,dx,0,0.02, pen1);
    DrawArrow(0,y1,0,dy,0.02, pen1);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawData(vector<double> T, vector<double> Ymin, vector<double> Ymax,QPen pen1)
{       pen1.setWidth(3);
        for (uint k=0;k<T.size();k++)
           DrawLine(T[k],Ymin[k],T[k],Ymax[k], pen1);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawEllipse(double cx, double cy, double r, QPen pen1, QBrush brush1)
{
     Scene->addEllipse(xToPix(cx-r),yToPix(cy+r),xToPix(cx+r)-xToPix(cx-r),yToPix(cy-r)-yToPix(cy+r),pen1,brush1);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawLine(double x1,double y1,double x2,double y2, QPen pen1)
{       Scene->addLine(xToPix(x1),yToPix(y1),xToPix(x2),yToPix(y2),pen1);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawPolygone(double x,double y,double theta,vector<double> X, vector<double> Y, QPen pen1, QBrush brush1)
{       QPolygonF poly1;
        for (unsigned int k=0;k<X.size();k++)
        {
            double x1=x+cos(theta)*X[k]-sin(theta)*Y[k];
            double y1=y+sin(theta)*X[k]+cos(theta)*Y[k];
            poly1 << QPointF(xToPix(x1),yToPix(y1));
        }
        Scene->addPolygon(poly1,pen1,brush1);
 }
//--------------------------------------------------------------------------------------------------
void repere::DrawRobot(double x,double y,double theta, double s)
{   vector<double> X,Y;
    X.push_back(0*s); Y.push_back(-1*s);
    X.push_back(3*s); Y.push_back(0*s);
    X.push_back(0*s); Y.push_back(1*s);
    DrawPolygone(x,y,theta,X,Y,QPen(Qt::blue),QBrush(Qt::black));
}
//--------------------------------------------------------------------------------------------------
void repere::DrawSailboat(double x,double y,double theta,QColor colr,double deltag,QColor colg, double deltav,QColor colv)

{   double a=0.8;
    vector<double> Xc,Yc;                //coque
    Xc.push_back(-a);  Yc.push_back(-a);
    Xc.push_back(4*a); Yc.push_back(0);
    Xc.push_back(-a);  Yc.push_back(a);
    Xc.push_back(-a);  Yc.push_back(-a);
    DrawPolygone(x,y,theta,Xc,Yc,colr, colr);

    vector<double> Xr,Yr;  //gouvernail
    Xr.push_back(-2*a);  Yr.push_back(0);
    Xr.push_back(0);   Yr.push_back(0);
    DrawPolygone(x-a*cos(theta),y-a*sin(theta),theta+deltag,Xr,Yr,QPen(colg),QBrush(colg));

    vector<double> Xv,Yv;  //voile
    Xv.push_back(-5*a);  Yv.push_back(0);
    Xv.push_back(0);     Yv.push_back(0);
    DrawPolygone(x+3*a*cos(theta),y+3*a*sin(theta),theta+deltav,Xv,Yv,colv,colv);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawText(QString s, int n)
{       for (int k=1;k<=n;k++)
        s="\r\n"+s;
        //Pour la syntaxe:  int a; double p; s=QString("a=%1,\r\n p=%2").arg(k).arg(p);
        Scene->addText(s);
}
//--------------------------------------------------------------------------------------------------
void repere::Save(QString nom)
{
    QImage *image = new QImage(QSize(1000,1000),QImage::Format_ARGB32);
    image->fill(QColor(Qt::white).rgb());
    QPainter *pngPainter = new QPainter(image);
    pngPainter->setRenderHint(QPainter::Antialiasing);
    Scene->render(pngPainter);
    pngPainter->end();
    image->save(nom+".png","PNG",100);
}
//--------------------------------------------------------------------------------------------------
/*void repere::drawMap(Map *map)
{
    for(uint i = 0; i < map->murs_xa.size(); i++){
        Scene->addLine(xToPix(map->murs_xa[i]),yToPix(map->murs_ya[i]),xToPix(map->murs_xb[i]),yToPix(map->murs_yb[i]),QPen(Qt::red));
    }
    for(uint i = 0; i < map->cercles_r.size(); i++){
        DrawEllipse(map->cercles_x[i],map->cercles_y[i],map->cercles_r[i],QPen(Qt::red), QBrush(Qt::NoBrush));
    }
}*/
//--------------------------------------------------------------------------------------------------
void repere::drawMap(const vector<double> &murs_xa, const vector<double> &murs_ya, const vector<double> &murs_xb, const vector<double> &murs_yb )
{
    for(uint i = 0; i < murs_xa.size(); i++){
        Scene->addLine(xToPix(murs_xa[i]),yToPix(murs_ya[i]),xToPix(murs_xb[i]),yToPix(murs_yb[i]),QPen(Qt::red));
    }
}
//--------------------------------------------------------------------------------------------------
void repere::mouseMoveEvent(QMouseEvent *event)
{
   double x = event->x();//Recuperer les coordonnees de la souris dans widgetCameleon
   double y = event->y();
   qDebug() << "repere x = " << (x) << " y = " << (y);//hasMouseTracking();
   //emit drawArtRob(xPixToX(x),yPixToY(y));
}
//--------------------------------------------------------------------------------------------------
