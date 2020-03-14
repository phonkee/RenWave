/*
  ==============================================================================

    WaveWindow.cpp
    Created: 9 Mar 2020 12:06:57am
    Author:  Peter Vrba

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveWindow.h"

//==============================================================================
WaveWindow::WaveWindow() {
    isLoading = false;
    reader = nullptr;

    zoomInButton.setTooltip("Zoom in wave.");
    zoomInButton.setTooltip("Zoom out wave.");

    zoomInButton.setLookAndFeel(&lookAndFeel);
    zoomOutButton.setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(zoomInButton);
    addAndMakeVisible(zoomOutButton);

//    auto duration = std::chrono::system_clock::duration{0};
//    auto now = std::chrono::system_clock::now();
//    auto in_time_t = std::chrono::system_clock::to_time_t(now);
//
//    std::cout << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << std::endl;
}


WaveWindow::~WaveWindow() {
    delete reader;
}

/*
 * paint window
 */
void WaveWindow::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::darkgrey);

    auto rect = getLocalBounds();
    g.drawRect(rect, 2);   // draw an outline around the component

    g.setColour(Colours::dimgrey);
    g.setFont(14.0f);

    if (isLoading) {
        g.drawText("Loading " + filename, getLocalBounds(),
                   Justification::centred, true);   // draw some placeholder text
    } else {
        g.drawText(blankText, getLocalBounds(),
                   Justification::centred, true);   // draw some placeholder text
    }

}

void WaveWindow::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto windowBounds = getLocalBounds();
    zoomInButton.setBounds(windowBounds.getWidth() - 40, 20, 15, 15);
    zoomOutButton.setBounds(windowBounds.getWidth() - 40, 40, 15, 15);

    zoomInButton.onClick = [&]() {
        DBG("clicked on plus :-)");
    };

    zoomOutButton.onClick = [&]() {
        DBG("clicked on minus :-(");
    };

    // FIXME: this is place where we should generate wave image
}

const std::string &WaveWindow::getBlankText() const {
    return blankText;
}

void WaveWindow::setBlankText(const std::string &blankText) {
    WaveWindow::blankText = blankText;
}

bool WaveWindow::isInterestedInFileDrag(const StringArray &files) {
    AudioFormatManager manager;
    manager.registerBasicFormats();

    for (const auto &fileName: files) {
        auto file = File(fileName);

        if (manager.findFormatForFileExtension(file.getFileExtension()) != nullptr) {
            return true;
        }
    }

    return false;
}

/*
 * filesDropped is called when files are drag'n'dropped to our component
 * Only the last file will be used though
 */
void WaveWindow::filesDropped(const StringArray &array, int i, int i1) {
    AudioFormatManager manager;
    manager.registerBasicFormats();

    // set that we are loading
    isLoading = true;

    // repaint
    repaint();

    File file;

    for (const auto &fileName: array) {
        file = File(fileName);
        auto *fmt = manager.findFormatForFileExtension(file.getFileExtension());
        if (fmt == nullptr) {
            continue;
        }

        // FIXME: not very efficient
        setReader(fmt->createMemoryMappedReader(file));
        filename = fileName;
    }

    // check that reader was not provided
    if (this->reader == nullptr) {
        repaint();
        return;
    }

    std::cout << "sample rate: " << reader->sampleRate << std::endl;
    std::cout << "bits: " << reader->bitsPerSample << std::endl;
    std::cout << "channels: " << reader->numChannels << std::endl;
    std::cout << "samples: " << reader->lengthInSamples << std::endl;
}

// getReader returns used reader
MemoryMappedAudioFormatReader *WaveWindow::getReader() const {
    return reader;
}

void WaveWindow::setReader(MemoryMappedAudioFormatReader *reader) {
    WaveWindow::reader = reader;
}

// readFile reads file
void WaveWindow::readFile(File &file) {

}
