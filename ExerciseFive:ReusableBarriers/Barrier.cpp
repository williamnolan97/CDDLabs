//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

/*! \file Barrier.cpp
    \brief Barrier class implementation.
    Creates a barrier for a number of threads
 */

// Code:
#include "Semaphore.h"
#include "Barrier.h"

/*! \fn Barrier(int numThreads)
    \brief Barrier class constructor. Sets number of Threads and initializes the semaphores and the mutex.
    \param numThreads the number of threads.

    Creates the Barrier object.
*/
Barrier::Barrier(int numThreads)
{
    this->numThreads = numThreads;
    this->turnstile1 = std::shared_ptr<Semaphore>(new Semaphore(0));
    this->turnstile2 = std::shared_ptr<Semaphore>(new Semaphore(1));
    this->mutex = std::shared_ptr<Semaphore>(new Semaphore(1));
}

/*! \fn void wait()
    \brief Function used to force threads to wait for other threads.

    All threads meet at the barrier before they can proceed.
*/
void Barrier::wait()
{
    mutex->Wait();
    threadCount++;

    if (threadCount == numThreads)
    {
        turnstile2->Wait();
        turnstile1->Signal();
    }
    mutex->Signal();

    turnstile1->Wait();
    turnstile1->Signal();

    mutex->Wait();

    threadCount--;
    if (threadCount == 0)
    {
        turnstile1->Wait();
        turnstile2->Signal();
    }
    mutex->Signal();

    turnstile2->Wait();
    turnstile2->Signal();
}

/*! \fn ~Barrier()
    \brief Virtual deconstructor
*/
Barrier::~Barrier()
{
}

//
// Barrier.cpp ends here
