//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU 

/* Code: */
#pragma once
#include "Semaphore.h"

class Barrier
{
  int numThreads;
  int threadCount;

  std::shared_ptr<Semaphore> mutex;
  std::shared_ptr<Semaphore> turnstile1;
  std::shared_ptr<Semaphore> turnstile2;

public:
  Barrier(int numThreads);
  virtual ~Barrier();
  void wait();
};

/* Barrier.h ends here */
