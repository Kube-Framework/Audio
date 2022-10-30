/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Audio device
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "Base.hpp"

namespace kF::Audio
{
    class Device;


    /** @brief Device device model */
    using DeviceModel = std::string_view;

    /** @brief List of audio device device models */
    using DeviceModels = Core::Vector<DeviceModel, AudioAllocator>;


    /** @brief Specifications of an audio device */
    struct DeviceSpecs
    {
        std::uint32_t sampleRate;
        std::uint32_t blockSize;
        bool stereo {};
    };
}

/** @brief Physical device abstraction */
class kF::Audio::Device
{
public:
    /** @brief Destructor */
    virtual ~Device(void) noexcept;

    /** @brief Constructor */
    Device(const DeviceModel &deviceModel, const DeviceSpecs &deviceSpecs) noexcept;


    /** @brief Start the device */
    void start(void) const noexcept;

    /** @brief Stop the device */
    void stop(void) const noexcept;


protected:
    /** @brief Virtual audio callback */
    virtual void onAudioCallback(float * const data, const std::uint32_t blockSize) const noexcept = 0;


    std::uint32_t _id {};
};