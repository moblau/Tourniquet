/*
  ==============================================================================

    Filter.cpp
    Created: 23 Dec 2024 8:00:12am
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "Filter.h"
Filter::Filter(juce::AudioProcessorValueTreeState& apvts) :
                    params(apvts),
                    lowPass(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100.f, 20000.f)),
                    highPass(juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(44100.f, 20.f))
                    
{
//    ramp0 = 1;
//    ramp1 = .1;
    noteStart = false;
    noteEnd = false;
}

void Filter::prepare(juce::dsp::ProcessSpec spec)
{
    sampleRate = spec.sampleRate;
    lowPass.prepare(spec);
    highPass.prepare(spec);
    lpfEnvParam.attack = *params.getRawParameterValue("lpfEnvAttack");
    hpfEnvParam.attack = *params.getRawParameterValue("hpfEnvAttack");
    lpfEnvParam.release = *params.getRawParameterValue("lpfEnvRelease");
    hpfEnvParam.release = *params.getRawParameterValue("hpfEnvRelease");
    lpfEnvParam.decay = .1;
    hpfEnvParam.decay = .1;
    lpfEnvParam.sustain = 1.0;
    hpfEnvParam.sustain = 1.0;
    
    lpfEnv.setParameters(lpfEnvParam);
    hpfEnv.setParameters(hpfEnvParam);
    
    lHp.prepare(spec);
    rHp.prepare(spec);
    lLp.prepare(spec);
    rLp.prepare(spec);
    
    lHp.coefficients =juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(44100.f, 20.f);
    rHp.coefficients =juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(44100.f, 20.f);

    lLp.coefficients =juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100.f, 20000.f);
    rLp.coefficients =juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100.f, 20000.f);

    
}

void Filter::process(juce::dsp::ProcessContextReplacing<float> block )
{
    
//    float lowPassFreq = *params.getRawParameterValue("lowPass");
//    float highPassFreq = *params.getRawParameterValue("highPass");
//    float lowQ = *params.getRawParameterValue("lowPassQ");;
//    float highQ = *params.getRawParameterValue("highPassQ");;
//    
    
//    *lowPass.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowPassFreq, lowQ);
//    *highPass.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highPassFreq, highQ);

    

    
    auto& audioBlock = block.getOutputBlock();
    
    
    for (int sample = 0; sample < audioBlock.getNumSamples(); ++sample)
    {
        
        if ( noteStart ){
            noteStart = false;
            lpfEnv.noteOn();
            hpfEnv.noteOn();
        }
        if ( noteEnd ){
            noteEnd = false;
            lpfEnv.noteOff();
            hpfEnv.noteOff();
        }
        
        lpfEnvParam.attack = *params.getRawParameterValue("lpfEnvAttack");
        hpfEnvParam.attack = *params.getRawParameterValue("hpfEnvAttack");
        
        lpfEnvParam.release = *params.getRawParameterValue("lpfEnvRelease");
        hpfEnvParam.release = *params.getRawParameterValue("hpfEnvRelease");
        
        lpfEnv.setParameters(lpfEnvParam);
        hpfEnv.setParameters(hpfEnvParam);
        
        lpfEnvGain  = *params.getRawParameterValue("lpfEnv");
        hpfEnvGain = *params.getRawParameterValue("hpfEnv");
        
        leftSample = audioBlock.getSample(0, sample);
        rightSample = audioBlock.getSample(1, sample);
        
        lowPassFreq = *params.getRawParameterValue("lowPass");
        highPassFreq = *params.getRawParameterValue("highPass");
        lowQ = *params.getRawParameterValue("lowPassQ");;
        highQ = *params.getRawParameterValue("highPassQ");;

        highPassFreq += hpfEnvGain*hpfEnv.getNextSample();
        lowPassFreq += lpfEnvGain*lpfEnv.getNextSample();
        highPassFreq = juce::jlimit<float>(20,20000,highPassFreq);
        lowPassFreq = juce::jlimit<float>(20,20000,lowPassFreq);
        
        lpfDeltaFreq =lowPassFreq;
        hpfDeltaFreq=highPassFreq;
        
        lHp.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highPassFreq, highQ);
        rHp.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highPassFreq, highQ);
        lLp.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowPassFreq, lowQ);
        rLp.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowPassFreq, lowQ);
        
        leftSample = lHp.processSample(leftSample);
        leftSample = lLp.processSample(leftSample);

        rightSample = rHp.processSample(rightSample);
        rightSample = rLp.processSample(rightSample);
        
        audioBlock.setSample(0, sample, leftSample);
        audioBlock.setSample(1, sample, rightSample);
        
    }
    
    
        
}
