#ifndef TREES_H
#define TREES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <cstdlib>  // for rand() and srand()
#include <cmath>

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

float verticesCUBE[NUM_VERTICES][3] = {
{-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5},
{0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}};

float facesCUBE[NUM_FACES][4] = {
{1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
{3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

class Color {
public:
    float red;
    float green;
    float blue;
    Color(float r, float g, float b);
};

struct ForestAnimationSettings // per a "unit" in time.
{
    float TREE_NEW_GROW_RATE = 0.1;
    float TREE_BURN_CHANCE_MAX = 0.33;
    float TREE_BURN_CHANCE_MIN = 0.04;
    float TREE_BURN_AGE_FACTOR = 1.0;
 // one percentage point add per unit.
    float TREE_BRUN_LENGTH_START = 100.0;
    float TREE_BURN_LENGTH_END = 10.0;
    float TREE_BURN_LENGTH_AGE_FACTOR = -1.0;
    float TREE_REGROW_FLAT_RATE = 0.01;
    float TREE_NEIGHBOR_BURN_FACTOR = 0.5;

    float TREE_REGROW_FLAT_RATE = 0.01;
    float TREE_REGROW_NEIGHBOR_RATE = 0.1;
    float TREE_COMPLETE_DEATH_RATE = 0.5;
    
};

class Tree
{

    float x_pos;
    float y_pos;
    float z_pos;
    Color color;
    glm::vec3 dimensions;
    int treeState;
    
    // 0 - no tree
    // 1 - alive
    // 2 - burning
    // 3 - burned
            
    // fps float
    float* fps;
    float* sqrtFPS;
    float age;
    float percentBurned;
    int neighbors;
    ForestAnimationSettings* forest;


public:
    // Constructor
    Tree(float x, float y, float z, glm::vec3 dimensions, ForestAnimationSettings* forest, float* fps)
    {
        std::srand(std::time(0) - 22);
        age = 0.0f;
    }
    

    // Getters
    glm::vec3 getDimensions();   
    float getXPos() const;
    float getYPos() const;
    float getZPos() const;
    glm::vec3 getDimensions() const;
    Color getColor() const;
    
    void draw()
    {
        glBegin(GL_QUADS);
        //bottom
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        //top
        glVertex3f(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));
        //sides
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));
        //sides
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));

        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));

        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        glVertex3f(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        glVertex3f(x_pos + (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));



        
        

        /* Draw each vertex.*/
        for (int i = 0; i < NUM_FACES; i++) {
            for (int j = 0; j < 4; j++) 
            {
                glm::vec3 result = glm::vec3(vertices[faces[i][j]][0],vertices[faces[i][j]][1],vertices[faces[i][j]][2]);
                glVertex3f(result.x, result.y, result.z);
            }
        }
        glEnd();
        
    }


    bool randomIF(float percent) // fps adjusted!
    {
        if(percent >= 1.0f)
        {
            return true;
        }
        else if(percent <= 0.0f)
        {
            return false;
        }
        double randomVal = (double)std::rand() / (double)RAND_MAX;
        float adjusted = pow(percent, 1.0 / (*sqrtFPS));
        
        return randomVal <= adjusted; 
    }
    // animation
    void registerTick()
    {
        age += 1
    }

private:
    // transitions
    void notreeTOAlive()
    {
        age = 0.0f;
    }
    void aliveTOBurning();
    void burnedTOAlive()
    {
        age = 0.0f;
    }
    void burnedTONoTree();
    void burningTOBurned();

public:
    void simulate()
    {
        if(treeState == 0)
        {
            simNoTree();
        }   
        else if(treeState == 1)
        {
            simAliveTree();
        }
        else if(treeState == 2)
        {
            simBurningTree();
        }
        else if(treeState == 3)
        {
            simBurnedTree();
        }
    }
    void simNoTree()
    {
        if(treeState != 0)
        {
            return;
        }
        if(randomIF(forest->TREE_NEW_GROW_RATE))
        {
            notreeTOAlive(); 
        }    
    }       
        
    void simAliveTree()
    {
        if(treeState != 1)
        {
            return;
        }
        // change alive to burning 10 precent of the time
        float percentToBurning = forest->TREE_BURN_CHANCE_MIN + forest->TREE_BURN_AGE_FACTOR * age;
        if(percentToBurning > forest->TREE_BURN_CHANCE_MAX)
        {
            percentToBurning = forest->TREE_BURN_CHANCE_MAX;
        }
        if(randomIF(percentToBurning))
        {
            aliveTOBurning(); 
        }            
    }
    
    void simBurningTree()
    {
        if (treeState != 2)
        {
            return;
        }
        

        float chanceTOspread = (neighbors * forest->TREE_NEIGHBOR_BURN_FACTOR) + forest->TREE_BURN_CHANCE_MIN;
        if(randomIF(chanceTOspread))
        {
            // spread
            spreadToNeighbors();
        }
        
            
    }

    void simBurnedTree()
    {
        if (treeState != 3)
        {
            return;
        }
        //regrow
        if(randomIF(forest->TREE_REGROW_FLAT_RATE))
        {
            burnedTOAlive(); 
        }
        // die completely
        if(randomIF(forest->TREE_COMPLETE_DEATH_RATE))
        {
            burnedTONoTree(); 
        }
        
    
    }

    void spreadToNeighbors()
    {
        TODO
    }
    
    
    

    // 
};


// class BurningTree : public Tree {
// private:
//     float percent_consumed;

// public:
//     // Constructor
//     BurningTree(float x, float y, float height);
//     void burn();
//     void update() override;
//     void transitionToBurned();
//     void draw() const override; // Override the draw method
// };


// class BurnedTree : public Tree {
// public:
//     // Constructor
//     BurnedTree(float x, float y, float height);
//     void draw() const override; // Override the draw method
// };


// class NoTree : public Tree {
// public:
//     // Constructor
//     NoTree(float x, float y, float height);
//     void draw() const override; // Override the draw method
// };


// class AliveTree : public Tree {
// public:
//     AliveTree(float x, float y, float height);
//     void draw() const override; // Override the draw method
// };

#endif // TREES_H
