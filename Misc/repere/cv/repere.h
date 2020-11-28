
#ifndef REPERE_H
#define REPERE_H

#ifdef _MSC_VER
// Disable some Visual Studio warnings that happen in OpenCV.
#pragma warning(disable : 4100) 
#pragma warning(disable : 4996)
#endif // _MSC_VER

// OpenCV headers.
#ifdef OPENCV220
#include "opencv/highgui.h"
// min and max seem to be undefined by OpenCV 2.2.0 so we need to redefine it here...
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif // max
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif // min
#else
#include "cv.h"
#include "cvaux.h"
#include "highgui.h"
#endif //OPENCV220

#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled for OpenCV.
#pragma warning(default : 4100) 
#pragma warning(default : 4996)
#endif // _MSC_VER

#include "../interval/box.h"

class repere
{
public:
	static const int BLACK = 0;
	static const int VERYDARKGRAY = 50+75*256+75*256*256;
	static const int DARKGRAY = 100+100*256+100*256*256;
	static const int GRAY = 150+150*256+150*256*256;
	static const int LIGHTGRAY = 200+200*256+200*256*256;
	static const int WHITE = 255+255*256+255*256*256;
	static const int RED = 255;
	static const int LIGHTGRAYRED = 255+100*256+100*256*256;
	static const int CHERRY = 150;
	static const int GREEN = 255*256;
	static const int BLUE = 255*256*256;
	static const int YELLOW = 255+255*256;
	static const int MAGENTA = 255+255*256*256;
	static const int CYAN = 255*256+255*256*256;
	static const int LIGHTROSE = 243+199*256+206*256*256;
	static const int LIGHTROSE2 = 230+136*256+152*256*256;
	static const int SKIN = 249+185*256+115*256*256;
	static const int MILDGREEN = 173+244*256+9*256*256;
	static const int DARKGREEN = 13+142*256+22*256*256;


	double xmin,xmax,ymin,ymax;
	IplImage* image;
	double scale,xscale,yscale;
	int height,width;
	bool adapt_to_IplImage;
	bool image_created;
public:
	//Core functions
	
	repere (double xmin,double xmax,double ymin,double ymax,IplImage* img,bool adapt_to_IplImage=false);
	repere (double xmin,double xmax,double ymin,double ymax,int width,int height,bool adapt_to_IplImage=false);
	repere (double xmin,double xmax,double ymin,double ymax,double scale);
	repere ();

	void init(double xmin,double xmax,double ymin,double ymax,IplImage* img,bool adapt_to_IplImage);

	void set_image(IplImage* img);
	void set_image_copy(IplImage* img);

	//inner useful functions
	int xToPixel(double x);
	int yToPixel(double y);
	int rToPixel(double r);
    
	double pixelToX(int x);
	double pixelToY(int y);
	double pixelToR(int r);

	//convert hsv to rgb
	static void hsvToRGB(double h,double s,double v, int &r,int &g, int &b){
		//Convert HSV color space to RGB color space
		//@param h: Hue 0-->360deg
		//@param s: Saturation 0-->1
		//@param v: Value 0-->1

		int hi = ((int)(h / 60.0)) % 6;
		double f =  (h / 60.0) - (int)(h / 60.0);
		double p = v * (1.0 - s);
		double q = v * (1.0 - (f*s));
		double t = v * (1.0 - ((1.0 - f) * s));
		switch(hi) {
			case 0: r=(int)(255*v);g=(int)(255*t);b=(int)(255*p);break;
			case 1: r=(int)(255*q);g=(int)(255*v);b=(int)(255*p);break;
			case 2: r=(int)(255*p);g=(int)(255*v);b=(int)(255*t);break;
			case 3: r=(int)(255*p);g=(int)(255*q);b=(int)(255*v);break;
			case 4: r=(int)(255*t);g=(int)(255*p);b=(int)(255*v);break;
			case 5: r=(int)(255*v);g=(int)(255*p);b=(int)(255*q);break;
		}
	}
	//convert double to matlab colors range (blue --> red) 
	static int matlabColor(double color,double range){
		double h = 200-200*color/range;double s = 1;double v = 1;
		int r,g,b;
		hsvToRGB(h,s,v,r,g,b);
		return r+g*256+b*256*256;
	}
	//
	static void matlabColors(double color,double range,int &r,int &g, int &b){
		double h = 200-200*color/range;double s = 1;double v = 1;
		hsvToRGB(h,s,v,r,g,b);
	}

	static int grayscaleColor(double color,double range){
		double c = 1-color/range;
		int int_coef = (int)(c*255);
		int res = int_coef+int_coef*256+int_coef*256*256;
		return res;
	}

	//user functions
	void Clean();
	void save(char* filename);
	//BOX DRAW
	void DrawSubBox (box& P,int color_out,int color_in,int line_type,int thickness,int index1,int index2);//root function
	void DrawBox (box& P,int color_out,int color_in,int line_type,int thickness);
	
	void DrawSubBox (box& P,int color_out,int color_in,int thickness,int index1,int index2);
	void DrawBox (box& P,int color_out,int color_in,int thickness);
	
	void DrawSubBox (box& P,int color_out,int color_in,int index1,int index2);
	void DrawBox (box& P,int color_out,int color_in);
	
	void DrawSubCadre (box& P,int color,int line_type,int thickness,int index1,int index2);//root function
	void DrawCadre (box& P,int color,int line_type,int thickness);
	
	void DrawSubCadre (box& P,int color,int thickness,int index1,int index2);
	void DrawCadre (box& P,int color,int thickness);

	void DrawSubCadre (box& P,int color,int index1,int index2);
	void DrawCadre (box& P,int color);
	//OTHER

	void DrawFilledRectangle (double xmin,double xmax,double ymin,double ymax,int color_out,int color_in,int line_type,int thickness);
	void DrawFilledRectangle (double xmin,double xmax,double ymin,double ymax,int color_out,int color_in,int thickness);
	void DrawFilledRectangle (double xmin,double xmax,double ymin,double ymax,int color_out,int color_in);

	void DrawRectangle (double xmin,double xmax,double ymin,double ymax,int color,int line_type,int thickness);
	void DrawRectangle (double xmin,double xmax,double ymin,double ymax,int color,int thickness);
	void DrawRectangle (double xmin,double xmax,double ymin,double ymax,int color);

	void DrawRectangle2(double x, double y,double width, double height);

	void DrawPoint (double x1,double y1,int color,int thickness);

	void DrawLine (double x1,double y1,double x2,double y2,int color,int line_type,int thickness);
    void DrawLine (double x1,double y1,double x2,double y2,int color,int thickness);
	void DrawLine (double a,double b,int color,int thickness);

	void DrawDisk (double x,double y,double r,int color_out,int color_in,int line_type,int thickness);
	void DrawDisk (double x,double y,double r,int color_out,int color_in,int thickness);
	void DrawDisk (double x,double y,double r,int color_out,int color_in);

	void DrawCircle (double x,double y,double r,int color,int line_type,int thickness);
	void DrawCircle (double x,double y,double r,int color,int thickness);
	void DrawCircle (double x,double y,double r,int color);

	void DrawText (double x,double y,const char* Text,int thickness);//untested
		
	void DrawCross(double x,double y,double size,int color,int thickness);
	void DrawXCross(double x,double y,double size,int color,int thickness);
	
	//useful functions
	void ChangementRepere(int x_pixel,int y_pixel,double* x, double* y);//useful for coordinate capture on image
	CvScalar IntToRGB(int color);
};

#endif // REPERE_H
