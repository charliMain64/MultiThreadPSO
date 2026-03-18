#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include "Eigen/Dense"
#include <omp.h>
#include <chrono>
#include <string>

double contourFunction(double x, double y) {
    double contour = pow(x - 0.4,2) + pow(y - 0.6, 2) -0.4;
    return contour;
}

// Can define other contour/objective functions here
int main(int argc, char *argv[]) {
    //*****if running in terminal this is the correct format for each argument  (threads/particles/iterations/write(y for write))

    bool debugFlag = false;
    int iterationHop;
    bool writeFileFlag;


    // if (argc >= 1) {
    //     debugFlag = atoi(argv[3]);
    // } else {
    //     debugFlag = true;
    // }

    // std::ofstream particleCordFile;
    //std::cout << contourFunction(4.7, 3.2) << std::endl;

    // if (writeFileFlag) {
    //     particleCordFile << "particle,iter,x,y,z,vx,vy" << std::endl;
    // }

    //num threads inputted
    int numThreads;
    if (argc >= 2) {
        numThreads = atoi(argv[1]);
    } else {
        numThreads = 1;
    }
    omp_set_num_threads(numThreads);

    if (numThreads <= 10) {
        iterationHop = 20;
    }else if (numThreads >= 11 && numThreads <= 20) {
        iterationHop = 40;
    }else if (numThreads >= 21 && numThreads <= 30) {
        iterationHop = 80;
    }else {
        iterationHop = 100;
    }

    //num particles to use
    int numParticles;
    if (argc >= 3) {
        numParticles = atoi(argv[2]);
    } else {
        numParticles = 10;
    }

    //number of iterations
    int numIters;
    if (argc >= 4) {
        numIters = atoi(argv[3]);
    } else {
        numIters = 100000;
    }

    if (argc >= 5) {
        std::string write = argv[4];
        if (write == "y") {
            writeFileFlag = true;
        }else {
            writeFileFlag = false;
        }
    }else {
        writeFileFlag = false;
    }
    // std::cout << "numThreads: " << numThreads << std::endl;

    std::ofstream particleCordFile("particleCords.txt");
    if (writeFileFlag) {
        //std::cout << "Before calculations \n" << std::endl;
        std::ofstream clearCordFile("particleCords.txt", std::ios::out | std::ios::trunc);
        clearCordFile.close();
        //std::ofstream particleCordFile("particleCords.txt");
        particleCordFile << "particle,iter,x,y,z,vx,vy" << std::endl;
    }

    //random generator init (supposedly closer to true random)
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    //this creates a 2d array of 100 particles and 3 columns per particle each row is used for an x,y,z
    Eigen::Matrix <double, Eigen::Dynamic, 3> particle(numParticles, 3);
    //this is used to find the particle with the best location
    Eigen::Matrix <double, Eigen::Dynamic, 3> particleBest(numParticles, 3);

    // Starting time point
    auto start = std::chrono::high_resolution_clock::now();
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
         if (writeFileFlag) {
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
        if (writeFileFlag) {
            std::cout << "start: " << xVal << " | " << yVal << " | " << zVal << "\n" << std::endl;
        }
    }

    ////////////////Velocity Calculations//////////////////

    //initialize velocity to the number of particles and set their start velocity to 0
    //float velocity[numParticles][2];
    Eigen::Matrix <double, Eigen::Dynamic, 2> velocity(numParticles, 2);
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
        #pragma omp parallel for
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


            if (i % iterationHop == 0) {
                #pragma omp critical
                if (z < globalBest(0,2)) {
                    for (int i = 0; i < 3; i++) {
                        globalBest(0,i) = particleBest(j,i);
                    }
                }
            }
            if (writeFileFlag) {
                #pragma omp critical
                particleCordFile << j + 1 << "," << i + 1 << "," << particle(j,0) << "," << particle(j,1) << "," << particle(j,2) << "," << velocity(j,0) << "," << velocity(j,1) << std::endl;
                //#pragma omp critical
                // if (writeFileFlag) {
                    // particleCordFile << j + 1 << "," << i + 1 << "," << particle(j,0) << "," << particle(j,1) << "," << particle(j,2) << "," << velocity(j,0) << "," << velocity(j,1) << std::endl;
                // }
            }
        }
    }

    //particleCordFile << "After Calculations:" << std::endl;
    for (int i = 0; i < numParticles; i++) {
        xVal = particle(i,0);
        yVal = particle(i,1);
        zVal = particle(i,2);
        if (writeFileFlag) {
             std::cout << "final: " << particle(i,0) << " | " << particle(i,1) << " | " << particle(i,2) << "\n" << std::endl;
        }
        if (writeFileFlag) {
            particleCordFile << i << "," << numIters + 1 << "," << xVal << "," << yVal << "," << zVal << "," << 0 << "," << 0 << std::endl;
        }
    }
    if (writeFileFlag) {
        particleCordFile.close();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Run time: " << duration << std::endl;
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