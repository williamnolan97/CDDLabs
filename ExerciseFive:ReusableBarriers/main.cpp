#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>

/*! \file main.cpp
    \brief Runs a number of threads and makes them wait at a barrier before proceeding.
*/

static const int num_threads = 100;
int sharedVariable=0;

/*! \mainpage Lab 5
    \section Reusable Barriers
    Creates a barrier for a number of threads
 */

/*! \fn barrierTask
    \brief An example of using a reusable barrier
    \param theBarrier the barrier for the threads to used
    \param numLoops the amount of loops the threads go through
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops)
{

  for (int i = 0; i < numLoops; ++i)
  {
    theBarrier->wait();
    //Do first bit of task
    std::cout << "A" << i;
    //Barrier
    theBarrier->wait();
    //Do second half of task
    std::cout << "B" << i;
  }
}

int main(void)
{
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier(new Barrier(num_threads));
  /**< Launch the threads  */
  int i = 0;
  for (std::thread &t : vt)
  {
    t = std::thread(barrierTask, aBarrier, 10);
  }
  /**< Join the threads with the main thread */
  for (auto &v : vt)
  {
    v.join();
  }
  return 0;
}
