/*
  ==============================================================================

    LookAndFeel.h
    Created: 13 Mar 2020 10:30:14pm
    Author:  Peter Vrba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LookAndFeel_RenWave : public LookAndFeel_V4 {

public:
    LookAndFeel_RenWave() {
        setColour(TextButton::textColourOffId, Colours::lightgrey);
        setColour(TextButton::textColourOnId, Colours::lightgrey);
    }

    void drawButtonBackground(Graphics &g,
                              Button &button,
                              const Colour &backgroundColour,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown) override {
        auto cornerSize = 6.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
                .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

        g.setColour(baseColour);

        auto flatOnLeft = true; // button.isConnectedOnLeft();
        auto flatOnRight = true; // button.isConnectedOnRight();
        auto flatOnTop = true; // button.isConnectedOnTop();
        auto flatOnBottom = true; // button.isConnectedOnBottom();

        if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom) {
            Path path;
            path.addRoundedRectangle(bounds.getX(), bounds.getY(),
                                     bounds.getWidth(), bounds.getHeight(),
                                     cornerSize, cornerSize,
                                     !(flatOnLeft || flatOnTop),
                                     !(flatOnRight || flatOnTop),
                                     !(flatOnLeft || flatOnBottom),
                                     !(flatOnRight || flatOnBottom));

            g.fillPath(path);

            g.setColour(Colours::darkgrey);
//            g.setColour(button.findColour(ComboBox::outlineColourId));
            g.strokePath(path, PathStrokeType(1.0f));
        } else {
            g.fillRoundedRectangle(bounds, cornerSize);

            g.setColour(Colours::darkgrey);
//            g.setColour(button.findColour(ComboBox::outlineColourId));
            g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        }
    }

};