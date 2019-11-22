//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

 #pragma once
 #include "Event.h"
 #include "Semaphore.h"
 #include <vector>

 /*! \file SafeBuffer.h
     \brief Consumer, securely takes and prints data.
 */

 class SafeBuffer
 {
   private:
     std::vector<Event> data;
     std::shared_ptr<Semaphore> mutex;
     std::shared_ptr<Semaphore> semaphore;

   public:
     SafeBuffer();
     int push(Event);
     Event pop();
 };



/* SafeBuffer.h ends here */
