//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

/*! \file main.cpp
    \brief Demonstrates the Producer-Consumer problem
*/

#include "SafeBuffer.h"
#include <iostream>
#include <chrono>
#include <thread>

int characterCountBuffer[26] = {0};
int num_threads = 5;

/*! \brief Demonstrates the Producer-Consumer problem

    \return The occurance of each character in the SafeBuffer
    \param sBuff the SafeBuffer
    \param num_threads number of threads created
    \param characterCountBuffer Main Buffer for counting characters consumed
 */

/*! \mainpage Lab 6
    \section Producer-Consumer
    Demonstrates the Producer-Consumer problem
 */

/*! \fn void consumer
    \brief removes a character from the safe buffer, at random time intevals and
    keeps track of the count of each letter removed.
    \param sBuff the SafeBuffer
*/
void consumer(std::shared_ptr<SafeBuffer> sBuff) {
  char c;
  while (c != 'X')
  {
     c = sBuff->Pop();
     std::cout << "Consuming " << c << std::endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
     characterCountBuffer[c]++;
  }
}

/*! \fn void producer
    \brief producer adds a random character to a safe buffer, at random timer intervals.
    When it has produced numCharacters amount of items it pushs 'X' to the buffer to signal the end.
    \param sBuff the SafeBuffer
    \param numCharacters number of characters per thread
*/
void producer(std::shared_ptr<SafeBuffer> sBuff, int numCharacters) {
  char c;
  int i = 0;
  while ( i <= numCharacters)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
    c =  std::rand() % 26 + 97;
    sBuff->Push(c);
    i++;
    std::cout << "Producing " << c << std::endl;
  }
  sBuff->Push('X');
}

/*! \fn void printCharCount
    \brief producer adds a random character to a safe buffer, at random timer intervals.
    When it has produced numCharacters amount of items it pushs 'X' to the buffer to signal the end.
*/
void printCharCount() {
  for ( char i = 97; i < 123; ++i ) {
    std::cout << i << ":" << characterCountBuffer[i] << std::endl;
  }
  std::cout << "Characters have been counted" << std::endl;
}

int main(void) {
  int numCharacters;
  std::shared_ptr<SafeBuffer> sBuff(new SafeBuffer);
  std::thread producerThread[num_threads];
  std::thread consumerThread[num_threads];

  std::cout << "How many characters will each thread use?" << std::endl;
  std::cin >> numCharacters;

  for ( int i = 0; i < 5; i++ ) {
    producerThread[i] = std::thread(producer, sBuff, numCharacters);
    consumerThread[i] = std::thread(consumer, sBuff);
  }

  for ( int i = 0; i < 5; i++ ) {
    producerThread[i].join();
    consumerThread[i].join();
  }

  printCharCount();
  return 0;
}
