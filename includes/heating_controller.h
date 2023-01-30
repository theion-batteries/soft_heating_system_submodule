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
#include "subsystem_feedback.h"
struct heating_config_yaml_params
{
    double sulfur_temperature = 120;
    double heat_mantle1_default_set_temp = 100;
    double heat_mantle2_default_set_temp = 100;
    double heat_plate_default_set_temp = 160;
};
struct heating_server
{
    const char* ip = "192.168.0.208";
    uint16_t port = 8881;
};
class heating_controller
{
private:
    heating_server _heating_server;
    sockpp::socket_initializer sockInit;
    bool heatingReady = false;
    YAML::Node config;
    heating_config_yaml_params _heating_params;
    heating_config_yaml_params _heating_params_default;
    sockpp::tcp_connector* _heating_client;

    std::map<u_int, std::string> heating_cmds = {
         {0,"info"}, {1,"on"}, {2,"off"},
        {3,"stay"}, {4,"temp?"},
        {5,"temp"}, {6,"state?"}, 
        {7,"plate_temp?"}, {8,"plate_temp"}
    };
    std::string heating_incoming_data;
    u_int heating_data_length = 1024;
    double sulfur_temperature = 0;

public:
    heating_controller(/* args */);
    ~heating_controller();
    // controller
    wgm_feedbacks::enum_sub_sys_feedback heating_controller_connect();
    void disconnect();
    void heating_controller_activate();
    void heating_controller_deactivate();
    void heating_controller_settemperature(double temp);
    void heating_controller_setpaltetemperature(double temp);
    /********* helper functions */
    bool get_heating_controller_status();
    /*     helper getter */
    double get_heating_plate_temperature();
    double get_heating_sulfur_temperature();
    // direct call
    std::string sendDirectCmd(std::string cmd);
    std::string waitForResponse();
    void sendCmd(std::string& cmd, sockpp::tcp_connector* client, std::string args);
    void reload_config_file();
};


