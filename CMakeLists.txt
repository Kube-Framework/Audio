find_package(SDL2 REQUIRED)

kube_add_library(Audio
    SOURCES
        Base.hpp
        Base.cpp

    LIBRARIES
        Core
        SDL2::SDL2
)