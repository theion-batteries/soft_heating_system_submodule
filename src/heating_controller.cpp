#include "heating_controller.h"



heating_controller::heating_controller(/* args */)
{
    std::cout << "creating subsystem heating controller " << std::endl;
#ifdef HEAT_CONFIG
    std::cout << "loading config file: " << HEAT_CONFIG << std::endl;
    std::ifstream filein(HEAT_CONFIG);
    for (std::string line; std::getline(filein, line); )
    {
        std::cout << line << std::endl;
    }
    config = YAML::LoadFile(HEAT_CONFIG);
    _heating_params.sulfur_temperature = config["sulfur_temperature"].as<double>();
#endif
}

heating_controller::~heating_controller()
{
}

void heating_controller::heating_controller_connect()
{

}

void heating_controller::heating_controller_activate()
{

}

void heating_controller::heating_controller_deactivate()
{

}
void heating_controller::heating_controller_settemperature(double temp)

{
    _heating_params.sulfur_temperature = temp;
}

/********* helper functions */

bool heating_controller::get_heating_controller_status()
{
    return heatingReady;
}



// direct call
void heating_controller::sendDirectCmd(std::string& cmd)
{

}

void heating_controller::reload_config_file()
{

    std::cout << "reloading config file: " << HEAT_CONFIG << std::endl;
    std::ifstream filein(HEAT_CONFIG);
    for (std::string line; std::getline(filein, line); )
    {
        std::cout << line << std::endl;
    }
    config = YAML::LoadFile(HEAT_CONFIG);
    _heating_params.sulfur_temperature = config["sulfur_temperature"].as<double>();


}