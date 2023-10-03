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
void Polygon::sortPointsCounterclockwise(Point arr[8]) {

    Point centroid = {0.0, 0.0};
    for (int i = 0; i < 8; i++) {
        centroid.x += arr[i].x;
        centroid.y += arr[i].y;
    }
    centroid.x /= 8.0;
    centroid.y /= 8.0;

    std::sort(arr, arr + 8, [centroid](const Point &p1, const Point &p2) {
        return Polygon::comparePoints(centroid, p1, p2);
    });
}


void Polygon::drawShape(Point arr[4], int color)
{
    for (int i = 0; i < 4; i++) {
        arr[i] = arr[i];
    }

    if (color == 1){
        glColor3f(0.0, 1.0, 1.0);
    } else if (color == 2){
        glColor3f(1.0, 0.0, 1.0);
    } else {
        glColor3f(1.0, 1.0, 0.0);
    }

    glBegin(GL_POLYGON);
    glVertex2f(arr[0].x, arr[0].y);
    glVertex2f(arr[1].x, arr[1].y);
    glVertex2f(arr[2].x, arr[2].y);
    glVertex2f(arr[3].x, arr[3].y);
    glEnd();
    glFlush(); 
}

Polygon::Polygon(Point* pointsList, int pointsLength)
{
    this->pointsList = pointsList;
    this->pointsLength = pointsLength;

    // pointsLength must == 8 right now!!!!

    sortPointsCounterclockwise(pointsList);
}   

void Polygon::draw()
{
    Point bottomFace[4] = {pointsList[0], pointsList[1], pointsList[2], pointsList[3]};
    Point topFace[4] = {pointsList[4], pointsList[5], pointsList[6], pointsList[7]};
    Point leftFace[4] = {pointsList[0], pointsList[1], pointsList[7], pointsList[6]};
    Point rightFace[4] = {pointsList[2], pointsList[3], pointsList[5], pointsList[4]};  
    Point backFace[4] = {pointsList[0], pointsList[3], pointsList[5], pointsList[6]}; 
    Point frontFace[4] = {pointsList[1], pointsList[2], pointsList[4], pointsList[7]};

    drawShape(bottomFace,1);
    drawShape(leftFace,2);
    drawShape(backFace,3);
    drawShape(topFace,1);
    drawShape(frontFace,3);
    drawShape(rightFace,2);
}