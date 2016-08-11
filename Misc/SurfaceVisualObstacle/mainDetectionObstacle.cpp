#include "mainDetectionObstacle.h"

using namespace std;
using namespace cv;

Mat output, srcInitialized, srcCroppedHD,srcObsInit;

/* Fonction permettant de detecter un obstacle
 *
 *  Paramètres:
 *
 *      - cv::Mat src: Image source ou detecter l'obstacle
 *
 *      - char weather: 'c' pour un temps nuageux et 's' pour un temps ensoleillé
 *
 *      - int boatSize: la hauteur en pixel de l'avant du bateau visible sur l'image
 *
 *  Sortie:
 *
 *      deux floats: Le premier prenant quatre valeurs:-1 si pas d'horizon trouvé
                                                        0 si pas d'obstacle trouvé
 *                                                      1 si obstacle a gauche
 *                                                      2 si obstacle a droite
 *
 *                    Le second étant la distance en pixel du centre de masse de l'obstacle
 *                      par rapport au bord lattéral de l'image le plus proche. (Pour placer
 *                      APPROXIMATIVEMENT l'obstacle dans l'espace)
 */
cv::Point2f detectObstacle(cv::Mat src, char weather, int boatSize){


    /* Initialisation */
    output = src;
    srcInitialized = initializeImage(src, boatSize);

    imshow("test", srcInitialized);


    /* Calcul des droites horizontale dans l'espace de Hough */
    vector <Point> houghPoint = cannyHough(srcInitialized, 5, 40); // On pourra changer les deux derniers paramètres en fonction de la résolution de l'image
    if(houghPoint.size() == 0){return cv::Point2f(-1, 0);}

    Vec2f houghCoef = LeastSquare(houghPoint);

    /*Calcul de la droite d'horizon s'etendant a  l'image */

    srcCroppedHD = estimateHorizon(houghCoef, src, boatSize);

    if(srcCroppedHD.rows == 0){return cv::Point2f(-1, 0);}
   // imshow("horizon", srcCroppedHD);



    /* Detection des obstacles en dessous de l'horizon trouvé précedemment */

    srcObsInit = obsInit(srcCroppedHD, true, weather); // Si les filtres de pour la detection d'obstacle ne marchent pas, c'est dans cette fonction qu'il faut les changer.

    Point2f massCenter = seaContour(srcObsInit, srcCroppedHD);

    if(massCenter == cv::Point2f(0,0)){return cv::Point2f(-1, 0);}
    char obs = (char)obstacleDetected(massCenter, srcCroppedHD);
  //  imshow("output", srcCroppedHD);
    /* Analyse de l'obstacle trouvé pour déterminer sa position par rapport au bateau */

    if(obs >= 10){return cv::Point2f(1, obs);}
    if(obs <= -10){return cv::Point2f(2, obs);}
    return cv::Point2f(0, 0);
}
