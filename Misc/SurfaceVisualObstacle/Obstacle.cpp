#include "Obstacle.h"
#include <iostream>

using namespace std;
using namespace cv;

/*
    Fonction pour initialiser l'image.
    1. Séparation des canaux HSV.
    2. application du filtre corespond a la météo choisie
    3. Montre le resultat du filtre si l'option est choisie

    Parametres: cv::Mat srcCroppedHD: image source
                bool show: booleen true pour montrer le resultat du filtre, false sinon
                char weather: 'c' pour cloudy/nuageux 's' pour sunny/ensoleillé.

    Sortie; l'image fitlree
*/
cv::Mat obsInit(cv::Mat srcCroppedHD, bool show, char weather){

    cv::Mat srcCroppedFilter;
    cv::Mat srcCroppedHSV;
    vector <Mat> srcCroppedSplit(3);
    cv::cvtColor(srcCroppedHD, srcCroppedHSV, CV_BGR2HSV);

    imshow("coucou", srcCroppedHSV);
    cv::split(srcCroppedHSV, srcCroppedSplit);
    std::cout << "hi \n";

    if(weather == 's'){
        cv::inRange(srcCroppedHSV,cv::Scalar(0, 40, 0), cv::Scalar(179, 255, 255), srcCroppedFilter); // Changer les valeurs du filtre ici pour 's' ensolleillé
        cv::threshold(srcCroppedFilter, srcCroppedFilter, 0, 255, THRESH_BINARY_INV);
    }
    else if(weather == 'c'){
        cv::inRange(srcCroppedHSV,cv::Scalar(40, 0, 0), cv::Scalar(95, 255, 255), srcCroppedFilter); // Changer les valeurs du filtre ici pour 'c' nuageux.
    }

    if(show){
        imshow("HSV Filter", srcCroppedFilter);
        imshow("h", srcCroppedSplit[0]);
        imshow("s", srcCroppedSplit[1]);
        imshow("v", srcCroppedSplit[2]);
    }

    return srcCroppedFilter;
}

/*
    Fonction pour detecter le blob de la mer.

    1. Detection des contours
    2. Prendre uniquement le plus gros contours
    3. detection du centre de masse du blob

    Parametres: cv::Mat srcFiltered image source
                cv::Mat srcCroppedToDraw image sur laquelle dessiner

    Sortie: un point représentant le centre de masse du blob.
*/
Point2f seaContour(cv::Mat srcFiltered, cv::Mat srcCroppedToDraw){

    vector <vector <cv::Point2i> > listContours;
    vector <cv::Vec4i> HierarchieContours;

    /* Mis en place de la detection de contour */
    cv::findContours(srcFiltered,listContours,HierarchieContours,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    if(listContours.size() == 0){
        return cv::Point2f(0,0);
    }
    Moments momentMer;
    Point2f massCenter = Point2f(0,0);
    for(size_t i = 0; i < listContours.size(); i++){
        vector <cv::Point2i> approx;
        cv::approxPolyDP(listContours[i],approx, 10, true);
        vector <vector <cv::Point2i> > tmpContours;
        tmpContours.push_back(approx);

        /* Seul le contour representant la mer est pris en compte */


        if(contourArea((approx))>4000){


            /* Detection du centre de masse du contour */


            momentMer = cv::moments(listContours[i], false);
            massCenter = Point2f((float)(momentMer.m10/momentMer.m00), (float)(momentMer.m01/momentMer.m00));
            cv::drawContours(srcCroppedToDraw, tmpContours,0, cv::Scalar(255,0,0),2, 8/*, HierarchieContours*/);


        }
    }
    return massCenter;
}


/* 
    Fonction pour detecter l'obstacle
    Creation des points d'interets: Le centre de masse correspondant au blob de l'eau et le centre de masse de l'image entiere.

    Parametres: Point2f massCenter Le Centre de masse du blob de l'eau
                cv::Mat srcCroppedHorizon image source

    Sortie: la différence d'abcisse entre les deux centres de masses.
*/
float obstacleDetected(Point2f massCenter, cv::Mat srcCroppedHorizon){
    /* Si le centre de masse s'eloigne trop du centre du ROI, alors il y a obstacle */
    cv::circle(srcCroppedHorizon, massCenter, 2, CV_RGB(0,255,0), -1, 8);
    cv::circle(srcCroppedHorizon, Point(srcCroppedHorizon.cols/2, srcCroppedHorizon.rows/2), 2, CV_RGB(255,0,255), -1, 8);
    float obstacle = srcCroppedHorizon.cols/2 - massCenter.x;
    return obstacle;
}
