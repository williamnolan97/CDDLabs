/* Code: */

#include "SafeBuffer.h"

SafeBuffer::SafeBuffer()
{
    theMutex = std::make_shared<Semaphore>(1);
    theSemaphore = std::make_shared<Semaphore>(0);
}

int SafeBuffer::push(Event newEvent)
{
    theMutex->Wait();
    theData.push_back(newEvent);
    int size = theData.size();
    theMutex->Signal();
    theSemaphore->Signal();
    return size;
}

Event SafeBuffer::pop()
{
    theSemaphore->Wait();
    theMutex->Wait();
    Event e = theData.back();
    theData.pop_back();
    theMutex->Signal();
    return e;
}
