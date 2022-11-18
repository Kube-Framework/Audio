/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Audio manager
 */

#include <SDL2/SDL.h>

#include <Kube/Core/Abort.hpp>

#include "Manager.hpp"

using namespace kF;

Audio::Manager::~Manager(void) noexcept
{
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

Audio::Manager::Manager(void) noexcept
    : _driver([] {
        kFEnsure(!SDL_WasInit(SDL_INIT_AUDIO),
            "Audio::Manager: Manager already initialized");

        kFEnsure(!SDL_Init(SDL_INIT_AUDIO),
            "Audio::Manager: Couldn't initialize SDL2 audio subsystem");

        kFEnsure(SDL_WasInit(SDL_INIT_AUDIO),
            "Audio::Manager: Audio initialization failed");

        return Driver(SDL_GetCurrentAudioDriver());
    }())
{
}

Audio::Drivers Audio::Manager::getAvailableDrivers(void) const noexcept
{
    const auto driverCount = SDL_GetNumAudioDrivers();
    Drivers drivers(static_cast<std::uint32_t>(driverCount));

    for (auto i = 0; i != driverCount; ++i)
        drivers[static_cast<std::uint32_t>(i)] = SDL_GetAudioDriver(i);
    return drivers;
}

void Audio::Manager::setDriver(const Driver &driver) noexcept
{
    _driver = driver;
    SDL_AudioQuit();
    SDL_AudioInit(driver.data());
}

Audio::DeviceModels Audio::Manager::getAvailableDeviceModels(const bool isCapture) const noexcept
{
    const auto deviceCount = SDL_GetNumAudioDevices(isCapture);
    DeviceModels deviceModels(deviceCount);

    for (auto i = 0; i != deviceCount; ++i)
        deviceModels[static_cast<std::uint32_t>(i)] = SDL_GetAudioDeviceName(i, isCapture);
    return deviceModels;
}