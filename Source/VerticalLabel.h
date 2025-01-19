/*
  ==============================================================================

    VerticalLabel.h
    Created: 9 Jan 2025 9:41:59am
    Author:  Morris Blaustein

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class VerticalLabel : public juce::Label
{
public:
    VerticalLabel() {}

    void paint(juce::Graphics& g) override
    {
        
        g.setColour(findColour(juce::Label::textColourId));
        g.setFont(getFont());

        auto text = getText();
        auto bounds = getLocalBounds();

        int letterHeight = g.getCurrentFont().getHeight();
        int totalHeight = letterHeight * text.length();
        int startY = (bounds.getHeight() - totalHeight) / 2;

        for (size_t i = 0; i < text.length(); ++i)
        {
            juce::String letter = text.substring((int)i, (int)i + 1);

            g.drawText(letter,
                       bounds.getX(),
                       startY + i * letterHeight,    
                       bounds.getWidth(),
                       letterHeight,
                       juce::Justification::centred);
        }
    }
};
