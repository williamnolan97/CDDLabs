//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

#include <mutex>
#include "Semaphore.h"
#include <queue>

/*! \file SafeBuffer.h
    \brief SafeBuffer header file.
 */
class SafeBuffer {
 public:
  std::shared_ptr<Semaphore> mutex;
  std::shared_ptr<Semaphore> items;
  std::shared_ptr<Semaphore> spaces;
  std::queue<char> safeBuffer;
  SafeBuffer();
  void Push(char);
  char Pop();
};
