/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    setSize(1024, 768);

    // add components
    addAndMakeVisible(&designWindow);
    addAndMakeVisible(wave);
    addAndMakeVisible(&timelineLabel);
}

MainComponent::~MainComponent() {
}

//==============================================================================
void MainComponent::paint(Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setFont(Font(16.0f));
    g.setColour(Colours::white);
}

void MainComponent::resized() {
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    auto waveBounds = getLocalBounds().reduced(padding);
    waveBounds.setTop(waveBounds.getHeight() - 200);

    wave.setBounds(waveBounds);

    auto designBounds = getLocalBounds().reduced(padding);
    designBounds.setBottom(waveBounds.getTopLeft().getY() - padding);
    designBounds.setTop(50);

    designWindow.setBounds(designBounds);

    auto timelineLabelBounds = getLocalBounds().reduced(padding);
//    timelineLabelBounds.setLeft(timelineLabelBounds.getX() / 2);
    timelineLabelBounds.setHeight(42);

    timelineLabel.setBounds(timelineLabelBounds);
}
