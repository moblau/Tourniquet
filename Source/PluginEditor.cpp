/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TourniquetAudioProcessorEditor::TourniquetAudioProcessorEditor (TourniquetAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), customSliderLookAndFeel(p.getAPVTS())
{
    setSize (512, 512);
    startTimer(.01);
    
    
    signalOrder.setLookAndFeel(&customSliderLookAndFeel);
    addAndMakeVisible(signalOrder);
    signalOrderAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.getAPVTS(), "signalOrder", signalOrder));
    
    filterOrder.setLookAndFeel(&customSliderLookAndFeel);
    addAndMakeVisible(filterOrder);
    filterOrderAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.getAPVTS(), "filterOrder", filterOrder));
    
    
    delayKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    delayKnob.setLookAndFeel(&customSliderLookAndFeel);
    delayKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    delayKnob.setRange(0,1000,0);
    delayKnob.setValue(0);
    addAndMakeVisible(delayKnob);
    delayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "delay", delayKnob));
    
    
    feedbackKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    feedbackKnob.setLookAndFeel(&customSliderLookAndFeel);
    feedbackKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    feedbackKnob.setRange(0.0,1.0,0);
    feedbackKnob.setValue(0.0);
    addAndMakeVisible(feedbackKnob);
    feedbackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "feedback", feedbackKnob));
    
    distortionKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    distortionKnob.setLookAndFeel(&customSliderLookAndFeel);

    distortionKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    distortionKnob.setRange(1.0,100);
    distortionKnob.setValue(50.0);
    addAndMakeVisible(distortionKnob);
    distortionAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "distortion", distortionKnob));
    
    lowPassKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    lowPassKnob.setLookAndFeel(&customSliderLookAndFeel);
    lowPassKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lowPassKnob.setRange(0,1,1);
    lowPassKnob.setValue(1);
    addAndMakeVisible(lowPassKnob);
    lowPassKnob.setComponentID("lpf");
    lowPassAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lowPass", lowPassKnob));
    
    highPassKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    highPassKnob.setLookAndFeel(&customSliderLookAndFeel);
    highPassKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    highPassKnob.setRange(0,1,0);
    highPassKnob.setValue(0);

    addAndMakeVisible(highPassKnob);
    highPassKnob.setComponentID("hpf");
    highPassAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "highPass", highPassKnob));
    
    lowPassQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    lowPassQKnob.setLookAndFeel(&customSliderLookAndFeel);

    lowPassQKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lowPassQKnob.setRange(1,50,.1);
    lowPassQKnob.setValue(1);
    addAndMakeVisible(lowPassQKnob);
    lowPassQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lowPassQ", lowPassQKnob));
    
    highPassQKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    highPassQKnob.setLookAndFeel(&customSliderLookAndFeel);

    highPassQKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    highPassQKnob.setRange(1,50,.1);
    highPassQKnob.setValue(1);
    addAndMakeVisible(highPassQKnob);
    highPassQAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "highPassQ", highPassQKnob));
    
    dryWetKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    dryWetKnob.setLookAndFeel(&customSliderLookAndFeel);

    dryWetKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    dryWetKnob.setRange(0.0,1.0,0.0);
    dryWetKnob.setValue(1.0);
    addAndMakeVisible(dryWetKnob);
    dryWetAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "dryWet", dryWetKnob));
    
    lpfEnvKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    lpfEnvKnob.setLookAndFeel(&customSliderLookAndFeel);
    lpfEnvKnob.setComponentID("envKnob");
    lpfEnvKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    lpfEnvKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lpfEnvKnob.setRange(0.0,1.0,0.0);
    lpfEnvKnob.setValue(1.0);
    addAndMakeVisible(lpfEnvKnob);
    lpfEnvAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lpfEnv", lpfEnvKnob));
    
    hpfEnvKnob.setComponentID("envKnob");

    hpfEnvKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    hpfEnvKnob.setLookAndFeel(&customSliderLookAndFeel);
    hpfEnvKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    hpfEnvKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    hpfEnvKnob.setRange(0.0,1.0,0.0);
    hpfEnvKnob.setValue(1.0);
    addAndMakeVisible(hpfEnvKnob);
    hpfEnvAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "hpfEnv", hpfEnvKnob));
    
    
    lpfSkewKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    lpfSkewKnob.setLookAndFeel(&customSliderLookAndFeel);
    lpfSkewKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    lpfSkewKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lpfSkewKnob.setRange(0.1,1.0,0.01);
    lpfSkewKnob.setValue(1);
    addAndMakeVisible(lpfSkewKnob);
    lpfSkewAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lpfSkew", lpfSkewKnob));
    
    hpfSkewKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    hpfSkewKnob.setLookAndFeel(&customSliderLookAndFeel);
    hpfSkewKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    hpfSkewKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    hpfSkewKnob.setRange(0.1,1.0,0.01);
    hpfSkewKnob.setValue(1);
    addAndMakeVisible(hpfSkewKnob);
    hpfSkewAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "hpfSkew", hpfSkewKnob));
    
    
    
    lpfEnvAttackKnob.setSliderStyle(juce::Slider::LinearHorizontal);

    lpfEnvAttackKnob.setLookAndFeel(&customSliderLookAndFeel);
    
    lpfEnvAttackKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lpfEnvAttackKnob.setRange(0.0,1.0,0.0);
    lpfEnvAttackKnob.setValue(1.0);
    addAndMakeVisible(lpfEnvAttackKnob);
    lpfEnvAttackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lpfEnvAttack", lpfEnvAttackKnob));
    
    lpfEnvReleaseKnob.setSliderStyle(juce::Slider::LinearHorizontal);

    lpfEnvReleaseKnob.setLookAndFeel(&customSliderLookAndFeel);
    
    lpfEnvReleaseKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    lpfEnvReleaseKnob.setRange(0.0,1.0,0.0);
    lpfEnvReleaseKnob.setValue(1.0);
    addAndMakeVisible(lpfEnvReleaseKnob);
    lpfEnvReleaseAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "lpfEnvRelease", lpfEnvReleaseKnob));

    hpfEnvAttackKnob.setSliderStyle(juce::Slider::LinearHorizontal);

    hpfEnvAttackKnob.setLookAndFeel(&customSliderLookAndFeel);

    hpfEnvAttackKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    hpfEnvAttackKnob.setRange(0.0,1.0,0.0);
    hpfEnvAttackKnob.setValue(1.0);
    addAndMakeVisible(hpfEnvAttackKnob);
    hpfEnvAttackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "hpfEnvAttack", hpfEnvAttackKnob));
    
    hpfEnvReleaseKnob.setSliderStyle(juce::Slider::LinearHorizontal);

    hpfEnvReleaseKnob.setLookAndFeel(&customSliderLookAndFeel);
    hpfEnvReleaseKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    hpfEnvReleaseKnob.setRange(0.0,1.0,0.0);
    hpfEnvReleaseKnob.setValue(1.0);
    addAndMakeVisible(hpfEnvReleaseKnob);
    hpfEnvReleaseAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getAPVTS(), "hpfEnvRelease", hpfEnvReleaseKnob));
    
    
    decayTimeLabel.setText("Decay Time", juce::dontSendNotification);
    decayTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayTimeLabel);
    
    spreadLabel.setText("Spread", juce::dontSendNotification);
    spreadLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(spreadLabel);
    
    distortionLabel.setText("Distortion", juce::dontSendNotification);
    distortionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(distortionLabel);
    
    dryWetLabel.setText("Dry/Wet", juce::dontSendNotification);
    dryWetLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(dryWetLabel);
    
    lpLabel.setText("Lowpass Filter", juce::dontSendNotification);
    lpLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lpLabel);
    
    hpLabel.setText("Highpass Filter", juce::dontSendNotification);
    hpLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(hpLabel);
    
    qLabel.setText("Q", juce::dontSendNotification);
    qLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(qLabel);
    
    freqLabel.setText("Freq", juce::dontSendNotification);
    freqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(freqLabel);
    
    envGainLabel.setText("Env", juce::dontSendNotification);
    envGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(envGainLabel);
    
    skewLabel.setText("Skew", juce::dontSendNotification);
    skewLabel.setJustificationType(juce::Justification::verticallyCentred);
    addAndMakeVisible(skewLabel);
    
    envGainLabel2.setText("Env", juce::dontSendNotification);
    envGainLabel2.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(envGainLabel2);
    
    skewLabel2.setText("Skew", juce::dontSendNotification);
    skewLabel2.setJustificationType(juce::Justification::verticallyCentred);
    addAndMakeVisible(skewLabel2);
    
    
    arLabel.setText("A/R", juce::dontSendNotification);
    arLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(arLabel);
    
    filterOrderLabel.setText("Rev          Dist", juce::dontSendNotification);
    filterOrderLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterOrderLabel);
    filterOrderLabel.setInterceptsMouseClicks(false, false);


    
    signalOrderLabel.setText("Rev          Filt", juce::dontSendNotification);
    signalOrderLabel.setJustificationType(juce::Justification::centred);
    signalOrderLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(signalOrderLabel);
    
    distortionType.addItemList({"Dist I", "Dist II", "Dist III"}, 1);
    addAndMakeVisible(distortionType);
    distortionTypeAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.getAPVTS(), "distType", distortionType));
    
    
}

TourniquetAudioProcessorEditor::~TourniquetAudioProcessorEditor()
{
    delayKnob.setLookAndFeel(nullptr);
    feedbackKnob.setLookAndFeel(nullptr);
    distortionKnob.setLookAndFeel(nullptr);
    lowPassKnob.setLookAndFeel(nullptr);
    highPassKnob.setLookAndFeel(nullptr);
    highPassQKnob.setLookAndFeel(nullptr);
    lowPassQKnob.setLookAndFeel(nullptr);
    dryWetKnob.setLookAndFeel(nullptr);
    signalOrder.setLookAndFeel(nullptr);
    filterOrder.setLookAndFeel(nullptr);
    hpfEnvAttackKnob.setLookAndFeel(nullptr);
    hpfEnvReleaseKnob.setLookAndFeel(nullptr);
    lpfEnvReleaseKnob.setLookAndFeel(nullptr);
    lpfEnvAttackKnob.setLookAndFeel(nullptr);
    lpfEnvKnob.setLookAndFeel(nullptr);
    hpfEnvKnob.setLookAndFeel(nullptr);
    lpfSkewKnob.setLookAndFeel(nullptr);
    hpfSkewKnob.setLookAndFeel(nullptr);

}

void TourniquetAudioProcessorEditor::timerCallback()
{
    lpfDeltaFreq = audioProcessor.lpfDelta.load();
    hpfDeltaFreq = audioProcessor.hpfDelta.load();
    customSliderLookAndFeel.setDelta(lpfDeltaFreq, hpfDeltaFreq);
    repaint();
}
//==============================================================================
void TourniquetAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> bounds = getLocalBounds();
    bg = juce::ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize  );
    g.drawImageWithin(bg, 0, 0, 512 , 512, juce::RectanglePlacement::stretchToFit);
    juce::ColourGradient gradient (juce::Colours::darkblue, bounds.getX(), bounds.getY(),
                                   juce::Colours::darkgrey, bounds.getX(), bounds.getBottom(), false);
    gradient.multiplyOpacity(.17);
    g.setGradientFill(gradient);
    g.fillRect(bounds);  // Fill the entire component with the gradient
    title = juce::ImageCache::getFromMemory(BinaryData::tourniquet_png, BinaryData::tourniquet_pngSize  );
    g.drawImageWithin(title, 30, 0, 512 , 256, juce::RectanglePlacement::stretchToFit);
    lulubyLogo = juce::ImageCache::getFromMemory(BinaryData::luluby_png, BinaryData::luluby_pngSize  );
    g.drawImageWithin(lulubyLogo, 70, 25, 70 , 70, juce::RectanglePlacement::stretchToFit);

    
}

void TourniquetAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds = bounds.reduced(15,15);
    auto topRatio = bounds.getWidth()/3;
    auto bottom = bounds.removeFromBottom(bounds.getHeight()/2);
    auto top = bounds.removeFromTop(topRatio/2);
    auto leftArea = bounds.removeFromLeft(topRatio);
    auto decayTimeArea = leftArea.removeFromBottom(25);
    auto midArea = bounds.removeFromLeft(topRatio);
    auto rightArea = bounds;
    auto spreadArea = midArea.removeFromBottom(25);
    auto distortionArea = rightArea.removeFromBottom(25);
    
//    for(int i = 0; i < 3; i ++){
//        auto leftTopArea = topArea.withTrimmedLeft(i * topArea.getWidth()/3).withWidth(topArea.getWidth()/3);
//        allPassDelaySlider[i].setBounds(leftTopArea);
//
//    }
    
    delayKnob.setBounds(leftArea.reduced(7));
    decayTimeLabel.setBounds(decayTimeArea);
    feedbackKnob.setBounds(midArea.reduced(7));
    spreadLabel.setBounds(spreadArea);
    distortionKnob.setBounds(rightArea.reduced(7));
    distortionLabel.setBounds(distortionArea);
//    auto freqGainBounds = bottom.removeFromTop(bottom.getHeight()/3);
//    auto w = freqGainBounds.getWidth()/3;
//    freqGainKnob.setBounds(freqGainBounds.removeFromLeft(w));
//    freqQKnob.setBounds(freqGainBounds.removeFromLeft(w));
//    ratioKnob.setBounds(freqGainBounds);
    float bottomRatio = bottom.getWidth()/3;
    auto topLowpass = bottom.removeFromLeft(bottomRatio);
    auto lpLabelArea = topLowpass.removeFromBottom(25);
    hpLabel.setBounds(lpLabelArea);
    auto hpfEnvArea = topLowpass.removeFromTop(70);
    envGainLabel.setBounds(hpfEnvArea.removeFromLeft(20));
    hpfEnvKnob.setBounds(hpfEnvArea.removeFromLeft(bottomRatio/3).reduced(1));
    skewLabel.setBounds(hpfEnvArea.removeFromLeft(20));
    hpfSkewKnob.setBounds(hpfEnvArea.reduced(7));
    highPassKnob.setBounds(topLowpass.removeFromTop(40));
    auto arKnobArea = topLowpass.removeFromTop(70);
//    envGainLabel.setBounds(160,270,70,20);
//    skewLabel.setBounds(160,290,70,20);
    hpfEnvAttackKnob.setBounds(arKnobArea.removeFromLeft(arKnobArea.getWidth()/2));
    hpfEnvReleaseKnob.setBounds(arKnobArea);
    highPassQKnob.setBounds(topLowpass);
    
    auto filterLabelArea = bottom.removeFromLeft(40);
    bottom.removeFromLeft(5);
    filterLabelArea.removeFromTop(70);
    filterLabelArea.removeFromBottom(25);
    
    freqLabel.setBounds(filterLabelArea.removeFromTop(30));
    arLabel.setBounds(filterLabelArea.removeFromTop(70));
    qLabel.setBounds(filterLabelArea);
    auto topHighPass =bottom.removeFromLeft(bottomRatio);
    auto hpLabelArea = topHighPass.removeFromBottom(25);
    lpLabel.setBounds(hpLabelArea);
    
    auto lpfEnvArea = topHighPass.removeFromTop(70);
    envGainLabel2.setBounds(lpfEnvArea.removeFromLeft(20));
    lpfEnvKnob.setBounds(lpfEnvArea.removeFromLeft(bottomRatio/3).reduced(1));
    skewLabel2.setBounds(lpfEnvArea.removeFromLeft(20));
    lpfSkewKnob.setBounds(lpfEnvArea.reduced(7));
    lowPassKnob.setBounds(topHighPass.removeFromTop(40));
    arKnobArea = topHighPass.removeFromTop(70);
    lpfEnvAttackKnob.setBounds(arKnobArea.removeFromLeft(arKnobArea.getWidth()/2));
    lpfEnvReleaseKnob.setBounds(arKnobArea);
    
    
    lowPassQKnob.setBounds(topHighPass);
    auto dryWetArea = bottom.removeFromLeft(bottomRatio);
    
    auto distTypeArea = dryWetArea.removeFromTop(60).reduced(15);
    distortionType.setBounds(distTypeArea);
    signalOrderLabel.setBounds(386,365,100,20);
    filterOrderLabel.setBounds(388,325,100,20);
    signalOrder.setBounds(dryWetArea.removeFromTop(40));
    filterOrder.setBounds(dryWetArea.removeFromTop(40));
    dryWetKnob.setBounds(dryWetArea.removeFromTop(70).reduced(7));
    dryWetLabel.setBounds(dryWetArea);
//    arLabel.setBounds(330,382,50,20);
//    qLabel.setBounds(325, 440, 50, 20);
//    freqLabel.setBounds(330,330,50,20);
}

