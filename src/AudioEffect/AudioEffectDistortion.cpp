//
//  AudioEffectDistortion.h
//  AudioEffectsFramework
//
//  Created by Snehesh Nag on 2/21/20.
//  Copyright © 2020 Snehesh Nag. All rights reserved.
//

#include "AudioEffectDistortion.h"
#include <cmath>

CAudioEffectDistortion::CAudioEffectDistortion()
{
    m_eEffectType = kDistortion;
    m_fGain = 0.f;
    m_fDryWetMix = 1.f;
    m_iNumChannels = 0;
    m_fSampleRateInHz = 0;
    m_bIsInitialized = false;
};

CAudioEffectDistortion::CAudioEffectDistortion(float fSampleRateInHz, int iNumChannels, EffectParam_t params[] = NULL, float values[] = NULL, int iNumParams = 0)
{
    m_eEffectType = kDistortion;
    init(fSampleRateInHz, iNumChannels, params, values, iNumParams);
};

CAudioEffectDistortion::~CAudioEffectDistortion()
{
    
};

Error_t CAudioEffectDistortion::init(float fSampleRateInHz, int iNumChannels, EffectParam_t params[] = NULL, float values[] = NULL, int iNumParams = 0)
{
    
    m_fSampleRateInHz = fSampleRateInHz;
    m_iNumChannels = iNumChannels;
    
    for (int i = 0; i < iNumParams; i++)
    {
        switch (params[i]) {
            case kParamGain:
                m_fGain = values[i];
                break;
            case kParamDryWetMix:
                m_fDryWetMix = values[i];
                break;
            default:
                break;
        }
    }
    
    m_bIsInitialized = true;
    
    return kNoError;
};

Error_t CAudioEffectDistortion::reset()
{
    return kNoError;
};

Error_t CAudioEffectDistortion::setParam(EffectParam_t eParam, float fValue)
{
    if (!m_bIsInitialized)
        return kNotInitializedError;
    
    switch (eParam) {
        case kParamDistortion:
            m_fGain = fValue;
            break;
        case kParamDryWetMix:
            m_fDryWetMix = fValue;
            break;
        default:
            return kFunctionInvalidArgsError;
            break;
    }
    return kNoError;
};

float CAudioEffectDistortion::getParam(EffectParam_t eParam)
{
    if (!m_bIsInitialized)
        return kNotInitializedError;
    
    switch (eParam) {
        case kParamGain:
            return m_fGain;
            break;
        case kParamDryWetMix:
            return m_fDryWetMix;
            break;
            
        default:
            return 0.f;
            break;
    }
};

Error_t CAudioEffectDistortion::process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{
    for (int channel = 0; channel < m_iNumChannels; channel++)
    {
        for (int frame = 0; frame < iNumberOfFrames; frame++)
        {
            float q = ppfInputBuffer[channel][frame] * m_fGain;
            float z = copysign(1-exp(-abs(q)), q);
            ppfOutputBuffer[channel][frame] = m_fDryWetMix*z + (1-m_fDryWetMix) * ppfInputBuffer[channel][frame];
        }
    }
    return kNoError;
};

