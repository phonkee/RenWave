/*
  ==============================================================================

    Project.h
    Created: 14 Mar 2020 1:48:00am
    Author:  Peter Vrba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DesignWindow.h"
#include "WaveWindow.h"
#include "Tools.h"

//==============================================================================
/*
 * Project
 *
*/
class Project : public Component {
public:
    // trivial constructor (very helpful comment)
    Project();

    // destructor (very helpful comment)
    ~Project() override;

    // paint is called when we want to paint component
    void paint(Graphics &) override;

    // resized is called when component is resized
    void resized() override;

    // ---- Custom methods ----

    // readFile reads given file
    void readFile(String &filename);

private:

    // design window where we manipulate all tools
    DesignWindow designWindow;

    // window for wave
    WaveWindow waveWindow;

    // prepare list of selected tools
    std::shared_ptr<std::vector<Tool>> tools;

    // Juce related macros
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project)
};
