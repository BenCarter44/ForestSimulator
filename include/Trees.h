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
#include "Mesh.h"

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif

struct ForestAnimationSettings // per a "unit" in time.
{
    // all percentages are per unit time.
    // noTree settings.
    float TREE_BLANK_SIT_VACANT_UNIT_TIME = 20.0f;
    float TREE_NEW_GROW_FLAT_RATE = 0.00004f; // smallest float value.
    float TREE_NEW_GROW_NEIGHBOR_RATE = 0.0025f;

    // alive tree settings.
    float TREE_INITIAL_ALIVE = 0.60f;
    float TREE_INITIAL_AGE = 50.0f;
    float ANIMATION_GROW_SPEED_SEC = 0.75f;

    // flamability settings of alive trees.
    float TREE_MINIMUM_FLAMABILITY = 0.20f; // ;33f; // 0.0033f;
    float TREE_AGE_FLAMABILITY_FACTOR = 0.022f;

    float TREE_SPONTANEOUS_IGNITE_BASE = 0.001f;
    float TREE_SPONTANEOUS_IGNITE_PER_ALIVE_TREES = 0.0001f;
    float TREE_SPONTANEOUS_FIRE_START_DIVISOR = 10.0;

    float TREE_NEIGHBOR_BURN_FACTOR = 0.23f; // max 8 neighbors.
    float TREE_UPHILL_BURN_BONUS = 0.1f; // per y height.

    // burning tree settings.
    float TREE_BRUN_LENGTH_START = 10.0f;
    float TREE_BURN_LENGTH_END = 0.8f;
    float TREE_BURN_LENGTH_AGE_FACTOR = -0.1f;

    // burned tree settings.
    float TREE_SIT_VACANT_UNIT_TIME = 20.0f;
    float TREE_REGROW_FLAT_RATE = 0.001f;
    float TREE_REGROW_NEIGHBOR_RATE = 0.15f;
    float TREE_COMPLETE_DEATH_RATE = 0.04f;

    // lightning settings.
    float LIGHTNING_FRAME_COUNT = 10.0f;
    
    
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
    ForestAnimationSettings* forest;
    glm::vec3 points[8];
    glm::vec3 lightningPoints[8];

    // lightning
    float lightningFrameCount;
    float scaleX;
    float scaleZ;
    float shrinkRate;

    bool setup = false;
    float UNITS_PER_SECOND;
    float* unitClock;
    float creationTime;
    float heightPercent;
    int numberOfNeighbors;
    int neighborsOnFire = 0;
    int neighborsAlive = 0;
    float burnTime = 0.0;
    Tree** neighborTrees;

    int treeID = 0;

    bool treeFireStarter = false;


public:
    static int numberOfTreesAlive;
    static int numberOfTreesBurning;
    static int numberOfNoTrees;
    static int numberOfTreesBurned;
    static int numberOfFireStarts;

    // Constructor
    Tree(); // do not use... Exits only for memory allocation with new. 
    Tree(
        glm::vec3 position, 
        glm::vec3 dimensions, 
        ForestAnimationSettings* forest, 
        float* fps, 
        float unitsPerSecond, 
        float* unitClockI
    );

    void lightningStrike(glm::vec3 position, glm::vec3 dimensions);

    void setNeighborData(Tree** neighborTrees, int numberOFneighbors);

    // A unit in time.
    void incrementAge(float t);
    void draw();
    bool randomIF(float percent); // fps adjusted!
    int getStatus();
    float getElevation();

private:
    // transitions
    void enterNoTree();
    void exitNoTree();
    void enterAlive();
    void exitAlive();
    void enterBurning();
    void exitBurning();
    void enterBurned();
    void exitBurned();



    void simNoTree();  
    void simAliveTree();
    void simBurningTree();
    void simBurnedTree();

    void registerNeighborFire();
    void regieterNeighborNoFire();
    void registerNeighborAlive();
    void registerNeighborNotAlive();

public:
    void simulate();

    void spreadToNeighbors()
    {
      //   TODO. will be in CPP file.
    }
    
};

#endif // TREES_H
