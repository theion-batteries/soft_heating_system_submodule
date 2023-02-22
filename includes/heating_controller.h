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
using enum wgm_feedbacks::enum_hw_feedback;
using enum wgm_feedbacks::enum_sub_sys_feedback;
struct heating_config_yaml_params
{
    std::string heating_server_ip= "192.168.0.208";
    uint16_t heating_server_port= 8881;
    double sulfur_temperature = 120;
    double heat_mantle1_default_set_temp = 100;
    double heat_mantle2_default_set_temp = 100;
    double heat_plate_default_set_temp = 160;
};

class heating_controller
{
private:
    sockpp::socket_initializer sockInit;
    bool heatingReady = false;
    YAML::Node config;
    heating_config_yaml_params _heating_params;
    heating_config_yaml_params _heating_params_default;
    sockpp::tcp_connector* _client=nullptr;

    std::map<u_int, std::string> heating_cmds = {
         {0,"info"}, {1,"on"}, {2,"off"},
        {3,"stay"}, {4,"temp?"},
        {5,"temp"}, {6,"state?"}, 
        {7,"plate_temp?"}, {8,"plate_temp"}, 
        {9, "set_temp?"} // get the internal set temp
    };
    std::string incoming_data;
    u_int data_length = 5012;
    double sulfur_temperature = 0;

public:
    heating_controller(std::string ip, uint16_t port);
    heating_controller();
    ~heating_controller();
    // controller
    wgm_feedbacks::enum_sub_sys_feedback heating_controller_connect();
    wgm_feedbacks::enum_sub_sys_feedback disconnect();
    wgm_feedbacks::enum_sub_sys_feedback heating_controller_activate();
    wgm_feedbacks::enum_sub_sys_feedback heating_controller_deactivate();
    wgm_feedbacks::enum_sub_sys_feedback heating_controller_settemperature(double temp);
    wgm_feedbacks::enum_sub_sys_feedback heating_controller_setpaltetemperature(double temp);
    /********* helper functions */
    bool get_heating_controller_status();
    /*     helper getter */
    double get_heating_plate_temperature();
    double get_heating_sulfur_temperature();
    double get_heating_previous_set_temperature();
    // direct call
    std::string sendDirectCmd(std::string cmd);
    std::string waitForResponse();
    void sendCmd(std::string& cmd, sockpp::tcp_connector* client, std::string args);
    wgm_feedbacks::enum_sub_sys_feedback reload_config_file();
};


