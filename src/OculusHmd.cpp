/**
 * @file    OculusHmdOrientation.cpp
 * @brief   Minimal application to get orientation from the Oculus Rift Head Mounted Display in C++ 
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#include "OVR.h"

#include <iostream>
#include <conio.h>
#include <memory>

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
    OVR::Ptr<OVR::SensorDevice>            mSensorPtr;
    std::shared_ptr<OVR::SensorFusion>  mSensorFusionPtr;
    OVR::HMDInfo                        mHMDInfo;
    bool                                mbInfoLoaded;
};

/// Now lets initialize the SDK:
OculusHMD::OculusHMD() :
    mbInfoLoaded(false) {
    OVR::Ptr<OVR::DeviceManager>    managerPtr;
    OVR::Ptr<OVR::HMDDevice>        hmdDevicePtr;
    OVR::Ptr<OVR::Profile>          userProfilePtr;

    std::cout << "--------------------------" << std::endl;
//    OVR::System::Init();  // done by mSystem constructor

    mSensorFusionPtr.reset(new OVR::SensorFusion());
    managerPtr = *(OVR::DeviceManager::Create());

    hmdDevicePtr = *(managerPtr->EnumerateDevices<OVR::HMDDevice>().CreateDevice());
    if (hmdDevicePtr) {
        std::cout << " [x] HMD Found" << std::endl;

        mbInfoLoaded = hmdDevicePtr->GetDeviceInfo(&mHMDInfo);

        mSensorPtr = *(hmdDevicePtr->GetSensor());

        // Retrieve relevant profile settings. 
        userProfilePtr = hmdDevicePtr->GetProfile();
        if (userProfilePtr) {
            userProfilePtr->GetEyeHeight();
            userProfilePtr.Clear();
        }
        hmdDevicePtr.Clear();
    } else {
        std::cout << " [ ] HMD Not Found" << std::endl;

        mSensorPtr = *(managerPtr->EnumerateDevices<OVR::SensorDevice>().CreateDevice());
    }
    managerPtr.Clear();

    if (false == mbInfoLoaded) {
        fakeInfo();
    }

    if (mSensorPtr)    {
        std::cout << " [x] Sensor Found" << std::endl;
        mSensorFusionPtr->AttachToSensor(mSensorPtr);
        mSensorFusionPtr->SetPredictionEnabled(true);
    } else {
        std::cout << " [ ] Sensor Not Found" << std::endl;
    }

    std::cout << "--------------------------" << std::endl;
}

// Next lets add a function to clean things up (this could be called in a destructor):
OculusHMD::~OculusHMD()
{
    mSensorPtr.Clear();
    mSensorFusionPtr.reset();

//     OVR::System::Destroy();  // done by mSystem destructor
    std::cout << "--------------------------" << std::endl;
}

void OculusHMD::fakeInfo() {
    mHMDInfo.HResolution = 1280;
    mHMDInfo.VResolution = 800;
    mHMDInfo.HScreenSize = 0.149759993f;
    mHMDInfo.VScreenSize = 0.0935999975f;
    mHMDInfo.VScreenCenter = 0.0467999987f;
    mHMDInfo.EyeToScreenDistance    = 0.0410000011f;
    mHMDInfo.LensSeparationDistance = 0.0635000020f;
    mHMDInfo.InterpupillaryDistance = 0.0640000030f;
    mHMDInfo.DistortionK[0] = 1.00000000f;
    mHMDInfo.DistortionK[1] = 0.219999999f;
    mHMDInfo.DistortionK[2] = 0.239999995f;
    mHMDInfo.DistortionK[3] = 0.000000000f;
    mHMDInfo.ChromaAbCorrection[0] = 0.995999992f;
    mHMDInfo.ChromaAbCorrection[1] = -0.00400000019f;
    mHMDInfo.ChromaAbCorrection[2] = 1.01400006f;
    mHMDInfo.ChromaAbCorrection[3] = 0.000000000f;
    mHMDInfo.DesktopX = 0;
    mHMDInfo.DesktopY = 0;
    mbInfoLoaded = true;
}

void OculusHMD::Output() {
    if (mbInfoLoaded) {
        std::cout << " DisplayDeviceName: " << mHMDInfo.DisplayDeviceName << std::endl;
        std::cout << " ProductName: " << mHMDInfo.ProductName << std::endl;
        std::cout << " Manufacturer: " << mHMDInfo.Manufacturer << std::endl;
        std::cout << " Version: " << mHMDInfo.Version << std::endl;
        std::cout << " HResolution: " << mHMDInfo.HResolution<< std::endl;
        std::cout << " VResolution: " << mHMDInfo.VResolution<< std::endl;
        std::cout << " HScreenSize: " << mHMDInfo.HScreenSize<< std::endl;
        std::cout << " VScreenSize: " << mHMDInfo.VScreenSize<< std::endl;
        std::cout << " VScreenCenter: " << mHMDInfo.VScreenCenter<< std::endl;
        std::cout << " EyeToScreenDistance: " << mHMDInfo.EyeToScreenDistance << std::endl;
        std::cout << " LensSeparationDistance: " << mHMDInfo.LensSeparationDistance << std::endl;
        std::cout << " InterpupillaryDistance: " << mHMDInfo.InterpupillaryDistance << std::endl;
        std::cout << " DistortionK[0]: " << mHMDInfo.DistortionK[0] << std::endl;
        std::cout << " DistortionK[1]: " << mHMDInfo.DistortionK[1] << std::endl;
        std::cout << " DistortionK[2]: " << mHMDInfo.DistortionK[2] << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

    std::cout << std::endl << " Press ENTER to continue" << std::endl;

    std::cin.get();
}

void OculusHMD::Loop() {
    while (mSensorPtr) {
        OVR::Quatf quaternion = mSensorFusionPtr->GetOrientation();

        float yaw, pitch, roll;
        quaternion.GetEulerAngles<OVR::Axis_Y, OVR::Axis_X, OVR::Axis_Z>(&yaw, &pitch, &roll);
        std::cout << " Yaw: " << OVR::RadToDegree(yaw)
                  << ", Pitch: " << OVR::RadToDegree(pitch)
                  << ", Roll: " << OVR::RadToDegree(roll) << std::endl;
        Sleep(200);

        if (_kbhit())
            break;
    }
}

int main() {
    OculusHMD oculusHMD;
    oculusHMD.Output();
    oculusHMD.Loop();
}
