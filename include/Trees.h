#ifndef TREES_H
#define TREES_H

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include <cstdlib>  // for rand() and srand()
#include <cmath>
#include <iostream>

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif

// class Color {
// public:
//     float red;
//     float green;
//     float blue;
//     Color(float r, float g, float b);
// };

struct ForestAnimationSettings // per a "unit" in time.
{
    float TREE_NEW_GROW_RATE = 0.1f;
    float TREE_BURN_CHANCE_MAX = 0.33f;
    float TREE_BURN_CHANCE_MIN = 0.04f;
    float TREE_BURN_AGE_FACTOR = 1.0f;
 // one percentage point add per unit.
    float TREE_BRUN_LENGTH_START = 100.0f;
    float TREE_BURN_LENGTH_END = 10.0f;
    float TREE_BURN_LENGTH_AGE_FACTOR = -1.0f;
    float TREE_NEIGHBOR_BURN_FACTOR = 0.5f;

    float TREE_REGROW_FLAT_RATE = 0.01f;
    float TREE_REGROW_NEIGHBOR_RATE = 0.1f;
    float TREE_COMPLETE_DEATH_RATE = 0.5f;
    
    float TREE_INITIAL_ALIVE = 0.50f;
    
};

class Tree
{

    float x_pos;
    float y_pos;
    float z_pos;
    glm::vec3 dimensions;
    int treeState;
    
    // 0 - no tree
    // 1 - alive
    // 2 - burning
    // 3 - burned
            
    // fps float
    float* fps;
    float age;
    float percentBurned;
    int neighbors;
    ForestAnimationSettings* forest;
    glm::vec3 points[8];
    bool setup = false;

public:
    Tree()
    {
        setup = false;
    }
    // Constructor
    Tree(glm::vec3 position, glm::vec3 dimensions, ForestAnimationSettings* forest, float* fps)
    {
        setup = true;
        x_pos = position.x;
        y_pos = position.y;
        z_pos = position.z;
        this->dimensions = dimensions;
    //    std::srand(std::time(0) * 2.0f - 22);
        age = 0.0f;

        float state = (float)std::rand() / (float)RAND_MAX;
        treeState = state <= forest->TREE_INITIAL_ALIVE;

        points[0] = glm::vec3(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
        points[1] = glm::vec3(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        points[2] = glm::vec3(x_pos + (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
        points[3] = glm::vec3(x_pos + (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
    
        points[4] = glm::vec3(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));
        points[5] = glm::vec3(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
        points[6] = glm::vec3(x_pos + (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
        points[7] = glm::vec3(x_pos + (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));

    }
    
    void setAge(float a)
    {
        age = a;
    }

    // Getters
    glm::vec3 getDimensions();   
    float getXPos() const;
    float getYPos() const;
    float getZPos() const;
    glm::vec3 getDimensions() const;
    
    void draw()
    {
        if(treeState == 0 || !setup)
        {
            return;
        }
        else if(treeState == 1)
        {
         //   glColor3f(1.0, 1.0, 1.0);
            glColor3f(CC(11.0f), CC(102.0f), CC(35.0f));
        }
        else if(treeState == 2)
        {
            glColor3f(CC(255.0f), CC(90.0f), CC(41.0f));
        }
        else if(treeState == 3)
        {
            glColor3f(CC(51.0f), CC(12.0f), CC(0.0f));
        }
    //    std::cout << x_pos << ' ' << y_pos << ' ' << z_pos << ' ' << dimensions.x << ' ' << dimensions.y << ' ' << dimensions.z << ' ' << std::endl;
        

        glBegin(GL_TRIANGLES);
            // bottom
            glVertex3f(points[0].x, points[0].y + 0.01, points[0].z);
            glVertex3f(points[1].x, points[1].y + 0.01, points[1].z);
            glVertex3f(points[2].x, points[2].y + 0.01, points[2].z);
            glVertex3f(points[3].x, points[3].y + 0.01, points[3].z);
            glVertex3f(points[2].x, points[2].y + 0.01, points[2].z);
            glVertex3f(points[0].x, points[0].y + 0.01, points[0].z);

            // top
            glVertex3f(points[4].x, points[4].y, points[4].z);
            glVertex3f(points[5].x, points[5].y, points[5].z);
            glVertex3f(points[6].x, points[6].y, points[6].z);
            glVertex3f(points[7].x, points[7].y, points[7].z);
            glVertex3f(points[6].x, points[6].y, points[6].z);
            glVertex3f(points[4].x, points[4].y, points[4].z);

            for(int i = 0; i < 4; i++)
            {
                // side
                glVertex3f(points[0 + i].x, points[0 + i].y, points[0 + i].z);
                glVertex3f(points[(1 + i) % 8].x, points[(1 + i) % 8].y, points[(1 + i) % 8].z);
                glVertex3f(points[(5 + i) % 8].x, points[(5 + i) % 8].y, points[(5 + i) % 8].z);
                glVertex3f(points[(5 + i) % 8].x, points[(5 + i) % 8].y, points[(5 + i) % 8].z);
                glVertex3f(points[(4 + i) % 8].x, points[(4 + i) % 8].y, points[(4 + i) % 8].z);
                glVertex3f(points[0 + i].x, points[0 + i].y, points[0 + i].z);
            }
        glEnd();

        /* Draw Borders */
        if(treeState == 1)
        {
         //   glColor3f(1.0, 1.0, 1.0);
            glColor3f(CC(0.0f), CC(0.0f), CC(0.0f));
        }
        else if(treeState == 2)
        {
            glColor3f(CC(255.0f), CC(255.0f), CC(255.0f));
        }
        else if(treeState == 3)
        {
            glColor3f(CC(50.0f), CC(50.0f), CC(50.0f));
        }
        glBegin(GL_LINE_STRIP);
            // bottom
            glVertex3f(points[0].x, points[0].y, points[0].z);
            glVertex3f(points[1].x, points[1].y, points[1].z);
            glVertex3f(points[2].x, points[2].y, points[2].z);
            glVertex3f(points[3].x, points[3].y, points[3].z);
            glVertex3f(points[0].x, points[0].y, points[0].z);
        
            // top
            glVertex3f(points[4].x, points[4].y, points[4].z);
            glVertex3f(points[5].x, points[5].y, points[5].z);
            glVertex3f(points[6].x, points[6].y, points[6].z);
            glVertex3f(points[7].x, points[7].y, points[7].z);
            glVertex3f(points[4].x, points[4].y, points[4].z);
        glEnd();
        glBegin(GL_LINES);
            for(int i = 0; i < 4; i++)
            {
                // side
                glVertex3f(points[0 + i].x, points[0 + i].y, points[0 + i].z);
                glVertex3f(points[(4 + i) % 8].x, points[(4 + i) % 8].y, points[(4 + i) % 8].z);
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
        float adjusted = pow(percent, 1.0 / (*fps));
        
        return randomVal <= adjusted; 
    }
    // animation
    void registerTick()
    {
        age += 1;
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
        if(!setup)
        {
            return;
        }
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
      //   TODO
    }
    
    
    

    // 
};



#endif // TREES_H
