//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
////#include <unistd.h>
//#include <iostream>
#include "ToolsObs.h"


using namespace cv;

/* Fonction de moindre carrées
   Parametre: Un vecteur de point
   Sortie les deux coefs de la droite de moindre carrée
   */
Vec2f LeastSquare(vector <Point> src){
    float meanX= 0.0;
    float meanY= 0.0;
    for(size_t i=0; i< src.size(); i++){
        meanX = meanX + src[i].x;
        meanY = meanY + src[i].y;
    }

    meanX = meanX/src.size();
    meanY = meanY/src.size();

    float a = 0.0;
    float sum1 = 0.0;
    float sum2 = 0.0;
    for(size_t j = 0; j < src.size(); j++){
        sum1 = sum1 + (src[j].x - meanX) * (src[j].y - meanY);
        sum2 = sum2 + (src[j].x - meanX) * (src[j].x - meanX);

    }
    a = sum1/sum2;
    float b = meanY - a*meanX;
    Vec2f res = Vec2f(a, b);
    return res;



}


int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
