/*
  ==============================================================================

    SVerb.cpp
    Created: 12 Dec 2024 8:40:34am
    Author:  Morris Blaustein

  ==============================================================================
*/

#include "SVerb.h"

SVerb::SVerb(juce::AudioProcessorValueTreeState& apvts) : params(apvts), distortion(apvts)
{
    
}
void SVerb::prepare(double sampleRate, int samplesPerBlock){

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    
    apDelay1 = (int)(347);
    apDelay2 = (int)(113);
    apDelay3 = (int)(37);

    cfDelay1 = (int)(1687);
    cfDelay2 = (int)(1601);
    cfDelay3 = (int)(2053);
    cfDelay4 = (int)(2251);
//
    line1.prepare(spec);
    line1.reset();
    line1.setMaximumDelayInSamples(sampleRate*4);
    
    line2.prepare(spec);
    line2.reset();
    line2.setMaximumDelayInSamples(sampleRate*4);
    
    line3.prepare(spec);
    line3.reset();
    line3.setMaximumDelayInSamples(sampleRate*4);
    
    line4.prepare(spec);
    line4.reset();
    line4.setMaximumDelayInSamples(sampleRate*4);
    
    line5.prepare(spec);
    line5.reset();
    line5.setMaximumDelayInSamples(sampleRate*4);
    
    line6.prepare(spec);
    line6.reset();
    line6.setMaximumDelayInSamples(sampleRate*4);

    line7.prepare(spec);
    line7.reset();
    line7.setMaximumDelayInSamples(sampleRate*4);


}

void SVerb::setParams(float delayTimeMs, float feedback, int allPassDelay0,int allPassDelay1,int allPassDelay2){
    decay = feedback;

}

float SVerb::process(juce::AudioBuffer<float>& buffer, std::atomic<float> * delayTime, std::atomic<float> * feedback,std::atomic<float> * waveshaper)
{

//
//
    
    float delayCaptured;
    float feedbackCaptured;
    int signalOrder;
    signalOrder = *params.getRawParameterValue("signalOrder");

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        if (signalOrder == 1){
            distortion.process(buffer);
        }
        for ( int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            
            delayCaptured = delayTime->load();
            feedbackCaptured = feedback->load();
//            float a= feedbackCaptured;
            line1.setDelay(apDelay1+delayCaptured);
            line2.setDelay(apDelay2+delayCaptured*(1+feedbackCaptured));
            line3.setDelay(apDelay3+delayCaptured*(3+feedbackCaptured*3));
            line4.setDelay(cfDelay1+delayCaptured*(3+feedbackCaptured*5));
            line5.setDelay(cfDelay2+delayCaptured*(3+feedbackCaptured*7));
            line6.setDelay(cfDelay3+delayCaptured*(3+feedbackCaptured*11));
            line7.setDelay(cfDelay4+delayCaptured*(3+feedbackCaptured*13));
            float inputSample = channelData[sample];
            setParams(0, .7, 0, 0, 0);
            
            float a=.62;
            
//            readIndex0 = writeIndex0 - apDelay1;
            
//            if ( readIndex0 < 0){
//                readIndex0+= apf0delayLine.getNumSamples();
//            }
//
//            float v_delayed = apf0delayLine.getSample(channel, writeIndex0);
//            DBG("read " << readIndex0 << " " << v_delayed);
            float v_delayed = line1.popSample(channel);
            float output = a*inputSample + v_delayed;
            float new_v = inputSample - a*v_delayed;
            line1.pushSample(channel, new_v);
            
            float temp = output;
            v_delayed = line2.popSample(channel);
            output = a*output + v_delayed;
            new_v = temp - a*v_delayed;
            line2.pushSample(channel, new_v);
//
            temp = output;
            v_delayed = line3.popSample(channel);
            output = a*output + v_delayed;
            new_v = temp - a*v_delayed;
            line3.pushSample(channel, new_v);
            
            temp = output;
            float out1, out2, out3, out4;
            
            v_delayed = line4.popSample(channel);
            out1 = temp + a*v_delayed;
            line4.pushSample(channel, temp);
            
            v_delayed = line5.popSample(channel);
            out2 = temp + a*v_delayed;
            line5.pushSample(channel, temp);
            
            v_delayed = line6.popSample(channel);
            out3 = temp + a*v_delayed;
            line6.pushSample(channel, temp);
            
            v_delayed = line7.popSample(channel);
            out4 = temp + a*v_delayed;
            line7.pushSample(channel, temp);
            
            
            
            output = (out1+out2+out3+out4)/4;

            
            channelData[sample] = output;

            
        }
        if (signalOrder == 0){
            distortion.process(buffer);
        }
    }
    
    


    
}
