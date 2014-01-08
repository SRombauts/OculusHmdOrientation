/**
 * @file    OculusHMD.h
 * @brief   Minimal application to get orientation from the Oculus Rift Head Mounted Display in C++ 
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <OVR.h>
#include <memory>


/**
 * @brief   Minimal application to get orientation from the Oculus Rift Head Mounted Display in C++ 
 */
class OculusHMD {
public:
    OculusHMD();
    ~OculusHMD();
    void Output();
    void Loop();

    // Fake OculusHMD rendering HMD info in cas of no device found (for dev)
    void fakeInfo();

private:
    OVR::System                         mSystem;
    OVR::Ptr<OVR::SensorDevice>         mSensorPtr;
    std::shared_ptr<OVR::SensorFusion>  mSensorFusionPtr;
    OVR::HMDInfo                        mHMDInfo;
    bool                                mbInfoLoaded;
};

