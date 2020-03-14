/*
  ==============================================================================

    SafeTimelineLabel.h
    Created: 9 Mar 2020 1:27:14am
    Author:  Peter Vrba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <chrono>

//==============================================================================
/*
*/
class SafeTimelineLabel : public AnimatedAppComponent {
public:
    SafeTimelineLabel();

    ~SafeTimelineLabel() override;

    void paint(Graphics &) override;

    void resized() override;

    void update() override;

private:
    CriticalSection mutex;

    // store actual time
    std::chrono::nanoseconds nanoDuration;
public:
    const std::chrono::nanoseconds &getNanoDuration() const;

    void setNanoDuration(const std::chrono::nanoseconds &duration);

private:

    // font height
    float fontHeight{14.0f};
public:
    float getFontHeight() const;

    void setFontHeight(float height);

private:

    // Juce related macros
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SafeTimelineLabel)
};
