/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomSliderLookAndFeel.h"
#include "VerticalLabel.h"
//==============================================================================
/**
*/



class TourniquetAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Timer
{
public:
    TourniquetAudioProcessorEditor (TourniquetAudioProcessor&);
    ~TourniquetAudioProcessorEditor() override;
    void setHpfDelta(float hpfDelta){
        hpfDeltaFreq = hpfDelta;
    }
    void setLpfDelta(float lpfDelta){
        lpfDeltaFreq = lpfDelta;
    }
    void timerCallback() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TourniquetAudioProcessor& audioProcessor;
    juce::Image title, lulubyLogo, bg;
    juce::Slider delayKnob;
    juce::Slider feedbackKnob;
    juce::Slider distortionKnob;
    juce::Slider highPassKnob;
    juce::Slider lowPassKnob;
    juce::Slider dryWetKnob;
    juce::Slider lowPassQKnob;
    juce::Slider highPassQKnob;
    juce::ToggleButton signalOrder, filterOrder;
    juce::ComboBox distortionType;
    juce::Slider lpfEnvKnob, hpfEnvKnob;
    juce::Slider lpfEnvAttackKnob, lpfEnvReleaseKnob, hpfEnvAttackKnob, hpfEnvReleaseKnob;
    juce::Slider lpfSkewKnob, hpfSkewKnob;
    
    
    
    float hpfDeltaFreq, lpfDeltaFreq;
    float lpfFreq, hpfFreq;
//    juce::Slider freqGainKnob;
//    juce::Slider freqQKnob;
//    juce::Slider ratioKnob;
    CustomSliderLookAndFeel customSliderLookAndFeel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> signalOrderAttachment, filterOrderAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowPassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highPassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowPassQAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highPassQAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> distortionTypeAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lpfEnvAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hpfEnvAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lpfEnvAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lpfEnvReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hpfEnvAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hpfEnvReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lpfSkewAttachment, hpfSkewAttachment;

    
    juce::Label decayTimeLabel, spreadLabel, distortionLabel, dryWetLabel, hpLabel, qLabel, freqLabel, lpLabel,  signalOrderLabel;
    juce::Label  arLabel, filterOrderLabel;
    VerticalLabel skewLabel, envGainLabel, skewLabel2, envGainLabel2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TourniquetAudioProcessorEditor)
};

