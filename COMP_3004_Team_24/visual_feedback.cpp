#ifndef VISUAL_FEEDBACK_H
#define VISUAL_FEEDBACK_H

class VisualFeedback {
public:
    VisualFeedback();
    ~VisualFeedback();

    // Turns on the green light indicating treatment is being delivered
    void turnOnGreenLight();

    // Turns off the green light indicating treatment has stopped
    void turnOffGreenLight();

    // Turns on the blue light indicating session start
    void turnOnBlueLight();

    // Turns on the red light indicating contact loss
    void turnOnRedLight();

    // Starts beeping to indicate contact loss
    void startBeeping();

    // Stops beeping - GG
    void stopBeeping();
};

#endif 
