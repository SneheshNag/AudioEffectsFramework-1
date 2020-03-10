//
// Created by Rishikesh Daoo on 2/15/20.
//  Copyright © 2020 Rishikesh Daoo. All rights reserved.
//

#ifndef AUDIOFXFRAMEWORK_AUDIOEFFECTDELAY_H
#define AUDIOFXFRAMEWORK_AUDIOEFFECTDELAY_H


#include "AudioEffect.h"
#include "RingBuffer.h"
#include "Lfo.h"

#include <stdio.h>
#include <iostream>

class CAudioEffectDelay: public CAudioEffect
{
public:
    
    enum DelayType_t
    {
        kDelay,
        kFlanger,
        kChorus,
        kPhaser
    };
    
    CAudioEffectDelay();
    CAudioEffectDelay(float fSampleRateInHz, int iNumChannels, int iMaxDelayInSec, EffectParam_t params[], float values[], int iNumParams);
    ~CAudioEffectDelay();

    Error_t init(float fSampleRateInHz, int iNumChannels, int iMaxDelayInSec, EffectParam_t params[], float values[], int iNumParams);
    Error_t reset();

    Error_t setParam(EffectParam_t eParam, float fValue);
    float getParam(EffectParam_t eParam);
    
    Error_t setDelayType(DelayType_t eValue);
    DelayType_t getDelayType();

    Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames);

private:

    CRingBuffer<float>  **m_ppCRingBuffer;
    DelayType_t m_eDelayType;
    float m_fModGain;
    
    float m_fGain;
    float m_fDelay;
    float m_fMaxDelay;
    
    CLfo *m_pCLfo;
//    CRingBuffer<float> **m_ppCRingBuff;
    
};


#endif //AUDIOFXFRAMEWORK_AUDIOEFFECTDELAY_H