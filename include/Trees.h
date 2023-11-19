/**
 * @file Trees.h
 * @author Benjamin Carter and Josh Canode
 * @brief This holds the tree class definitions.
 * @version 1.0
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

/**
 * @brief The constants for the forest.
 * 
 */
struct ForestAnimationSettings // per a "unit" in time.
{
    /* all percentages are per unit time. */
    /* noTree settings. */
    /**
     * @brief This is the length of time that an empty cell will try to stay empty (with it being a linear % ramp up)
     * 
     */
    float TREE_BLANK_SIT_VACANT_UNIT_TIME = 20.0f;
    /**
     * @brief This is the percent that a new tree will grow from an empty cell per time unit.
     * 
     */
    float TREE_NEW_GROW_FLAT_RATE = 0.00004f; // smallest float value.
    /**
     * @brief This is the increase in percent that an empty spot will receive for every alive neighbor around it.
     * 
     */
    float TREE_NEW_GROW_NEIGHBOR_RATE = 0.0025f;

    /* alive tree settings. */
    /**
     * @brief This is the initial % of trees that are alive in the forest.
     * 
     */
    float TREE_INITIAL_ALIVE = 0.60f;
    /**
     * @brief This is the initial age of the trees at the start of the program.
     * 
     */
    float TREE_INITIAL_AGE = 50.0f;
    /**
     * @brief This is the "grow" animation in seconds.
     * 
     */
    float ANIMATION_GROW_SPEED_SEC = 0.75f;

    /* flamability settings of alive trees. */
    /**
     * @brief This is the minimal % a tree starts with in likelihood of catching fire when receiving a spark.
     * 
     */
    float TREE_MINIMUM_FLAMABILITY = 0.20f; // ;33f; // 0.0033f;
    /**
     * @brief This is how much % the flammability increases per unit time.
     * 
     */
    float TREE_AGE_FLAMABILITY_FACTOR = 0.022f;

    /**
     * @brief This is the % that a tree will ignite (lightning)
     * 
     */
    float TREE_SPONTANEOUS_IGNITE_BASE = 0.001f;
    /**
     * @brief This is how much the spontaneous percent will increase for every alive tree on the map.
     * 
     */
    float TREE_SPONTANEOUS_IGNITE_PER_ALIVE_TREES = 0.0001f;
    /**
     * @brief For every fire started, the percent is divided by this amount to decrease the number of concurrent fires on the map.
     * 
     */
    float TREE_SPONTANEOUS_FIRE_START_DIVISOR = 10.0;

    /**
     * @brief This is % chance that a tree will receive a spark from a neighbor. Two neighbors equals double this.
     * 
     */
    float TREE_NEIGHBOR_BURN_FACTOR = 0.23f; // max 8 neighbors.
    /**
     * @brief If the neighboring tree is on fire and of lower elevation, increase by this uphill bonus % per 1 unit in y direction.
     * 
     */
    float TREE_UPHILL_BURN_BONUS = 0.1f; // per y height.

    /* burning tree settings. */
    /**
     * @brief The length of time a tree is on fire (in units)
     * 
     */
    float TREE_BRUN_LENGTH_START = 10.0f;
    /**
     * @brief The minimum length of time a tree is on fire (in units)
     * 
     */
    float TREE_BURN_LENGTH_END = 0.8f;
    /**
     * @brief The length decreases by this amount of units per unit in age.
     * 
     */
    float TREE_BURN_LENGTH_AGE_FACTOR = -0.1f;

    /* burned tree settings. */
    /**
     * @brief A burned stump attempts to stay as is for this amount of time (linearly ramping up %)
     * 
     */
    float TREE_SIT_VACANT_UNIT_TIME = 20.0f;

    /**
     * @brief Regrow percentage minimum
     * 
     */
    float TREE_REGROW_FLAT_RATE = 0.001f;
    /**
     * @brief For each neighbor alive, increment grow % by this much.
     * 
     */
    float TREE_REGROW_NEIGHBOR_RATE = 0.15f;
    /**
     * @brief Complete death of cell % rate
     * 
     */
    float TREE_COMPLETE_DEATH_RATE = 0.04f;

    /* lightning settings. */
    /**
     * @brief Length of lightning animation in frames.
     * 
     */
    float LIGHTNING_FRAME_COUNT = 10.0f;

    /**
     * @brief Lightning top y-value
     * 
     */
    float LIGHTNING_HEIGHT = 20.0f;
};

/**
 * @brief The Tree class manages what each cell does, broken up into four states.
 * 
 */
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
    /* Global Counters */
    static int numberOfTreesAlive;
    static int numberOfTreesBurning;
    static int numberOfNoTrees;
    static int numberOfTreesBurned;
    static int numberOfFireStarts;

    /**
     * @brief Construct a new Tree object. Do not use! Only for mem allocations.
     * 
     */
    Tree();

    /**
     * @brief Construct a new Tree cell
     * 
     * @param position - the center position of the cell
     * @param dimensions - the dimensions of the cell
     * @param forest - the forest settings 
     * @param fps - a pointer to the FPS counter
     * @param unitsPerSecond - units per second.
     * @param unitClockI - a pointer to the unit counter.
     */
    Tree(
        glm::vec3 position, 
        glm::vec3 dimensions, 
        ForestAnimationSettings* forest, 
        float* fps, 
        float unitsPerSecond, 
        float* unitClockI
    );

    /**
     * @brief Draw Lightning Strike 
     * 
     * @param position
     * @param dimensions 
     */
    void lightningStrike(glm::vec3 position, glm::vec3 dimensions);

    /**
     * @brief Update the tree with pointers to its neighbors. This must be called before anything else!
     * 
     * @param neighborTrees 
     * @param numberOFneighbors 
     */
    void setNeighborData(Tree** neighborTrees, int numberOFneighbors);

    /**
     * @brief Increment the age of the tree (already automatically internally increments age, but this is for extra aging)
     * 
     * @param t - time unit
     */
    void incrementAge(float t);

    /**
     * @brief Draw the tree
     * 
     */
    void draw();

    /**
     * @brief Return true or false randomly based on a percent. FPS adjusted.
     * 
     * @param percent 
     * @return true 
     * @return false 
     */
    bool randomIF(float percent); // fps adjusted!

    /**
     * @brief Get the status of the tree. 0 - no tree. 1 - alive tree. 2 - burning tree. 3 - burned tree.
     * 
     * @return int 
     */
    int getStatus();

    /**
     * @brief Get the Elevation of the tree
     * 
     * @return float 
     */
    float getElevation();

    /**
     * @brief Simulate the tree.
     * 
     */
    void simulate();

private:
    /* transitions */
    void enterNoTree();
    void exitNoTree();
    void enterAlive();
    void exitAlive();
    void enterBurning();
    void exitBurning();
    void enterBurned();
    void exitBurned();

    /* simulations for each stage */
    void simNoTree();  
    void simAliveTree();
    void simBurningTree();
    void simBurnedTree();

    /* neighbor callbacks */
    void registerNeighborFire();
    void regieterNeighborNoFire();
    void registerNeighborAlive();
    void registerNeighborNotAlive();
    
};

#endif // TREES_H
