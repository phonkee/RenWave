/*
  ==============================================================================

    Tool.h
    Created: 14 Mar 2020 1:01:11am
    Author:  Peter Vrba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Tool {

public:
    Tool() = delete;

    virtual ~Tool() = 0;

    String getName();

protected:
    String name;

private:


};
