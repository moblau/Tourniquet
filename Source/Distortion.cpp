/*
  ==============================================================================

    Distortion.cpp
    Created: 21 Dec 2024 10:44:49pm
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion(juce::AudioProcessorValueTreeState& apvts) : waveshaper{{std::tanh}},
    oversampling(std::make_unique<juce::dsp::Oversampling<float>>(2, 4, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR)),
    params(apvts)
{
}

void Distortion::prepare(const juce::dsp::ProcessSpec& spec)
{
    oversampling->reset();
    oversampling->initProcessing(spec.maximumBlockSize);
}

void Distortion::process(juce::AudioBuffer<float>& buffer)
{
    float dist = *params.getRawParameterValue("distortion");
    inputGain.setGainLinear(dist);
    outputGain.setGainLinear(1/sqrt(dist));
    
    juce::dsp::AudioBlock<float> block(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    inputGain.process(context);
    auto oversampledBlock = oversampling->processSamplesUp(context.getInputBlock());
    
//    auto waveshaperContext = juce::dsp::ProcessContextReplacing<float>(oversampledBlock);
    waveshape(context);
    
    oversampling->processSamplesDown(context.getOutputBlock());
    outputGain.process(context);
    
//    oversampling->processSamplesDown(oversampledBlock);

}

void Distortion::waveshape(juce::dsp::ProcessContextReplacing<float> &context)
{
    auto& inputBlock  = context.getInputBlock();   // Read input data
    auto& outputBlock = context.getOutputBlock();
    
    int distType = *params.getRawParameterValue("distType");
    for (int channel = 0; channel < outputBlock.getNumChannels(); ++channel) {
        auto* inputChannelData  = inputBlock.getChannelPointer(channel);
        auto* outputChannelData = outputBlock.getChannelPointer(channel);

        for (int sample = 0; sample < outputBlock.getNumSamples(); ++sample) {
            // Example: apply a distortion effect
            
            if ( distType == 1 ){

                outputChannelData[sample] = std::tanh(inputChannelData[sample]);
            }
            else if( distType == 2)
            {
                float k = *params.getRawParameterValue("distortion");
                k /= 100;
                k = 2*k/(1-k);
                outputChannelData[sample] = (1+k)*inputChannelData[sample]/(1+k*abs(inputChannelData[sample]));
            }
            else if (distType == 3){
                outputChannelData[sample] = std::sin(inputChannelData[sample]/2);

            }

        }
    }
}
