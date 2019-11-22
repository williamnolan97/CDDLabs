//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU 

/*! \file Barrier.cpp
    \brief Barrier class implementation.

    Creates a barrier for a number of threads.
*/

// Code:
#include "Semaphore.h"
#include "Barrier.h"

Barrier::Barrier(int numThreads)
{
    this->numThreads = numThreads;
    this->turnstile1 = std::shared_ptr<Semaphore>(new Semaphore(0));
    this->turnstile2 = std::shared_ptr<Semaphore>(new Semaphore(1));
    this->mutex = std::shared_ptr<Semaphore>(new Semaphore(1));
}

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

Barrier::~Barrier()
{
}

//
// Barrier.cpp ends here
