#include <iostream>
#include <cmath>
#include <random>
#include <Eigen/Dense>

float contourFunction(float x, float y) {
    float contor = pow(x - 0.4,2) + pow(y - 0.6, 2) -0.4;
    return contor;
}

int main() {

    //std::cout << contourFunction(4.7, 3.2) << std::endl;
    std::cout << "Before calculations \n" << std::endl;


    const int numParticles = 10;

    // int xBounds[2];
    // xBounds[0] = -1;
    // xBounds[1] = 1;
    //
    // int yBounds[2];
    // yBounds[0] = -1;
    // yBounds[1] = 1;

    //random generator init (supposedly closer to true random)
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    //this creates a 2d array of 100 particles and 3 columns per particle each row is used for an x,y,z
    //float particle[numParticles][3];
    Eigen::Matrix <float, numParticles, 3> particle;
    //this is used to find the particle with the best location
    //float particleBest[numParticles][3];
    Eigen::Matrix <float, numParticles, 3> particleBest;

    //for each particle assign it to a random x and y coordinate
    for (int i = 0; i < numParticles; i++) {
        float x = dist(gen);
        float y = dist(gen);

        /*z takes the x and y of the randomly placed particle and assigns it to the contour function and
         *returns the z of the particle*/
        float z = contourFunction(x, y);

        //stores the particles coordinates
        particle(i, 0) = x;
        particle(i, 1) = y;
        particle(i, 2) = z;
        particleBest(i, 0) = x;
        particleBest(i, 1) = y;
        particleBest(i, 2) = z;
    }
    //used to hold the x, y and z of the global best
    Eigen::Matrix <float, 1, 3> globalBest;
    //float globalBest[3];
    globalBest(0, 0) = 0.0f;
    globalBest(0, 1) = 0.0f;
    globalBest(0, 2) = 0.0f;

    //go through particle array and find which one has the best value (lowest z value) and set it to new global best
    for (int i = 0; i < numParticles; i++) {
        if (particleBest(i, 2) == particle(i, 2)) {
            for (int j = 0; j < 3; j++) {
                globalBest(0,j) = particleBest(i,j);
            }
        }
    }

    float xVal;
    float yVal;
    float zVal;

    for (int i = 0; i < numParticles; i++) {
        xVal = particle(i, 0);
        yVal = particle(i, 1);
        zVal = particle(i, 2);
        std::cout << "start: " << xVal << " | " << yVal << " | " << zVal << "\n" << std::endl;
    }

    ////////////////Velocity Calculations//////////////////
    std::cout << "After calculations \n" << std::endl;

    //initialize velocity to the number of particles and set their start velocity to 0
    //float velocity[numParticles][2];
    Eigen::Matrix <float, numParticles, 2> velocity;
    for (int i = 0; i < numParticles; i++) {
        velocity(i,0) = 0;
        velocity(i,1) = 0;
    }

    //Inertia weight (w) constant, between 0 and 1 and determines how much should the particle keep on with its previous velocity
    float w = 0.05;

    /*
     * The parameters 𝑐1 and 𝑐2 are called the cognitive and the social coefficients respectively.
     * They controls how much weight should be given between refining the search result of the particle
     * itself and recognizing the search result of the swarm.
     * We can consider these parameters controls the trade off between exploration and exploitation. */

    //Individual weight (c1),
    float c1 = 0.005;

    //Global weight (c2),
    float c2 = 0.001;

    //𝑟1 and 𝑟2 are random numbers between 0 and 1
    std::uniform_real_distribution<float> distTwo(0.0f, 1.0f);
    float r1 = distTwo(gen);//r1 pulls particle toward personal best
    float r2 = distTwo(gen);//r2 pulls particle toward global best

    for (int i = 0; i < 100000; i++) {
        //Updates particle velocity and position; tracks best positions
        for (int j = 0; j < numParticles; j++) {
            //iterating through particles
            for (int k = 0; k < 2; k++) {
                //iterating both x and y for velocity and particle
                velocity(j,k) = w * velocity(j,k) + c1 * r1 * (particleBest(j,k) - particle(j,k)) + c2 * r2 * (globalBest(0,k) - particle(j,k));
                particle(j,k) += velocity(j,k);
            }
            float z = contourFunction(particle(j,0), particle(j,1)); //get z of the particle at that x and y
            particle(j,2) = z; //set z to the particle

            if (z < particleBest(j,2)) {
                for (int i = 0; i < 3; i++) {
                    particleBest(j,i) = particle(j,i);
                }
            }
            if (z < globalBest(0,2)) {
                for (int i = 0; i < 3; i++) {
                    globalBest(0,i) = particleBest(j,i);
                }
            }
        }
    }

    for (int i = 0; i < numParticles; i++) {
        xVal = particle(i,0);
        yVal = particle(i,1);
        zVal = particle(i,2);
        std::cout << "final: " << xVal << " | " << yVal << " | " << zVal << "\n" << std::endl;
    }

    return 0;
}