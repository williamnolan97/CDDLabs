//Author: William Nolan
//Creation Date: 21-11-2019
//Licence: GNU

#include "SafeBuffer.h"

/*! \file SafeBuffer.cpp
    \brief Consumer, securely takes and prints data.
*/

/*! \fn SafeBuffer()
    \brief Constructor for SafeBuffer object. Sets the mutex and semaphore.
*/
SafeBuffer::SafeBuffer()
{
    mutex = std::make_shared<Semaphore>(1);
    semaphore = std::make_shared<Semaphore>(0);
}

/*! \fn int push(Event newEvent)
    \brief Pushes the event onto the buffer.
    \param newEvent the event that is to be pushed.
*/
int SafeBuffer::push(Event newEvent)
{
    mutex->Wait();
    data.push_back(newEvent);
    int size = data.size();
    mutex->Signal();
    semaphore->Signal();
    return size;
}

/*! \fn Event pop()
    \brief Pops the element from the buffer.
*/
Event SafeBuffer::pop()
{
    semaphore->Wait();
    mutex->Wait();
    Event e = data.back();
    data.pop_back();
    mutex->Signal();
    return e;
}
