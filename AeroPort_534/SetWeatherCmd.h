#pragma once
#include "Command.h"
#include "Flight.h"
#include <sstream>
#include <string>
#include <vector>
#include <memory>

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;
    virtual void updateWeather(const std::string& newWeather) = 0;
};

class SetWeatherCmd : public Command {
private:
    std::string newWeather; 
    std::vector<std::shared_ptr<WeatherObserver>> observers; 

public:
    SetWeatherCmd(std::stringstream& ss);

    void attach(std::shared_ptr<WeatherObserver> observer);
    void notifyObservers();

    void execute() override;
    void undo() override {}
};

class FlightWeatherWatch : public WeatherObserver {
private:
    std::shared_ptr<Flight> flight;
public:
    FlightWeatherWatch(std::shared_ptr<Flight> f) : flight(f) {}
    void updateWeather(const std::string& newWeather) override;
};