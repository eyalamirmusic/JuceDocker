cmake_minimum_required(VERSION 3.16)
project(JUCEDocker)

include(CMake/CPM.cmake)

option(BUILD_JUCE_PROTOTYPE_EXAMPLES "Build JUCE prototype examples" OFF)
option(BUILD_UNIT_TESTS "" OFF)

CPMAddPackage(
        NAME JUCE_Config
        GITHUB_REPOSITORY eyalamirmusic/JUCECMakeRepoPrototype
        GIT_TAG origin/master)

CPMAddPackage("gh:yhirose/cpp-httplib#master")

add_subdirectory(Apps)