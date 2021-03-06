/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class Plugin_testAudioProcessorEditor  : public AudioProcessorEditor,
                                         private Slider::Listener
{
public:
    Plugin_testAudioProcessorEditor (Plugin_testAudioProcessor&);
    ~Plugin_testAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    void sliderValueChanged (Slider* slider) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Plugin_testAudioProcessor& processor;
    
    Slider tremoloRate, gain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Plugin_testAudioProcessorEditor)
};
