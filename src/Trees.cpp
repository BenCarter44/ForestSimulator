#include "Trees.h"

int Tree::numberOfTreesAlive = 0;
int Tree::numberOfTreesBurning = 0;
int Tree::numberOfNoTrees = 0;
int Tree::numberOfTreesBurned = 0;
int Tree::numberOfFireStarts = 0;

Tree::Tree()
{
    setup = false;
}

Tree::Tree(
    glm::vec3 position, 
    glm::vec3 dimensions, 
    ForestAnimationSettings* forest, 
    float* fps, 
    float unitsPerSecond, 
    float* unitClockI)
{
    setup = true;
    x_pos = position.x;
    y_pos = position.y;
    z_pos = position.z;
    this->dimensions = dimensions;
    heightPercent = 1.0f;
    
    neighborsOnFire = 0;
    this->numberOfNeighbors = 0;

    unitClock = unitClockI;

    creationTime = *(unitClock);

    burnTime = 0.0;
    neighborsAlive = 0;

    setup = true;
    x_pos = position.x;
    y_pos = position.y;
    z_pos = position.z;
    this->dimensions = dimensions;
    heightPercent = 1.0f;

    unitClock = unitClockI;

    creationTime = *(unitClock);
//    std::srand(std::time(0) * 2.0f - 22);

    this->forest = forest;
    this->fps = fps;

    float state = (float)std::rand() / (float)RAND_MAX;
    treeState = state <= forest->TREE_INITIAL_ALIVE;
    if(treeState)
    {
        numberOfTreesAlive++;

        treeID = numberOfTreesAlive;
    }
    else
    {
        numberOfNoTrees++;

        treeID = -1 * numberOfNoTrees;
    }

    points[0] = glm::vec3(x_pos - (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));
    points[1] = glm::vec3(x_pos - (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
    points[2] = glm::vec3(x_pos + (dimensions.x / 2), y_pos, z_pos + (dimensions.z / 2));
    points[3] = glm::vec3(x_pos + (dimensions.x / 2), y_pos, z_pos - (dimensions.z / 2));

    points[4] = glm::vec3(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));
    points[5] = glm::vec3(x_pos - (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
    points[6] = glm::vec3(x_pos + (dimensions.x / 2), y_pos + dimensions.y, z_pos + (dimensions.z / 2));
    points[7] = glm::vec3(x_pos + (dimensions.x / 2), y_pos + dimensions.y, z_pos - (dimensions.z / 2));
    UNITS_PER_SECOND = unitsPerSecond;
}

void Tree::setNeighborData(Tree** neighborTrees, int nubmerOfNeighbors)
{
    this->numberOfNeighbors = nubmerOfNeighbors;
    this->neighborTrees = neighborTrees;
}

void Tree::incrementAge(float t)
{
    creationTime -= t;
}

void Tree::draw()
{
    if(treeState == 0 || !setup || (*fps) < 1.0f)
    {
        return;
    }
    else if(treeState == 1)
    {
        //   glColor3f(1.0, 1.0, 1.0);
        glColor3f(CC(11.0f), CC(102.0f), CC(35.0f));
        if(heightPercent < 1.0f)
        {
            heightPercent += 1.0 / ((*fps) * forest->ANIMATION_GROW_SPEED_SEC);
        }
    }
    else if(treeState == 2)
    {
        glColor3f(CC(255.0f), CC(90.0f), CC(41.0f));

        float age = burnTime - creationTime;
        
        float maxBurnLength = forest->TREE_BRUN_LENGTH_START + forest->TREE_BURN_LENGTH_AGE_FACTOR * age;
    //    std::cout << maxBurnLength << ' ' << forest->TREE_BURN_LENGTH_END << std::endl;
        if(maxBurnLength < forest->TREE_BURN_LENGTH_END)
        {
            maxBurnLength = forest->TREE_BURN_LENGTH_END;
        }

        heightPercent = 1.0 - Mesh::mapF(*unitClock, burnTime, maxBurnLength + burnTime,0.0, 0.75);
    //    std::cout << heightPercent << '\t' << *unitClock << '\t' << burnTime << '\t' << maxBurnLength << std::endl;
        if(*unitClock > burnTime + maxBurnLength)
        {
            exitBurning();
            enterBurned();
        }
    }
    else if(treeState == 3)
    {
        glColor3f(CC(51.0f), CC(12.0f), CC(0.0f));
    }



    
//    std::cout << x_pos << ' ' << y_pos << ' ' << z_pos << ' ' << dimensions.x << ' ' << dimensions.y << ' ' << dimensions.z << ' ' << std::endl;
    
    // for burning:




        float topY = heightPercent * (points[7].y - points[0].y) + points[0].y;

    glBegin(GL_TRIANGLES);
        // // bottom
        // glVertex3f(points[0].x, points[0].y + 0.01, points[0].z);
        // glVertex3f(points[1].x, points[1].y + 0.01, points[1].z);
        // glVertex3f(points[2].x, points[2].y + 0.01, points[2].z);
        // glVertex3f(points[3].x, points[3].y + 0.01, points[3].z);
        // glVertex3f(points[2].x, points[2].y + 0.01, points[2].z);
        // glVertex3f(points[0].x, points[0].y + 0.01, points[0].z);

        // top
        glVertex3f(points[4].x, topY, points[4].z);
        glVertex3f(points[5].x, topY, points[5].z);
        glVertex3f(points[6].x, topY, points[6].z);
        glVertex3f(points[7].x, topY, points[7].z);
        glVertex3f(points[6].x, topY, points[6].z);
        glVertex3f(points[4].x, topY, points[4].z);

        for(int i = 0; i < 3; i++)
        {
            // side
            glVertex3f(points[0 + i].x, points[0 + i].y, points[0 + i].z);
            glVertex3f(points[(1 + i) % 8].x, points[(1 + i) % 8].y, points[(1 + i) % 8].z);
            glVertex3f(points[(5 + i) % 8].x, topY, points[(5 + i) % 8].z);
            
            glVertex3f(points[(5 + i) % 8].x, topY, points[(5 + i) % 8].z);
            glVertex3f(points[(4 + i) % 8].x, topY, points[(4 + i) % 8].z);
            glVertex3f(points[0 + i].x, points[0 + i].y, points[0 + i].z);
        }
        // back side
        glVertex3f(points[3].x, points[3].y, points[3].z);
        glVertex3f(points[7].x, topY, points[7].z);
        glVertex3f(points[4].x, topY, points[4].z);

        glVertex3f(points[3].x, points[3].y, points[3].z);
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glVertex3f(points[4].x, topY, points[4].z);
            
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
        glVertex3f(points[0].x, topY, points[0].z);
        glVertex3f(points[1].x, topY, points[1].z);
        glVertex3f(points[2].x, topY, points[2].z);
        glVertex3f(points[3].x, topY, points[3].z);
        glVertex3f(points[0].x, topY, points[0].z);
    
        // top
        glVertex3f(points[4].x, topY, points[4].z);
        glVertex3f(points[5].x, topY, points[5].z);
        glVertex3f(points[6].x, topY, points[6].z);
        glVertex3f(points[7].x, topY, points[7].z);
        glVertex3f(points[4].x, topY, points[4].z);
    glEnd();
    glBegin(GL_LINES);
        for(int i = 0; i < 4; i++)
        {
            // side
            glVertex3f(points[0 + i].x, points[0 + i].y, points[0 + i].z);
            glVertex3f(points[(4 + i) % 8].x, topY, points[(4 + i) % 8].z);
        }
    glEnd();
}

bool Tree::randomIF(float percent)
{
    if(percent >= 1.0f)
    {
        return true;
    }
    else if(percent <= 0.0f)
    {
        return false;
    }
    if((*fps) < 1.0)
    {
        return false;
    }
    double randomVal = (double)std::rand() / (double)RAND_MAX;
    // float adjusted = pow(percent, 1.0 / ((*fps) / UNITS_PER_SECOND));
    float adjusted = percent / ((*fps) / UNITS_PER_SECOND);
    
    // std::cout << "Original " << percent <<  " Percent: " << adjusted <<  "FPS: " << *fps << std::endl;
    return randomVal <= adjusted; 
}


void Tree::enterNoTree()
{
    treeState = 0;
    heightPercent = 1.0f;
    numberOfNoTrees++;
    creationTime = *(unitClock);
    //std::cout << *unitClock << " A burned tree rotted away... bare rock now\n";
}
void Tree::exitNoTree()
{
    numberOfNoTrees--;
}
void Tree::enterAlive()
{
    treeState = 1;
    heightPercent = 0.0f;
    numberOfTreesAlive++;

    creationTime = *(unitClock);
    //std::cout << *unitClock << " A tree grew in a new spot!!\n";

    for (int i=0; i < numberOfNeighbors; i++)
    {
        Tree* tree = neighborTrees[i];
        tree->registerNeighborAlive();
    }
}
void Tree::exitAlive()
{
    numberOfTreesAlive--;
}

void Tree::enterBurning()
{
    treeState = 2;
    numberOfTreesBurning++;
    heightPercent = 1.0f;
    burnTime = *(unitClock);

    //std::cout << *unitClock << " My ID: " << treeID << " Tree on fire!\n";
    // std::cout << "Alert # neighbors: " << numberOfNeighbors << std::endl;
    for (int i = 0; i < numberOfNeighbors; i++)
    {
        Tree* tree = neighborTrees[i];
        tree->registerNeighborFire();
    }
}

void Tree::exitBurning()
{
    numberOfTreesBurning--;
    for (int i=0; i < numberOfNeighbors; i++)
    {
        Tree* tree = neighborTrees[i];
        tree->regieterNeighborNoFire();
        tree->registerNeighborNotAlive();
    }

    if(treeFireStarter)
    {
        treeFireStarter = false;
        numberOfFireStarts -= 1;
    }
}

void Tree::enterBurned()
{
    heightPercent = 0.20f;
    numberOfTreesBurned++;
    treeState = 3;
    creationTime = *(unitClock);
}
void Tree::exitBurned()
{
    numberOfTreesBurned--;
}


void Tree::simNoTree()
{
    if(treeState != 0)
    {
        return;
    }
    if(randomIF(forest->TREE_NEW_GROW_RATE))
    {
        exitNoTree();
        enterAlive(); 
    }    
} 


void Tree::simAliveTree()
{
    if(treeState != 1)
    {
        return;
    }


    // change alive to burning 10 precent of the time
    float age = *(unitClock) - creationTime;
    float percentToBurning = forest->TREE_BURN_CHANCE_MIN + forest->TREE_BURN_AGE_FACTOR * age;
    if(percentToBurning > forest->TREE_BURN_CHANCE_MAX)
    {
        percentToBurning = forest->TREE_BURN_CHANCE_MAX;
    }
    if(randomIF(percentToBurning))
    {
        std::cout << "Fire Started! TreeID: " << treeID << " Fire Percentage: " << percentToBurning << std::endl;
        numberOfFireStarts++;
        treeFireStarter = true;
        exitAlive();
        enterBurning();
        return;
    }

    if(randomIF(neighborsOnFire * forest->TREE_NEIGHBOR_BURN_FACTOR / numberOfNeighbors))
    {  
    //    std::cout << "I am Alive. MyID: " << treeID << " Percent to burn: " << percentToBurning << std::endl;
        exitAlive();
        enterBurning();
    }
}

void Tree::simBurningTree()
{
    if (treeState != 2)
    {
        return;
    }
    // get chance to completely burn...
}

void Tree::simBurnedTree()
{
    if (treeState != 3)
    {
        return;
    }

    //regrow
    if(randomIF(forest->TREE_REGROW_FLAT_RATE))
    {
        exitBurned();
        enterAlive(); 
        return;
    }

    // die completely
    if(randomIF(forest->TREE_COMPLETE_DEATH_RATE))
    {
        exitBurned();
        enterNoTree();
    }
    

}

void Tree::registerNeighborFire() // called be the tree reciving the fire
{
   // std::cout << "Neighbor on fire! My ID: " << treeID << std::endl;
    neighborsOnFire += 1;
}

void Tree::regieterNeighborNoFire()
{
//    std::cout << "Neighbor fire went out! " << treeID << std::endl;
    neighborsOnFire -= 1;
}

void Tree::registerNeighborAlive() // called be the tree reciving the fire
{
   // std::cout << "Neighbor on fire! My ID: " << treeID << std::endl;
    neighborsAlive += 1;
}

void Tree::registerNeighborNotAlive()
{
   // std::cout << "Neighbor not alive! " << treeID << std::endl;
    neighborsAlive -= 1;
}

void Tree::simulate()
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