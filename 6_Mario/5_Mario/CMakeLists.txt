# Version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Mario_SFML)

# Définir le standard de C++ (SFML fonctionne bien avec C++11 et supérieur)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter l'exécutable et ses fichiers sources
add_executable(MiniMario
    code/main.cpp
    code/game.cpp
    code/Player.cpp
    code/maker.cpp
    code/monster.cpp
    code/Tilemap.cpp
)

# Ajouter le répertoire des fichiers d'en-tête
target_include_directories(MiniMario PRIVATE include)

# Trouver SFML automatiquement
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

# Lier les bibliothèques SFML
target_link_libraries(MiniMario PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

if (WIN32)
    # Pour Release
    set_target_properties(MiniMario PROPERTIES
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS"
    )
    # Pour Debug
    set_target_properties(MiniMario PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS"
    )
endif()