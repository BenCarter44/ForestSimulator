#include "Trees.h"

// Color class constructor
Color::Color(float r, float g, float b) : red(r), green(g), blue(b) {}

// Tree class constructor
Tree::Tree(float x, float y, float height) : x_pos(x), y_pos(y), z_pos(height), dimensions(1.0f) {}

float Tree::getXPos() const { return x_pos; }
float Tree::getYPos() const { return y_pos; }
float Tree::getZPos() const { return z_pos; }
float Tree::getDimensions() const { return dimensions; }
Color Tree::getColor() const { return color; }
void Tree::noTree() { dimensions = 0.0f; }

void Tree::draw() const {
    // Implement the drawing logic for a generic tree (as a cube) here.
    
}

// BurningTree class constructor
BurningTree::BurningTree(float x, float y, float height) : Tree(x, y, height), percent_consumed(0.0f) {
    getColor() = Color(1.0f, 0.0f, 0.0f);
}

void BurningTree::burn() {
    percent_consumed += 0.1f;
}

void BurningTree::update() {
    burn();
    if (percent_consumed >= 1.0f) {
        transitionToBurned();
    }
}

void BurningTree::transitionToBurned() {
    // TODO: Transition to a burned tree
}

void BurningTree::draw() const {
    // Implement the drawing logic for a burning tree (as a cube) here.
}

// BurnedTree class constructor
BurnedTree::BurnedTree(float x, float y, float height) : Tree(x, y, height) {
    getColor() = Color(0.5f, 0.5f, 0.5f);
}

void BurnedTree::draw() const {
    // Implement the drawing logic for a burned tree (as a cube) here.
}

// NoTree class constructor
NoTree::NoTree(float x, float y, float height) : Tree(x, y, height) {
    noTree();
}

void NoTree::draw() const {
    // Implement the drawing logic for a non-existent tree here.
}

// AliveTree class constructor
AliveTree::AliveTree(float x, float y, float height) : Tree(x, y, height) {
    getColor() = Color(0.0f, 1.0f, 0.0f);
}

void AliveTree::draw() const {
    // Implement the drawing logic for a living tree (as a cube) here.
}


