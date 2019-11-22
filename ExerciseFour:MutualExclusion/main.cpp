//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

/*! \file main.cpp
    \brief An implementation of mutual exclusion.
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

static const int num_threads = 100;
int sharedVariable=0;

/*! \brief An implementation of a mutual exclusion.
    All threads have access to a shared variable and are trying to increment it.
    Mutual exclusion must be implemented to prevent a race condition

    \return num_threads * 10000
    \param num_threads is the number of threads used
    \param aSemaphore Semaphore object initialised to open
 */

/*! \mainpage Lab 4

    \section Mutual Exclusion
    This lab demonstrates a mutual exclusion.
    A number of threads try to increment a shared variable and mutual
    exclusion will be used to prevent a race condition.

 */

/*! \fn void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief updateTask is carried out by each thread
    \param firstSem Semaphore object
    \param numUpdates int to be used for incrementations
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){
  for(int i=0;i<numUpdates;i++){
    firstSem->Wait();
    //UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
    firstSem->Signal();
  }
}

int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore(new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
