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
};

#endif 
