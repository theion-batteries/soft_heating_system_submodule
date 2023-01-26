#pragma once
#include "sockpp/socket.h"
#include <iostream>
#include <string>
#include "sockpp/tcp_connector.h"
#include "Windows.h" 
#include <shellapi.h> 
#include <map>
#include <thread>
#include <atomic>
#include <queue>
#include <memory>
#include <fstream>
#include <iostream>
#include <string.h>
#include "yaml-cpp/yaml.h"

struct heating_config_yaml_params
{

    double sulfur_temperature = 120;


};
class heating_controller
{
private:
 
    bool heatingReady = false;
    YAML::Node config;
    heating_config_yaml_params _heating_params;
public:
    heating_controller(/* args */);
    ~heating_controller();
    // controller
    void heating_controller_connect();
    void heating_controller_activate();
    void heating_controller_deactivate();
    void heating_controller_settemperature(double temp);


    /********* helper functions */
    bool get_heating_controller_status();
    /*     helper getter */
    double get_heating_plate_temperature();
    double get_heating_sulfur_temperature();
    // direct call
    void sendDirectCmd(std::string& cmd);
    void reload_config_file();
};


