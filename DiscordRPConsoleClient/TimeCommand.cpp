#include "pch.h"

#include "TimeCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"
#include <iomanip>
#include <sstream>
#include <regex>

void TimeCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string* type = nullptr;
    std::string timeStr = "";
    bool updateRequired = false;
    for (unsigned i = 0; i < argsLength; i++) {
        // Check for new option.
        if (!args[i].rfind("--", 0)) {
            if (type) {
                // Save previous option.
                if (updateTime(*type, timeStr)) {
                    updateRequired = true;
                }
            }
            timeStr.clear();
            if (!sutils::equalsIgnoreCase(args[i], "--starttime") && !sutils::equalsIgnoreCase(args[i], "--endtime")) {
                std::cout << "Skipped type " << args[i] << " because it's not valid!" << std::endl;
                type = nullptr;
            } else {
                type = &args[i];
            }
            continue;
        }
        if (!type) {
            // Unknown option just skip.
            continue;
        }
        timeStr += (timeStr.empty() ? "" : " ") + args[i];
    }
    if (type && updateTime(*type, timeStr)) {
        updateRequired = true;
    }
    if (!updateRequired) {
        std::cout << "Nothing to update." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    if (!dhandler.updatePresence()) {
        dhandler.printNotConnectedErrorMessage();
    }
}

extern "C" char* strptime(const char* s, const char* f, struct tm* tm) {
    std::istringstream input(s);
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, f);
    if (input.fail()) {
        return nullptr;
    }
    std::istringstream::streamoff data = input.tellg();
    return (char*) (s + data);
}

bool TimeCommand::updateTime(const std::string& type, const std::string& timeStr) {
    std::time_t timestamp;
    bool reset = sutils::equalsIgnoreCase(timeStr, "reset");
    if (reset) {
        timestamp = -1;
    } else {
        // This regex won't filter everything but it's good enough for the only reason it exists.
        // https://developercommunity.visualstudio.com/content/problem/18311/stdget-time-asserts-with-istreambuf-iterator-is-no.html
        std::regex dateRegex("([0-9]{4})-(1|0)?([0-9]{1})-([0-3]?)([0-9]{1}) ([0-2]?)([0-9]{1}):([0-6]?)([0-9]{1}):([0-5]?)([0-9]{1})");
        if (!std::regex_match(timeStr, dateRegex)) {
            std::cout << "\"" << timeStr << "\" is not a proper date! Use the following format: yyyy-MM-dd HH:mm:ss" << std::endl;
            return false;
        }
        std::tm tm;
        const char* sdate = strptime(timeStr.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
        if (!sdate) {
            std::cout << "\"" << timeStr << "\" is not a proper date! Use the following format: yyyy-MM-dd HH:mm:ss" << std::endl;
            return false;
        }
        timestamp = std::mktime(&tm);
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool startTime = sutils::equalsIgnoreCase(type, "--starttime");
    bool updateRequired = startTime ? !dhandler.setStartTimestamp(timestamp, false) : !dhandler.setEndTimestamp(timestamp, false);
    if (reset || timestamp == -1) {
        std::cout << (reset ? "" : "Invalid date! ") << "Resetting \"" << (startTime ? "start" : "end") << "\" timestamp." << std::endl;
    } else {
        std::cout << "Updating \"" << (startTime ? "start" : "end") << "\" timestamp to \"" << timeStr << "\"." << std::endl;
    }
    return updateRequired;
}