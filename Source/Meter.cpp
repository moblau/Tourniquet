/*
  ==============================================================================

    Meter.cpp
    Created: 14 Jan 2025 9:13:06am
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "Meter.h"


void Meter::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    

    g.setColour(juce::Colours::lightblue);
    g.drawRoundedRectangle(bounds.reduced(5), 5, 1);
    juce::ColourGradient gradient(
            juce::Colour::fromRGB(255, 182, 193),
            bounds.getTopLeft(),
            juce::Colour::fromRGB(152, 251, 152),
            bounds.getBottomRight(),
            false
        );
    
    gradient.addColour(0.5, juce::Colour::fromRGB(173, 216, 230));

    g.setGradientFill(gradient);

    const auto scaledY = juce::jmap(level,-100.f,6.f,0.f,static_cast<float>(getHeight()));
    auto sig =bounds.removeFromBottom(scaledY).reduced(5);
    g.fillRoundedRectangle(sig, 5);
    g.setColour(juce::Colours::red);
    if(clipping){
        g.fillRoundedRectangle(sig.removeFromTop(10),5);
    }
}
