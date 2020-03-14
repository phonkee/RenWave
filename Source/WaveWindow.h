/*
  ==============================================================================

    WaveWindow.h
    Created: 9 Mar 2020 12:06:57am
    Author:  Peter Vrba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <chrono>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "LookAndFeel.h"

//==============================================================================
/*
 * WaveWindow is UI component that represents sound
*/
class WaveWindow : public Component,
                   public FileDragAndDropTarget {
public:
    WaveWindow();

    ~WaveWindow() override;

    void paint(Graphics &) override;

    void resized() override;

    [[nodiscard]] const std::string &getBlankText() const;

    void setBlankText(const std::string &blankText);

    bool isInterestedInFileDrag(const StringArray &files) override;

    [[nodiscard]] MemoryMappedAudioFormatReader *getReader() const;

    void setReader(MemoryMappedAudioFormatReader *reader);

    // readFile reads file
    void readFile(File &file);

    // callback when time range was selected
    std::function<void(int x, int y)> onSelect;

private:
    // set our look and feel
    LookAndFeel_RenWave lookAndFeel;

    // shown text when no wave loaded
    std::string blankText{"Please drag wave file here"};

    // isLoading has information if we are loading wave
    bool isLoading;

    // filename of given file.
    String filename;

    // reader of given file
    MemoryMappedAudioFormatReader *reader{};

    // audio data
    std::unique_ptr<AudioBuffer<float>> data;

    // components
    TextButton zoomInButton{"+", "Zoom in"};
    TextButton zoomOutButton{"-", "Zoom out"};

    int padding = 10;

    void filesDropped(const StringArray &array, int i, int i1) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveWindow)
};
