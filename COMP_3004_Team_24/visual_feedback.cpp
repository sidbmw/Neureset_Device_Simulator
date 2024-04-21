#include "visual_feedback.h"
#include <iostream>

VisualFeedback::VisualFeedback()
{
    isGreenLight = false;
    isBlueLight = false;
    isRedLight = false;
    isBeeping = false;
}

VisualFeedback::~VisualFeedback()
{
}

void VisualFeedback::turnOnGreenLight()
{
    isGreenLight = true;
    // Implement hardware-specific code to turn on the green light
    std::cout << "Green light turned on" << std::endl;
}

void VisualFeedback::turnOffGreenLight()
{
    isGreenLight = false;
    // Implement hardware-specific code to turn off the green light
    std::cout << "Green light turned off" << std::endl;
}

void VisualFeedback::turnOnBlueLight()
{
    isBlueLight = true;
    // Implement hardware-specific code to turn on the blue light
    std::cout << "Blue light turned on" << std::endl;
}

void VisualFeedback::turnOnRedLight()
{
    isRedLight = true;
    // Implement hardware-specific code to turn on the red light
    std::cout << "Red light turned on" << std::endl;
}

void VisualFeedback::startBeeping()
{
    isBeeping = true;
    // Implement hardware-specific code to start the beeping sound
    std::cout << "Beeping started" << std::endl;
}

void VisualFeedback::stopBeeping()
{
    isBeeping = false;
    // Implement hardware-specific code to stop the beeping sound
    std::cout << "Beeping stopped" << std::endl;
}
