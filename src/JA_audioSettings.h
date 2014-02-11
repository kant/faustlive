//
//  JA_audioSettings.h
//  
//
//  Created by Sarah Denoux on 15/07/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

// This class describes the Settings of a jackaudio, which are non-existant 

#ifndef _JA_audioSettings_h
#define _JA_audioSettings_h

#include "AudioSettings.h"

class JA_audioSettings : public AudioSettings{

    public :
    JA_audioSettings(QString home, QGroupBox* parent);
    
        virtual ~JA_audioSettings();
    
        virtual void readSettings();
        virtual void writeSettings();
        virtual void setVisualSettings();
        virtual void storeVisualSettings();
    
        virtual bool isEqual(AudioSettings* as);
    
        virtual QString get_ArchiName();
};

#endif
