//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

#include "SafeBuffer.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>

static const int num_threads = 100;
const int numLoops = 20;

/*! \file main.cpp
    \brief Run two threads, one's consumer, one's producer.
*/

/*! \brief Run two threads, one's consumer, one's producer.
    Demonstates the Producer-Consumer Solution

    \param numLoops number of times event will be produced
    \param num_threads number of threads created
 */

/*! \mainpage Lab 6
    \section Producer-Consumer
    Demonstates the Producer-Consumer Solution
 */

/*! \fn producer
    \brief Creates events and adds them to buffer
    \param theBuffer
    \param numLoops number of times event will be produced
*/
void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
{

  for (int i = 0; i < numLoops; ++i)
  {
    //Produce event and add to buffer
    Event e;
    theBuffer->push(e);
  }
}

/*! \fn consumer
    \brief Takes events from buffer and consumes them
    \param theBuffer
    \param numLoops number of times event will be produced
*/
void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
{

  for (int i = 0; i < numLoops; ++i)
  {
    //Produce event and add to buffer
    Event e = theBuffer->pop();
    e.consume();
  }
}

int main(void)
{

  std::vector<std::thread> producers(num_threads);
  std::vector<std::thread> consumers(num_threads);
  std::shared_ptr<SafeBuffer> aBuffer(new SafeBuffer());
  /**< Launch the threads  */
  for (std::thread &p : producers)
  {
    p = std::thread(producer, aBuffer, numLoops);
  }
  for (std::thread &c : consumers)
  {
    c = std::thread(consumer, aBuffer, numLoops);
  }
  /**< Join the threads with the main thread */
  for (auto &p : producers)
  {
    p.join();
  }
  for (auto &c : consumers)
  {
    c.join();
  }
  std::cout << std::endl;
  return 0;
}
