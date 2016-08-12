#include "Horizon.h"

using namespace std;
using namespace cv;

/* 
    Fonction pour initialiser l'image:

    1. On recadre legerement l'image pour limiter les effets de bords et faire moins de calculs
    2. On fait une erosion pour limiter les effets des vaguelettes
    3. on passe l'image en gris pour n'avoir qu'un canal.
    4. On égalise les gris pour limiter encore les effets des vaguelettes.
*/
cv::Mat initializeImage(cv::Mat src, int boatSize){

	cv::Mat srcCropped, srcErode, srcGray, srcGrayEqualized;

    srcCropped = src(Rect(0,10, src.cols, src.rows - 10 - boatSize));

    cv::erode(srcCropped,srcErode,cv::Mat::ones(5,5,CV_8U));

    cv::cvtColor(srcErode, srcGray, CV_BGR2GRAY);

    cv::equalizeHist(srcGray, srcGrayEqualized);

    return srcGrayEqualized;
}

/* 
    Fonction pour détecter les droites horizontales suceptible d'être celle de l'horizon.

    1. Application de canny pour pour détecter les contours
    2. Détection des lignes de Hough sur ces contours
    3. On enlève les lignes clairement non horizontales
    4. On calcule la moyenne de la hauteur ds lignes restantes
    5. On enlève celles trop éloignées de la moyenne (a ajuster selon le 3eme paramètre)

    Paramètres:
    - cv::Mat src: l'image source
    - int line_length: la taille minimum des lignes de Hough a détecter
    - int difference: la distance par rapport a la moyenne que chaque lignes doit a avoir au maximum.

    Sortie: un vecteur de points contenant les
*/
vector <Point> cannyHough(cv::Mat src, int line_length, int difference){

	cv::Mat srcCanny, srcThresh;

    /* Application du filtre de Canny pour détecter les contours */
    double high_thres = cv::threshold( src, srcThresh, 0, 255, CV_THRESH_BINARY+CV_THRESH_OTSU );

    Canny(src, srcCanny, high_thres*0.3, 0.5*high_thres, 3);
    imshow("Canny", srcCanny);


    /*Application de la transformee de Hough pour detecter les lignes.*/

    vector <cv::Vec4i> lines;
    HoughLinesP( srcCanny, lines, 1, CV_PI/180, 100, line_length, 0);


    /* Suppression des lignes clairement non horizontale */

    vector <Point> houghPoint;
    vector <int> houghCompare;
    Point tmpHough;
    for( size_t i = 0; i < lines.size(); i++ )
    {
        if ((fabs((double)lines[i][0]-(double)lines[i][2])> line_length) && (fabs((double)lines[i][1]-(double)lines[i][3]) < 40)) {
            tmpHough.x = (lines[i][2] + lines[i][0])/2;
            tmpHough.y = (lines[i][3] + lines[i][1])/2;
            houghPoint.push_back(tmpHough);
            houghCompare.push_back(tmpHough.y);
        }

    }
    if(houghPoint.size() == 0){return houghPoint;}

    /* Calcul de la moyenne de la hauteur des lignes*/
    int tmpAdd = 0;

    for(size_t j = 0; j < houghCompare.size(); j++){
        tmpAdd = tmpAdd + houghCompare[j];
    }
    int meanHough = tmpAdd/ houghCompare.size();

    /*Suppression des lignes trop éloigné par rapport a la moyenne */
    size_t iEr = 0;
    while(iEr < houghPoint.size()){
        if(abs(houghCompare.at(iEr) - meanHough) > difference){
            houghPoint.erase(houghPoint.begin() + iEr);
            iEr = iEr - 1;
        }
         //  cv::circle(srcCropped, houghPoint[iEr],2, CV_RGB(255,0,255), -1, 8 );
        iEr = iEr+1;
    }

    return houghPoint;
}

/*
    Fonction pour ajouter un triangle pour completer l'image decoupee par l'horizon
    Paramètre: image source
               les deux poins extremites de l'horizon
               coefficient directeur et ordonnee a l'origine de la droite

    Sortie L'image completee

    /!\ Possibilite de changer la couleur de remplissage dans les Vec3b.
*/
cv::Mat fillWithNothing(cv::Mat srcCropped, Point2i point1, Point2i point2, float coef, float ord){
    bool sup;
    if(point1.y == point2.y){
		return srcCropped;
	}
    point1.y - point2.y > 0 ? sup = false : sup = true;
    Point2i tmp;
    if(sup){
        for(int i = point1.y; i < point2.y; i++){
            tmp = Point2i((int)((i - ord)/coef), i);
            for(int j = tmp.x; j <= srcCropped.cols; j++){

                srcCropped.at<Vec3b>(Point(j,i)) = Vec3b(153,153,153); // Changer la couleur ici
            }
        }
    }
    else if(!sup){
        for(int i = point2.y; i < point1.y; i++){
            tmp = Point2i((int)((i - ord)/coef), i);
            for(int j = 0; j <= tmp.x; j++){
                srcCropped.at<Vec3b>(Point(j,i)) = Vec3b(153,153,153); // et ici.
            }
        }
    }
    return srcCropped;
}

/* 
    Fonction pour trouver l'horizon sur l'image.
    1. Calcul des points extrimites de la droite
    2. Decoupage de l'image source sur le point le plus haut
    3. Dessin de la droite d'horizon sur l'image
    4. Transformation de ce qu'il y a au dessus de l'image en "vide"

    Parametres: Vec2f houghCoef: Coefficients de la droite des moindres carrées sur les lignes de Hough trouvées précdemment
        cv::Mat src: l'image source
        int boatSize: la hauteur visible de l'avant du bateau.

        Sortie: l'image decoupee sur l'horizon.
*/
cv::Mat estimateHorizon(Vec2f houghCoef, cv::Mat src, int boatSize){
	cv::Mat srcCroppedEst, srcCroppedHorizon;
    float coef = houghCoef[0];

    float ord = houghCoef[1];

    Point2i point1 = Point2i(1,(int)ord);
    Point2i point2;
    ((src.cols*coef + ord <= src.cols - (boatSize + 10)) && ( src.cols*coef + ord > 0))  ?  point2 = Point2i(src.cols -1,(int)(src.cols*coef + ord)): point2 = Point2i(src.cols - 1,src.cols - (boatSize + 10));
    srcCroppedEst = src(Rect(0, 10, src.cols, src.rows - 10 - boatSize));
    /*Dessin de la droite passant par toute l'image. */
    int maxSize;
    boatSize > 10 ? maxSize = boatSize : maxSize = 10;
    if((10 < point1.y) && (point1.y < src.rows - 10 - maxSize)){
       // cv::line(srcCroppedEst, point1, point2, CV_RGB(0,255,255), 2, 8);
    }
    else{
        return cv::Mat();
    }
	cv::Mat srcTmpEst = srcCroppedEst;
	imshow("debug", srcCroppedEst);
	cv::waitKey(1000);
    srcTmpEst = fillWithNothing(srcCroppedEst, point1, point2, coef, ord);
	srcCroppedEst = srcTmpEst;
    if((point1.y > point2.y) && (src.rows - point2.y - boatSize - 10 > 0)){
        srcCroppedHorizon = src(Rect(0, point2.y + 10, src.cols, src.rows - point2.y - 10 - boatSize));
    }
    else if((point1.y <= point2.y) && (src.rows - point1.y - boatSize - 10 > 0)){
        srcCroppedHorizon = src(Rect(0, point1.y + 10, src.cols, src.rows - point1.y - 10 - boatSize));

    }
    else {

        return cv::Mat();
    }
    return srcCroppedHorizon;
}
