#include <juce_core/juce_core.h>

using juce::Logger;
using juce::String;

struct CustomLogger : Logger
{
    void logMessage(const String& message) override
    {
        std::cout << message << std::endl;
    }
};

int main()
{
    Logger::writeToLog("Default JUCE logger");

    CustomLogger customLogger;
    Logger::setCurrentLogger(&customLogger);

    Logger::writeToLog("std::cout logger");

    Logger::setCurrentLogger(nullptr);

    return 0;
}
