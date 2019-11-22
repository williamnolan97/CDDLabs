//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/** @brief An implementation of a semaphore. Thread associated with taskTwo must wait to be signalled by
 * task associated with taskOne.
 *
 * @return a message
 * @param sem shared semaphore object
 * @param taskOneDelay represents the time for the thread to sleep.
 */

/*! \mainpage Lab 2
 *
 * \section Semaphores
 *
 * This lab demonstrates semaphores by getting two threads to execute a task each.
 * The second task may only begin once it has been signalled by task one.
 *
 */

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief Description of void taskOne function
    \param theSemaphore share semaphore between two threads created in main
    \param delay used for sleep() function
    \details This function will always run first while taskTwo waits, then signals taskTwo to begin
*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief Description of void taskTwo function
    \param theSemaphore shared semaphore between two threads created in main
    \details This function runs second once it has been signaled by taskOne
*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
