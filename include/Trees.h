#ifndef TREES_H
#define TREES_H

class Color {
public:
    float red;
    float green;
    float blue;

    Color(float r, float g, float b);
};

class Tree {
private:
    float x_pos;
    float y_pos;
    float z_pos;
    float dimensions;
    Color color;

public:
    // Constructor
    Tree(float x, float y, float height);
    // Getters
    float getXPos() const;
    float getYPos() const;
    float getZPos() const;
    float getDimensions() const;
    Color getColor() const;
    // Setters
    void noTree();
    
    virtual void update() {}
    virtual void draw() const; // Add the draw method
};

class BurningTree : public Tree {
private:
    float percent_consumed;

public:
    // Constructor
    BurningTree(float x, float y, float height);
    void burn();
    void update() override;
    void transitionToBurned();
    void draw() const override; // Override the draw method
};

class BurnedTree : public Tree {
public:
    // Constructor
    BurnedTree(float x, float y, float height);
    void draw() const override; // Override the draw method
};

class NoTree : public Tree {
public:
    // Constructor
    NoTree(float x, float y, float height);
    void draw() const override; // Override the draw method
};

class AliveTree : public Tree {
public:
    AliveTree(float x, float y, float height);
    void draw() const override; // Override the draw method
};

#endif // TREES_H
