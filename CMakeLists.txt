cmake_minimum_required(VERSION 3.16)
project(JUCEDocker)

include(CMake/CPM.cmake)

option(BUILD_JUCE_PROTOTYPE_EXAMPES "Build JUCE prototype examples" OFF)

CPMAddPackage(
        NAME JUCE_Config
        GITHUB_REPOSITORY eyalamirmusic/JUCECMakeRepoPrototype
        GIT_TAG origin/master)

add_subdirectory(Apps)