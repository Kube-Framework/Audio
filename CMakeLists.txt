find_package(SDL2 REQUIRED)

kube_add_library(Audio
    SOURCES
        Base.hpp
        Manager.hpp
        Manager.cpp
        Output.hpp
        Output.cpp
        Input.hpp
        Input.cpp

    LIBRARIES
        Core
        SDL2::SDL2
)