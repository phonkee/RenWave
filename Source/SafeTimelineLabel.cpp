/*
  ==============================================================================

    SafeTimelineLabel.cpp
    Created: 9 Mar 2020 1:27:14am
    Author:  Peter Vrba

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SafeTimelineLabel.h"
#include "Settings.h"
#include <chrono>
#include <iomanip>
#include <optional>
#include <ostream>

String formatDuration(std::chrono::nanoseconds ns) {
    using namespace std::chrono;

    std::stringstream os;

    using days = duration<int, std::ratio<86400>>;
    auto d = duration_cast<days>(ns);
    ns -= d;
    auto h = duration_cast<hours>(ns);
    ns -= h;
    auto m = duration_cast<minutes>(ns);
    ns -= m;
    auto s = duration_cast<seconds>(ns);
    ns -= s;
    auto ms = duration_cast<milliseconds>(ns);
    ns -= ms;

    std::optional<int> fs_count;
    switch (os.precision()) {
        case 9:
            fs_count = ns.count();
            break;
        case 6:
            fs_count = duration_cast<microseconds>(ns).count();
            break;
        case 3:
            fs_count = duration_cast<milliseconds>(ns).count();
            break;
    }

    char fill = os.fill('0');
    os << std::setw(2) << h.count() << ":";
    os << std::setw(2) << m.count() << ":";
    os << std::setw(2) << s.count() << ":";
    os << std::setw(2) << s.count();

    os.fill(fill);
    return String{os.str()};
}

//==============================================================================
SafeTimelineLabel::SafeTimelineLabel() {

    // set framerate
    setFramesPerSecond(settings::framePerSecond);

    using namespace std::chrono_literals;

    // set duration to zero
    nanoDuration = 0s;
}

SafeTimelineLabel::~SafeTimelineLabel() {
}

void SafeTimelineLabel::paint(Graphics &g) {
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

//    g.setColour(Colours::darkgrey);

//    auto rect = getLocalBounds();
//    g.drawRect(rect, 2);   // draw an outline around the component

    g.setColour(Colours::white);
    g.setFont(14.0f);

    g.drawText(formatDuration(nanoDuration), getLocalBounds(),
               Justification::centred, true);   // draw some placeholder text
}

void SafeTimelineLabel::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

const std::chrono::nanoseconds &SafeTimelineLabel::getNanoDuration() const {
    return nanoDuration;
}

void SafeTimelineLabel::setNanoDuration(const std::chrono::nanoseconds &duration) {
    this->nanoDuration = duration;
}

float SafeTimelineLabel::getFontHeight() const {
    return fontHeight;
}

void SafeTimelineLabel::setFontHeight(float height) {
    this->fontHeight = height;
}

void SafeTimelineLabel::update() {
//    DBG(rand());
}

