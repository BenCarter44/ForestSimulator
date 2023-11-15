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

struct ForestAnimationSettings // per a "unit" in time.
{
    float TREE_NEW_GROW_RATE = 0.02f;
    float TREE_BURN_CHANCE_MAX = 0.0f; // 0.0033f;
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
    
    float ANIMATION_GROW_SPEED_SEC = 0.75f;
};

class Tree
{
private:
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
    float percentBurned;
    int neighbors;
    ForestAnimationSettings* forest;
    glm::vec3 points[8];
    bool setup = false;
    float UNITS_PER_SECOND;
    float* unitClock;
    float creationTime;
    float heightPercent;

public:
    static int numberOfTreesAlive;
    static int numberOfTreesBurning;
    static int numberOfNoTrees;
    static int numberOfTreesBurned;

    // Constructor
    Tree(); // do not use... Exits only for memory allocation with new. 
    Tree(glm::vec3 position, glm::vec3 dimensions, ForestAnimationSettings* forest, float* fps, float unitsPerSecond, float* unitClockI);
    
    // A unit in time.
    void incrementAge(float t);
    void draw();
    bool randomIF(float percent); // fps adjusted!
    
private:
    // transitions
    void notreeTOAlive();
    void aliveTOBurning();
    void burnedTOAlive();
    void burnedTONoTree();
    void burningTOBurned();

    void simNoTree();  
    void simAliveTree();
    void simBurningTree();
    void simBurnedTree();

public:
    void simulate();

    void spreadToNeighbors()
    {
      //   TODO. will be in CPP file.
    }
    
};

#endif // TREES_H
