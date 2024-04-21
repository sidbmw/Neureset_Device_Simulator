#ifndef VISUAL_FEEDBACK_H
#define VISUAL_FEEDBACK_H

class VisualFeedback
{
public:
    VisualFeedback();
    ~VisualFeedback();

    // Turns on the green light indicating treatment is being delivered
    void turnOnGreenLight();

    // Turns off the green light indicating treatment has stopped
    void turnOffGreenLight();

    // Turns on the blue light indicating electrode contact
    void turnOnBlueLight();

    // Turns on the red light indicating an error or warning
    void turnOnRedLight();

    // Starts the beeping sound to alert the user
    void startBeeping();

    // Stops the beeping sound
    void stopBeeping();

private:
    bool isGreenLight;
    bool isBlueLight;
    bool isRedLight;
    bool isBeeping;
};

#endif
