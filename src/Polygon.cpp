#include "Polygon.h"


double Polygon::polarAngle(Point reference, Point p) {
    return atan2(p.y - reference.y, p.x - reference.x);
}

// Helper function
bool Polygon::closerToReference(Point reference, Point p1, Point p2) {
    return (p1.x - reference.x) * (p1.x - reference.x) + (p1.y - reference.y) * (p1.y - reference.y) <
           (p2.x - reference.x) * (p2.x - reference.x) + (p2.y - reference.y) * (p2.y - reference.y);
}

// Comparator for sorting points by polar angle
bool Polygon::comparePoints(Point reference, Point p1, Point p2) {
    double angle1 = polarAngle(reference, p1);
    double angle2 = polarAngle(reference, p2);

    if (angle1 != angle2)
        return angle1 < angle2;

    return closerToReference(reference, p1, p2);
}

// Function to sort points in counterclockwise order
void Polygon::sortPointsCounterclockwise(Point* arr, int len) {

    
    // get average of all points.
    Point centroid = {0.0, 0.0};
    for (int i = 0; i < len; i++) {
        centroid.x += arr[i].x;
        centroid.y += arr[i].y;
    }
    centroid.x /= (float)len;
    centroid.y /= (float)len;

    // sort them out going counterclockwise.
    std::sort(arr, arr + 8, [centroid](const Point &p1, const Point &p2) {
        return Polygon::comparePoints(centroid, p1, p2);
    });
}



void Polygon::drawShape(Face* arr)
{
    cout << "DRAW " << endl;
    glColor3f(arr->r / 255.0f, arr->g / 255.0f, arr->b / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(arr->points[0].x, arr->points[0].y);
    glVertex2f(arr->points[1].x, arr->points[1].y);
    glVertex2f(arr->points[2].x, arr->points[2].y);
    glVertex2f(arr->points[3].x, arr->points[3].y);
    glEnd();
}
void Polygon::draw()
{
    for(int i = 0; i < getNumberFaces(); i++)
    {
        drawShape(faceListOriginal[i]);
    }
    glFlush(); 
}
Polygon::Polygon(Point* pointsList, int pointsLength)
{
    this->pointsList = pointsList;
    this->pointsLength = pointsLength;

    this->faceList = new Face*[getNumberFaces()];
    this->faceListOriginal = new Face*[getNumberFaces()];
    // pointsLength must == 8 right now!!!!

    sortPointsCounterclockwise(pointsList, pointsLength);
    getFaces();
    // sort faces by area.
    struct
    {
        bool operator()(Face* face1, Face* face2) const { return getArea(face1) > getArea(face2);}
    } areaCompare;

    std::sort(faceList, faceList + getNumberFaces(), areaCompare);
    
}   

Polygon::~Polygon()
{
    delete[] faceList;
    delete[] faceListOriginal;
}

Face** Polygon::getColorFaces()
{
    return this->faceList;
}

int Polygon::getNumberFaces()
{
    return pointsLength / 2 + 2;
}

double Polygon::getArea(Face* arr)
{
    // uses the bretschneider's formula
    Point pointA = arr->points[0];
    Point pointB = arr->points[1];
    Point pointC = arr->points[2];
    Point pointD = arr->points[3];

    // all distances are squared

    double distAB = (pointA.x - pointB.x) * (pointA.x - pointB.x) + (pointA.y - pointB.y) * (pointA.y - pointB.y);
    double distBC = (pointB.x - pointC.x) * (pointB.x - pointC.x) + (pointB.y - pointC.y) * (pointB.y - pointC.y);
    double distCD = (pointC.x - pointD.x) * (pointC.x - pointD.x) + (pointC.y - pointD.y) * (pointC.y - pointD.y);
    double distDA = (pointD.x - pointA.x) * (pointD.x - pointA.x) + (pointD.y - pointA.y) * (pointD.y - pointA.y);

    double diagAC = (pointA.x - pointC.x) * (pointA.x - pointC.x) + (pointA.y - pointC.y) * (pointA.y - pointC.y);
    double diagBD = (pointB.x - pointD.x) * (pointB.x - pointD.x) + (pointB.y - pointD.y) * (pointB.y - pointD.y);


    // answer is 0.25 * sqrt(area)
    double temp = distBC + distDA - distAB - distCD;
    double ans =  4.0 * diagAC * diagBD - (temp * temp);
    return ans;
}

void Polygon::getFaces()
{
    int topVertNum = pointsLength / 2;

    Face* bottomFace = new Face(pointsList[0], pointsList[1], pointsList[2], pointsList[3]);
    Face* topFace = new Face(pointsList[4], pointsList[5], pointsList[6], pointsList[7]);
    Face* leftFace = new Face(pointsList[0], pointsList[1], pointsList[7], pointsList[6]);
    Face* rightFace = new Face(pointsList[2], pointsList[3], pointsList[5], pointsList[4]);  
    Face* backFace = new Face(pointsList[0], pointsList[3], pointsList[5], pointsList[6]); 
    Face* frontFace = new Face(pointsList[1], pointsList[2], pointsList[4], pointsList[7]);


    // whatever is rendered first "covers" up other stuff
    faceList[5] = bottomFace;
    faceList[0] = topFace;
    faceList[1] = leftFace;
    faceList[2] = rightFace;
    faceList[3] = backFace;
    faceList[4] = frontFace;
    faceListOriginal[5] = bottomFace;
    faceListOriginal[1] = topFace;
    faceListOriginal[4] = leftFace;
    faceListOriginal[3] = rightFace;
    faceListOriginal[2] = backFace;
    faceListOriginal[0] = frontFace;
}