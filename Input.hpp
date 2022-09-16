/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Audio output device
 */

#pragma once

#include <Kube/Core/TrivialFunctor.hpp>

#include "Device.hpp"

namespace kF::Audio
{
    class Input;
}

/** @brief Physical output device abstraction */
class kF::Audio::Input final : public Device
{
public:
    /** @brief Audio callback functor */
    using Callback = Core::TrivialFunctor<void(const float * const, const std::uint32_t)>;


    /** @brief Destructor */
    ~Input(void) noexcept override = default;

    /** @brief Constructor */
    Input(const DeviceModel &deviceModel, const DeviceSpecs &deviceSpecs, Callback &&callback) noexcept
        : Device(deviceModel, deviceSpecs), _callback(std::move(callback)) {}


private:
    /** @brief Audio callback */
    void onAudioCallback(float * const data, const std::uint32_t blockSize) const noexcept final
        { _callback(data, blockSize); }


    Callback _callback {};
};