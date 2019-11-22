//Author: William Nolan
//Creation Date: 22-11-2019
//Licence: GNU

#include "Event.h"
#include <iostream>
#include <stdlib.h>

/*! \file Event.cpp
    \brief Event class implementation

    Runs two threads. Thread two needs to wait for thread one before proceeding.
*/

/*! \fn Event()
    \brief Constructor for the Event class. Creates a random character and prints it out.
*/
Event::Event()
{
    c = 'a' + rand() % 26;
    std::cout << c;
}

/*! \fn bool consume()
    \brief Consumes, creates a character in CAPS and prints it out.
*/
void Event::consume()
{
    char upperC = c - 32;
    std::cout << upperC;
}
