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
    _heating_params.heat_mantle1_default_set_temp = config["heat_mantle1_default_set_temp"].as<double>();
    _heating_params.heat_mantle2_default_set_temp = config["heat_mantle2_default_set_temp"].as<double>();
    _heating_params.heat_plate_default_set_temp = config["heat_plate_default_set_temp"].as<double>();

#endif
}

heating_controller::~heating_controller()
{
}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::disconnect()
{
    if (!_heating_client) _heating_client->close();
    return wgm_feedbacks::enum_sub_sys_feedback::sub_success;
}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_connect()
{
    std::cout << "connecting to heating server" << std::endl;
    _heating_client = new sockpp::tcp_connector({ _heating_server.ip, _heating_server.port });
    // Implicitly creates an inet_address from {host,port}
    // and then tries the connection.
    if (!_heating_client) {
        std::cerr << "Error connecting to server at "
            << sockpp::inet_address(_heating_server.ip, _heating_server.port)
            << "\n\t" << _heating_client->last_error_str() << std::endl;
        return wgm_feedbacks::enum_sub_sys_feedback::sub_error;
    }
    std::cout << "Created a connection from " << _heating_client->address() << std::endl;
    std::cout << "Created a connection to " << _heating_client->peer_address() << std::endl;
    // Set a timeout for the responses
    if (!_heating_client->read_timeout(std::chrono::seconds(5))) {
        std::cerr << "Error setting timeout on TCP stream: "
            << _heating_client->last_error_str() << std::endl;
        return wgm_feedbacks::enum_sub_sys_feedback::sub_error;
    }
    heatingReady = true;
    return wgm_feedbacks::enum_sub_sys_feedback::sub_success;
}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_activate()
{
    auto command = heating_cmds.find(1);
    if (command != heating_cmds.end()) {
        std::cout << "sending command: " << command->second << '\n';
        sendDirectCmd(command->second);
    }
    return wgm_feedbacks::enum_sub_sys_feedback::sub_success;

}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_deactivate()
{
    auto command = heating_cmds.find(2);
    if (command != heating_cmds.end()) {
        std::cout << "sending command: " << command->second << '\n';
        sendDirectCmd(command->second);
    }
    return wgm_feedbacks::enum_sub_sys_feedback::sub_success;

}
void heating_controller::heating_controller_settemperature(double temp)

{
    auto command = heating_cmds.find(5);
    if (command != heating_cmds.end()) {
        std::cout << "sending command: " << command->second << " args: " << temp << '\n';
        std::string args = "=" + std::to_string(temp);
        sendCmd(command->second, _heating_client, args);
    }
    _heating_params.sulfur_temperature = temp;
}
void heating_controller::heating_controller_setpaltetemperature(double temp)

{
    auto command = heating_cmds.find(8);
    if (command != heating_cmds.end()) {
        std::cout << "sending command: " << command->second << " args: " << temp << '\n';
        std::string args = "=" + std::to_string(temp);
        sendCmd(command->second, _heating_client, args);
    }
    _heating_params.sulfur_temperature = temp;
}

double heating_controller::get_heating_plate_temperature()
{
    double duration = 0;
    std::cout << "get axis curent position" << std::endl;
    auto command = heating_cmds.find(7);
    std::cout << "sending command: " << command->second << '\n';
    auto resp = sendDirectCmd(command->second);
    duration = std::stod(resp); // to double
    return duration;
}
double heating_controller::get_heating_sulfur_temperature()
{
    std::cout << "get axis curent position" << std::endl;
    auto command = heating_cmds.find(4);
    std::cout << "sending command: " << command->second << '\n';
    auto resp = sendDirectCmd(command->second);
    sulfur_temperature = std::stod(resp); // to double
    return sulfur_temperature;
}
/********* helper functions */

bool heating_controller::get_heating_controller_status()
{
    return heatingReady;
}



// direct call
std::string heating_controller::sendDirectCmd(std::string cmd)
{
    if (_heating_client == nullptr) return "not connected";
    std::cout << "sending heaitng command " << cmd << std::endl;
    cmd = cmd + "\r\n";
    if (_heating_client->write(cmd) != ssize_t(std::string(cmd).length())) {
        std::cout << "Error writing to the TCP stream: "
            << _heating_client->last_error_str() << std::endl;
    }
    return waitForResponse();
}
std::string heating_controller::waitForResponse()
{
    static int attempts = 0;
    if (attempts == 10)
    {
        std::cout << "attempts: " << attempts << std::endl;
        attempts = 0;
        return "NA";
    }
    std::cout << "awaiting server response" << std::endl;
    if (_heating_client->is_connected())
    {
        char Strholder[1024];
        ssize_t n = _heating_client->read_n(&Strholder, 1024);
        if (n > 0)
        {
            std::cout << "n bytes received: " << n << std::endl;
            heating_incoming_data = Strholder;
            heating_incoming_data.resize(n);
            std::cout << "server replied : " << heating_incoming_data << std::endl;
            return heating_incoming_data;
        }
        else
        {
            std::cout << "no server response " << n << std::endl;
            attempts++;
            return waitForResponse();
        }

    }
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
    _heating_params.heat_mantle1_default_set_temp = config["heat_mantle1_default_set_temp"].as<double>();
    _heating_params.heat_mantle2_default_set_temp = config["heat_mantle2_default_set_temp"].as<double>();
    _heating_params.heat_plate_default_set_temp = config["heat_plate_default_set_temp"].as<double>();

}

void heating_controller::sendCmd(std::string& cmd, sockpp::tcp_connector* client, std::string args)
{
    if (client->write(cmd + args) != ssize_t(std::string(cmd + args).length())) {
        std::cerr << "Error writing to the TCP stream: "
            << client->last_error_str() << std::endl;
    }
    std::cout << "command " << cmd + args << " sent" << std::endl;
}

