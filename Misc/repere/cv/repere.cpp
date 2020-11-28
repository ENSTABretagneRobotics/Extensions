#include "repere.h"

repere::repere (){}

int repere::xToPixel(double x){
	//scaling
	return (int)(xscale*(x-xmin));	
}
int repere::yToPixel(double y){
	//scaling
	return (int)(height-yscale*(y-ymin));	
}
int repere::rToPixel(double r){
	//scaling
	return (int)(scale*r);
}

double repere::pixelToX(int x){
	//scaling
	return (double)x/(double)xscale+xmin;	
}
double repere::pixelToY(int y){
	//scaling
	return (double)(height-y)/(double)xscale+ymin;	
}
double repere::pixelToR(int r){
	//scaling
	return (double)r/(double)scale;
}
//-------------------------------------------------------------------------------
void repere::init(double xmin,double xmax,double ymin,double ymax,IplImage* img,bool adapt_to_IplImage){
	this->xmax=xmax;this->xmin=xmin;this->ymax=ymax;this->ymin=ymin;
	image=img;
	this->width= image->width;
	this->height= image->height;
	if(adapt_to_IplImage){
		xscale = width/(xmax-xmin);
		yscale = height/(ymax-ymin);
		scale = (height/(ymax-ymin)+width/(xmax-xmin))/2;
	}
	else{
		scale = std::min(height/(ymax-ymin),width/(xmax-xmin));
		xscale = scale;
		yscale = scale;
	}
	image_created = false;
	this->adapt_to_IplImage = adapt_to_IplImage;//for info

}
//-------------------------------------------------------------------------------
repere::repere (double xmin,double xmax,double ymin,double ymax,IplImage* img,bool adapt_to_IplImage){
	init(xmin,xmax,ymin,ymax,img,adapt_to_IplImage);
}
//-------------------------------------------------------------------------------
repere::repere (double xmin,double xmax,double ymin,double ymax,int width,int height,bool adapt_to_IplImage){
	image = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 3);
	init(xmin,xmax,ymin,ymax,image,adapt_to_IplImage);//image_created=false
	image_created = true;
}
//-------------------------------------------------------------------------------
void repere::set_image(IplImage* img){
	image = img;
	this->width= image->width;
	this->height= image->height;
	scale = std::min(height/(ymax-ymin),width/(xmax-xmin));

}
//-------------------------------------------------------------------------------
void repere::set_image_copy(IplImage* img){
	cvResize(img,image);
}
//-------------------------------------------------------------------------------
void repere::Clean(){
	cvSet(image, CV_RGB(255,255,255));
}
//-------------------------------------------------------------------------------
void repere::save(char* filename){
   cvSaveImage(filename,image);
}
////-------------------------------------------------------------------------------
///*___________________________________________________________________________
//_____________BOX DRAW______________________________________________________*/
void repere::DrawSubBox (box& P,int color_out,int color_in,int line_type,int thickness,int index1,int index2){//root function
	DrawFilledRectangle (P[index1].inf,P[index1].sup,P[index2].inf,P[index2].sup,color_out,color_in,line_type,thickness);
}	
void repere::DrawBox (box& P,int color_out,int color_in,int line_type,int thickness){
	DrawSubBox (P,color_out,color_in,line_type,thickness,1,2);
}
////-------------------------------------------------------------------------------
void repere::DrawSubBox (box& P,int color_out,int color_in,int thickness,int index1,int index2){
	DrawSubBox (P,color_out,color_in,8,thickness,index1,index2);
}
void repere::DrawBox (box& P,int color_out,int color_in,int thickness){
	DrawSubBox (P,color_out,color_in,8,thickness,1,2);
}
////-------------------------------------------------------------------------------
void repere::DrawSubBox (box& P,int color_out,int color_in,int index1,int index2){
	DrawSubBox (P,color_out,color_in,8,1,index1,index2);
}
void repere::DrawBox (box& P,int color_out,int color_in){
    DrawSubBox (P,color_out,color_in,8,1,1,2);
}
////-------------------------------------------------------------------------------
///*___________________________________________________________________________
//_____________CADRE DRAW____________________________________________________*/
void repere::DrawSubCadre (box& P,int color,int line_type,int thickness,int index1,int index2){//root function
	DrawRectangle (P[index1].inf,P[index1].sup,P[index2].inf,P[index2].sup,color,line_type,thickness);
}
void repere::DrawCadre (box& P,int color,int line_type,int thickness){
    DrawSubCadre (P,color,line_type,thickness,1,2);
}
////-------------------------------------------------------------------------------	
void repere::DrawSubCadre (box& P,int color,int thickness,int index1,int index2){
	DrawSubCadre (P,color,8,thickness,index1,index2);
}
void repere::DrawCadre (box& P,int color,int thickness){
	DrawSubCadre (P,color,8,thickness,1,2);
}
////-------------------------------------------------------------------------------
void repere::DrawSubCadre (box& P,int color,int index1,int index2){
    DrawSubCadre (P,color,1,1,index1,index2);
}
void repere::DrawCadre (box& P,int color){
    DrawSubCadre (P,color,1,1,1,2);
}
////-------------------------------------------------------------------------------
/*___________________________________________________________________________
_____________OTHER DRAWING FUNCTIONS_______________________________________*/

///___________________________________________________________________________________________________
void repere::DrawPoint (double x1,double y1,int color,int thickness){
  double point_radius = thickness/scale;
  DrawDisk (x1,y1,point_radius,color,color,8,thickness);
	//DrawDisk (x1,y1,point_radius,color,color,8,1);
}
///___________________________________________________________________________________________________
///___________________________________________________________________________________________________
void repere::DrawLine (double x1,double y1,double x2,double y2,int color,int line_type,int thickness){
    CvPoint A,B;
    A.x= xToPixel(x1);B.x= xToPixel(x2);
    A.y= yToPixel(y1);B.y= yToPixel(y2);
    cvLine(image, A, B,IntToRGB(color), thickness, line_type, 0 );
}
//------------------------------------------------------------------------------------------------------
void repere::DrawLine (double x1,double y1,double x2,double y2,int color,int thickness){
    DrawLine (x1,y1,x2,y2,color,8,thickness);
}
//------------------------------------------------------------------------------------------------------
void repere::DrawLine (double a,double b,int color,int thickness){
	//y = a*x+b, we draw it for xmin and xmax
	double yline_max = a*xmax+b;
	double yline_min = a*xmin+b;
    DrawLine (xmin,yline_min,xmax,yline_max,color,8,thickness);
}
///___________________________________________________________________________________________________
///___________________________________________________________________________________________________
void repere::DrawDisk (double x,double y,double r,int color_out,int color_in,int line_type,int thickness){
    CvPoint center;
    center.x = xToPixel(x); center.y = yToPixel(y);int radius =rToPixel(r);
    //inner disc
	cvCircle(image, center, (int)radius,IntToRGB(color_in), thickness, CV_FILLED, 0 );
    //outer circle
    cvCircle(image, center, (int)radius,IntToRGB(color_out), thickness, line_type, 0 );
	
}
//------------------------------------------------------------------------------------------------------
void repere::DrawDisk (double x,double y,double r,int color_out,int color_in,int thickness){
	DrawDisk (x,y,r,color_out,color_in,8,thickness);
}
//------------------------------------------------------------------------------------------------------
void repere::DrawDisk (double x,double y,double r,int color_out,int color_in){
    DrawDisk (x,y,r,color_out,color_in,8,1);
}
///___________________________________________________________________________________________________
///___________________________________________________________________________________________________
void repere::DrawCircle (double x,double y,double r,int color,int line_type,int thickness){//root function
    CvPoint center;
    center.x =xToPixel(x); center.y = yToPixel(y);int radius = rToPixel(r);
    cvCircle(image, (CvPoint)center, (int)radius,IntToRGB(color), thickness, (int) line_type, 0 );
}
//-------------------------------------------------------------------------------
void repere::DrawCircle (double x,double y,double r,int color,int thickness){
	DrawCircle (x,y,r,color,8,thickness);
}
//-------------------------------------------------------------------------------
void repere::DrawCircle (double x,double y,double r,int color){
    DrawCircle (x,y,r,color,8,1);
}
///___________________________________________________________________________________________________
///___________________________________________________________________________________________________
void repere::DrawFilledRectangle (double xmin,double xmax,double ymin,double ymax,int color_out,int color_in,int line_type,int thickness){
	CvPoint A,B;
	A.x=xToPixel(xmin);A.y=yToPixel(ymin);B.x=xToPixel(xmax);B.y=yToPixel(ymax);
	//filled rectangle thickness negative
	cvRectangle(image,A,B,IntToRGB(color_in),-1,line_type,0);	
	//normal rectangle
	cvRectangle(image,A,B,IntToRGB(color_out),thickness,line_type,0);
}
//-------------------------------------------------------------------------------
void repere::DrawFilledRectangle (double xmin,double xmax,double ymin,double ymax,int color_out,int color_in,int thickness){
	DrawFilledRectangle (xmin,xmax,ymin,ymax,color_out,color_in,8,thickness);
}
//-------------------------------------------------------------------------------
void repere::DrawFilledRectangle (double xmin,double xmax,double ymin,double ymax,int color_out,int color_in){
	DrawFilledRectangle (xmin,xmax,ymin,ymax,color_out,color_in,8,1);
}
///___________________________________________________________________________________________________
///___________________________________________________________________________________________________
void repere::DrawRectangle (double xmin,double xmax,double ymin,double ymax,int color,int line_type,int thickness){
	CvPoint A,B;
	A.x=xToPixel(xmin);A.y=yToPixel(ymin);B.x=xToPixel(xmax);B.y=yToPixel(ymax);
	cvRectangle(image,A,B,IntToRGB(color),thickness,line_type,0);
}
//-------------------------------------------------------------------------------
void repere::DrawRectangle(double xmin,double xmax, double ymin,double ymax,int color, int thickness ){
	DrawRectangle (xmin,xmax,ymin,ymax,color,8,thickness);
}
//-------------------------------------------------------------------------------
void repere::DrawRectangle (double xmin,double xmax,double ymin,double ymax,int color){
	DrawRectangle (xmin,xmax,ymin,ymax,color,8,1);
}
//-------------------------------------------------------------------------------
void repere::DrawRectangle2(double x, double y,double width, double height)
{
	CvPoint down,up;
    down.x = xToPixel(x); down.y = yToPixel(y);up.x = xToPixel(x+width);
	up.y=yToPixel(y+height);
	cvRectangle(image,down,up,CV_RGB(0,0,0),-1);
}
//-------------------------------------------------------------------------------
void repere::DrawText (double x,double y,const char* text,int thickness){
    CvPoint org;
    org.x = xToPixel(x);org.y = yToPixel(y);
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0f, 1.0f, 1.0f, thickness, 8 );
    CvScalar color = CV_RGB(0,0,0);//Black??
    cvPutText(image, text, org, &font, color);
}
//-------------------------------------------------------------------------------
void repere::DrawCross(double x,double y,double size,int color,int thickness){
	DrawLine(x,y,x,y+size,color,thickness);
	DrawLine(x,y,x-size,y,color,thickness);
	DrawLine(x,y,x,y-size,color,thickness);
	DrawLine(x,y,x+size,y,color,thickness);
}
//-------------------------------------------------------------------------------
void repere::DrawXCross(double x,double y,double size,int color,int thickness){
	DrawLine(x,y,x+size,y+size,color,thickness);
	DrawLine(x,y,x-size,y-size,color,thickness);
	DrawLine(x,y,x+size,y-size,color,thickness);
	DrawLine(x,y,x-size,y+size,color,thickness);
}
/*___________________________________________________________________________
_____________USEFUL FUNCTIONS______________________________________________*/
//useful functions
void repere::ChangementRepere(int x_pixel,int y_pixel,double* x, double* y)
{       *x = xmin + ((double)x_pixel/(image->width))*(abs(xmax-xmin));
        *y = ymin - ((double)y_pixel/(image->height))*(abs(ymax-ymin));
}
//VCL Interface  ????
//vcl_update(TImage*);
//-------------------------------------------------------------------------------
CvScalar repere::IntToRGB(int color){
	int B = (int)(color/(256*256));
	int G = (int)((color-B*256*256)/256);
	int R = (int)(color-B*256*256-G*256);
	return CV_RGB(R,G,B);
}
