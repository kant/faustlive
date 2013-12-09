//
//  PA_audioManager.cpp
//  
//
//  Created by Sarah Denoux on 15/07/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

// PA_audioManager controls 1 PA_audioFader. It can switch from one DSP to another with a crossfade or it can act like a simple jackaudio-dsp
// PA_audioManager also controls the jack connections of the audio. 

#include "PA_audioManager.h"
#include "PA_audioFader.h"

#include <QFileInfo>

PA_audioManager::PA_audioManager(AudioSettings* as): AudioManager(as){

    
    printf("NEW PORT AUDIO\n");
    
    fSettings = dynamic_cast<PA_audioSettings*>(as);
    
    fCurrentAudio = new PA_audioFader(fSettings->get_SampleRate(), fSettings->get_BufferSize());
}

PA_audioManager::~PA_audioManager(){

    delete fCurrentAudio;
}

//INIT/START/STOP on Current PortAudio
bool PA_audioManager::initAudio(string& error, const char* name, dsp* DSP, const char* /*port_name*/){
    
    if(fCurrentAudio->init(name, DSP))
        return true;
    else{
        error = "Impossible to init PortAudio Client";
        return false;
    }
}

bool PA_audioManager::init(const char* name, dsp* DSP){
    return fCurrentAudio->init(name, DSP);
}

bool PA_audioManager::start(){
    return fCurrentAudio->start();
}

void PA_audioManager::stop(){
    fCurrentAudio->stop();
}

//Init new dsp, that will fade in current audio
bool PA_audioManager::init_FadeAudio(string& error, const char* name, dsp* DSP){

    printf("PA_audioManager::init_FadeAudio\n");
    
    fFadeInAudio = new PA_audioFader(fSettings->get_SampleRate(), fSettings->get_BufferSize());
    
    if(fFadeInAudio->init(name, DSP))
        return true;
    else{
        error = "Impossible to init new Port Audio Client";
        return false;
    }
}

//Crossfade start
void PA_audioManager::start_Fade(){

    fFadeInAudio->launch_fadeIn();
    fCurrentAudio->launch_fadeOut();
    
    fFadeInAudio->start();
}

//When the crossfade ends, the DSP is updated in jackaudio Fader
void PA_audioManager::wait_EndFade(){
    
    while(fCurrentAudio->get_FadeOut() == 1){}
    
    fCurrentAudio->stop();
    PA_audioFader* intermediate = fCurrentAudio;
    fCurrentAudio = fFadeInAudio;
    fFadeInAudio = intermediate;
    delete fFadeInAudio;
}

