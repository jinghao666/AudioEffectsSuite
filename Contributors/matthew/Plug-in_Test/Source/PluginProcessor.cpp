/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Plugin_testAudioProcessor::Plugin_testAudioProcessor() : //ampTremolo(getSampleRate()),
                                                         //chorusEffect(getSampleRate()),
//                                                         delayEffect(4000,getSampleRate()),
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
}

Plugin_testAudioProcessor::~Plugin_testAudioProcessor()
{
}

//==============================================================================
const String Plugin_testAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Plugin_testAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Plugin_testAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Plugin_testAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Plugin_testAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Plugin_testAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Plugin_testAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Plugin_testAudioProcessor::setCurrentProgram (int index)
{
}

const String Plugin_testAudioProcessor::getProgramName (int index)
{
    return {};
}

void Plugin_testAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Plugin_testAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    chorus.setupChorus(sampleRate);
    delay.setupSimpleDelay(80000);
}

void Plugin_testAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Plugin_testAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Plugin_testAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    const float* inputData  = buffer.getReadPointer (0);
    float* const outputData = buffer.getWritePointer (0);
    
    for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        outputData[samp] = delay.process(inputData[samp]);
    
    for (int channel = 1; channel < totalNumOutputChannels; ++channel)
        buffer.copyFrom(channel, 0, outputData, buffer.getNumSamples());
}

//==============================================================================
bool Plugin_testAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Plugin_testAudioProcessor::createEditor()
{
    return new Plugin_testAudioProcessorEditor (*this);
}

//==============================================================================
void Plugin_testAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Plugin_testAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Plugin_testAudioProcessor();
}
