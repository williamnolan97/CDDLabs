//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/** @brief An implementation of a rendezvous.
 * A message is displayed in two parts. Both threads must arrive at the
 * rendezvous point before they can continue. TaskOne is carried out by
 * threadOne, taskTwo is carried out by threadTwo.
 *
 * @return either part one/two of the message
 * @param sem1 Semaphore object representing firstThread arrival
 * @param sem2 Semaphore object representing secondThread arrival
 * @param taskOneDelay represents the time taskOne should sleep for
 * @param taskTwoDelay represents the time taskTwo should sleep for
 */

/*! \mainpage Lab 3
 *
 * \section Rendezvous
 *
 * This lab demonstrates a rendezvous.
 * A message is displayed in two parts.
 * Both threads must arrive at one point (the rendezvous) before they can continue.
 *
 */

/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore> secondSem, int delay)
   \brief taskTwo is carried out by thread two
   \param firstSem Semaphore object to indicate first arrival
   \param secondSem Semaphore object to indicate second arrival
   \param delay int to be used for sleep_for() function
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  firstSem->Signal();
  //Rendezvous point
  secondSem->Wait();
  std::cout << "Task One has left!"<<std::endl;
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore> secondSem, int delay)
    \brief taskTwo is carried out by thread two
    \param firstSem Semaphore object to indicate first arrival
    \param secondSem Semaphore object to indicate second arrival
    \param delay int to be used for sleep_for() function
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  secondSem->Signal();
  //Rendezvous point
  firstSem->Wait();
  std::cout << "Task Two has left "<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
