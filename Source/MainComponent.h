/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DesignWindow.h"
#include "WaveWindow.h"
#include "Project.h"
#include "SafeTimelineLabel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component {
public:
    //==============================================================================
    MainComponent();

    ~MainComponent() override;

    //==============================================================================
    void paint(Graphics &) override;

    void resized() override;

private:

    float padding = 4;

    // prepare project
    Project project;

    // Design window where we add/change various widgets
    DesignWindow designWindow;

    // Wave window holds wave and renders it appropriately
    WaveWindow wave;

    // timelineLabel
    SafeTimelineLabel timelineLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
