#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include "Eigen/Dense"
#include <omp.h>

double contourFunction(double x, double y) {
    double contour = pow(x - 0.4,2) + pow(y - 0.6, 2) -0.4;
    return contour;
}

// Can define other contour/objective functions here

int main(int argc, char *argv[]) {

    //std::cout << contourFunction(4.7, 3.2) << std::endl;
    std::cout << "Before calculations \n" << std::endl;
    std::ofstream clearCordFile("particleCords.txt", std::ios::out | std::ios::trunc);
    clearCordFile.close();
    std::ofstream particleCordFile("particleCords.txt");
    bool debugFlag = true;

    if (debugFlag) {
        particleCordFile << "particle,iter,x,y,z,vx,vy" << std::endl;
    }

    const int numParticles = 10;
    //omp_set_num_threads(numParticles);
    const int numIters = 100000;

    //check if opm is working (ask Evan if this is what he meant)
    #ifdef _OPENMP
        omp_set_num_threads(numParticles);
    #else
        omp_set_num_threads(1);
    #endif

    //random generator init (supposedly closer to true random)
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    //this creates a 2d array of 100 particles and 3 columns per particle each row is used for an x,y,z
    Eigen::Matrix <double, numParticles, 3> particle;
    //this is used to find the particle with the best location
    Eigen::Matrix <double, numParticles, 3> particleBest;

    //for each particle assign it to a random x and y coordinate
    for (int i = 0; i < numParticles; i++) {
        double x = dist(gen);
        double y = dist(gen);

        /*z takes the x and y of the randomly placed particle and assigns it to the contour function and
         *returns the z of the particle*/
        double z = contourFunction(x, y);

        //stores the particles coordinates
        particle(i, 0) = x;
        particle(i, 1) = y;
        particle(i, 2) = z;
        particleBest(i, 0) = x;
        particleBest(i, 1) = y;
        particleBest(i, 2) = z;
        if (debugFlag) {
            particleCordFile << i +1 << "," << 0 << "," << x << "," << y << "," << z << "," << 0 << "," << 0 << std::endl;
        }
    }
    //used to hold the x, y and z of the global best
    Eigen::Matrix <double, 1, 3> globalBest;
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

    double xVal;
    double yVal;
    double zVal;

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
    Eigen::Matrix <double, numParticles, 2> velocity;
    for (int i = 0; i < numParticles; i++) {
        velocity(i,0) = 0;
        velocity(i,1) = 0;
    }

    //Inertia weight (w) constant, between 0 and 1 and determines how much should the particle keep on with its previous velocity
    double w = 0.05;

    /*
     * The parameters 𝑐1 and 𝑐2 are called the cognitive and the social coefficients respectively.
     * They controls how much weight should be given between refining the search result of the particle
     * itself and recognizing the search result of the swarm.
     * We can consider these parameters controls the trade off between exploration and exploitation. */

    //Individual weight (c1),
    double c1 = 0.005;

    //Global weight (c2),
    double c2 = 0.001;

    //𝑟1 and 𝑟2 are random numbers between 0 and 1
    std::uniform_real_distribution<float> distTwo(0.0f, 1.0f);
    double r1 = distTwo(gen);//r1 pulls particle toward personal best
    double r2 = distTwo(gen);//r2 pulls particle toward global best


    for (int i = 0; i < numIters; i++) {
        //Updates particle velocity and position; tracks best positions
        #pragma omp parallel for schedule(static) num_threads(numParticles)
        for (int j = 0; j < numParticles; j++) {
            // #pragma omp critical
            // std::cout << "particle " << j << " thread " << omp_get_thread_num() << std::endl;
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
            #pragma omp critical
            if (z < globalBest(0,2)) {
                for (int i = 0; i < 3; i++) {
                    globalBest(0,i) = particleBest(j,i);
                }
            }
            #pragma omp critical
            if (debugFlag) {
                particleCordFile << j + 1 << "," << i + 1 << "," << particle(j,0) << "," << particle(j,1) << "," << particle(j,2) << "," << velocity(j,0) << "," << velocity(j,1) << std::endl;
            }
        }
    }

    particleCordFile << "After Calculations:" << std::endl;
    for (int i = 0; i < numParticles; i++) {
        xVal = particle(i,0);
        yVal = particle(i,1);
        zVal = particle(i,2);
        std::cout << "final: " << particle(i,0) << " | " << particle(i,1) << " | " << particle(i,2) << "\n" << std::endl;
        if (debugFlag) {
            particleCordFile << i << "," << numIters + 1 << "," << xVal << "," << yVal << "," << zVal << "," << 0 << "," << 0 << std::endl;
        }
    }
    //particleCordFile.close();
    if (particleCordFile.is_open()) {
        particleCordFile << "Some data\n";
        particleCordFile.flush(); // Force write to disk
        particleCordFile.close();// is called automatically
    }
    return 0;
}


// #pragma omp parallel for schedule(static) threads(THREADS)
// if (environment variable OMP_NUM_THREADS exists in the underlying shell process) {
//     use threads = OMP_NUM_THREADS
// } else {
//     use threads = 1
// }
// for (int i = 0; i < N; i++) {
//     /* a loop that doesn't take very long */
//
// }