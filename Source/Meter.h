/*
  ==============================================================================

    Meter.h
    Created: 14 Jan 2025 7:47:03am
    Author:  Morris Blaustein

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Meter : public juce::Component
{
public:
    Meter()
    {
        
    }
    
    void paint(juce::Graphics& g) override;

    
    void setLevel(const float value)
    {
        level = value;
    }
    void setClipping(bool isClipping){
        clipping = isClipping;
    }
private:
    float level = -60;
    bool clipping = false;
};
