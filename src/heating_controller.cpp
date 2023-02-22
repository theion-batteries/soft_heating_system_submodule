#include "heating_controller.h"



heating_controller::heating_controller(std::string ip, uint16_t port)
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

    _heating_params.heating_server_ip = ip;
    _heating_params.heating_server_port = port;
#endif
}
heating_controller::heating_controller()
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

    _heating_params.heating_server_ip = config["heating_server_ip"].as<std::string>();
    _heating_params.heating_server_port = config["heating_server_port"].as<uint16_t>();
#endif
}
heating_controller::~heating_controller()
{
}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::disconnect()
{
    if (!_client)
    {
        _client->close();
        heatingReady = false;

        return wgm_feedbacks::enum_sub_sys_feedback::sub_success;
    }
    return wgm_feedbacks::enum_sub_sys_feedback::sub_error;

}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_connect()
{
    std::cout << "connecting to heating server " << _heating_params.heating_server_ip << std::endl;
    _client = new sockpp::tcp_connector({ _heating_params.heating_server_ip, _heating_params.heating_server_port });
    // Implicitly creates an inet_address from {host,port}
    // and then tries the connection.
    if (!_client) {
        std::cerr << "Error connecting to server at "
            << sockpp::inet_address(_heating_params.heating_server_ip, _heating_params.heating_server_port)
            << "\n\t" << _client->last_error_str() << std::endl;
        return wgm_feedbacks::enum_sub_sys_feedback::sub_error;
    }
    std::cout << "Created a connection from " << _client->address() << std::endl;
    std::cout << "Created a connection to " << _client->peer_address() << std::endl;
    // Set a timeout for the responses
    if (!_client->read_timeout(std::chrono::seconds(5))) {
        std::cerr << "Error setting timeout on TCP stream: "
            << _client->last_error_str() << std::endl;
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
        auto reply = sendDirectCmd(command->second);
        std::cout << "activate reply received " << reply << '\n';
        if (reply == "ok") return sub_success;
        return sub_error;
    }
    return sub_error;
}

wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_deactivate()
{
    auto command = heating_cmds.find(2);
    if (command != heating_cmds.end()) {
        std::cout << "sending command: " << command->second << '\n';
        auto reply = sendDirectCmd(command->second);
        std::cout << "deactivate reply received " << reply << '\n';
        if (reply == "ok") return sub_success;
        return sub_error;
    }
    return sub_error;
}
wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_settemperature(double temp)

{
    auto command = heating_cmds.find(5);
    if (command != heating_cmds.end()) {
        _heating_params.sulfur_temperature = temp;
        std::cout << "sending command: " << command->second << " args: " << temp << '\n';
        std::string args = "=" + std::to_string(temp);
        auto reply = sendDirectCmd(command->second + args);
        std::cout << "set temp reply received " << reply << '\n';
        if (reply == "ok") return sub_success;
        return sub_error;
    }
    return sub_error;
}
wgm_feedbacks::enum_sub_sys_feedback heating_controller::heating_controller_setpaltetemperature(double temp)

{
    auto command = heating_cmds.find(8);
    if (command != heating_cmds.end()) {
        _heating_params.sulfur_temperature = temp;
        std::cout << "sending command: " << command->second << " args: " << temp << '\n';
        std::string args = "=" + std::to_string(temp);
        auto reply = sendDirectCmd(command->second + args);
        std::cout << "set temp reply received " << reply << '\n';
        if (reply == "ok") return sub_success;
        return sub_error;
    }
    return sub_error;
}

double heating_controller::get_heating_plate_temperature()
{
    double duration = 0;
    std::cout << "get heating plate temperature" << std::endl;
    auto command = heating_cmds.find(7);
    std::cout << "sending command: " << command->second << '\n';
    auto resp = sendDirectCmd(command->second);
    duration = std::stod(resp); // to double
    return duration;
}
double heating_controller::get_heating_sulfur_temperature()
{
    std::cout << "get heating  temperature" << std::endl;
    auto command = heating_cmds.find(4);
    std::cout << "sending command: " << command->second << '\n';
    auto resp = sendDirectCmd(command->second);
    if (!resp.find("ok"))
    {
        std::cout << "missing ok, error" << std::endl;
        return 0;
    }
    sulfur_temperature = std::stod(resp); // to double
    return sulfur_temperature;
}

double heating_controller::get_heating_previous_set_temperature()
{
    std::cout << "get heating pervious set temperature" << std::endl;
    auto command = heating_cmds.find(9);
    std::cout << "sending command: " << command->second << '\n';
    auto resp = sendDirectCmd(command->second);
    if (!resp.find("ok"))
    {
        std::cout << "missing ok, error" << std::endl;
        return 0;
    }
    sulfur_temperature = std::stod(resp); // to double
    return sulfur_temperature;
}

/********* helper functions */

bool heating_controller::get_heating_controller_status()
{
    std::cout << "check heating status: " << heatingReady << std::endl;

    return heatingReady;
}



// direct call
std::string heating_controller::sendDirectCmd(std::string cmd)
{
    if (_client == nullptr) return "not connected";
    std::cout << "sending heating command " << cmd << std::endl;
    cmd = cmd + "\r\n";
    if (_client->write(cmd) != ssize_t(std::string(cmd).length())) {
        std::cout << "Error writing to the TCP stream: "
            << _client->last_error_str() << std::endl;
    }
    return waitForResponse();
}
std::string heating_controller::waitForResponse()
{
    std::cout << "awaiting server response" << std::endl;
    auto start = std::chrono::steady_clock::now();
    while (_client->is_connected())
    {

        char Strholder[5012];

        ssize_t n = _client->read_n(&Strholder, sizeof(Strholder));
        if (n > 0)
        {
            std::cout << "n bytes received: " << n << std::endl;
            incoming_data = Strholder;
            incoming_data.resize(n);
            std::cout << "server replied : " << incoming_data << std::endl;
            break;
        }
        else
        {
            std::cout << "no server response, retry " << n << std::endl;
            incoming_data = "NA";
            long long timeout = 10;
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
            if (duration >= timeout)
            {
                std::cout << "no response within a timeout of " << duration << " seconds, " << "aborting.." << std::endl;
                break;
            }
            continue;
        }

    }
    return incoming_data;
}
wgm_feedbacks::enum_sub_sys_feedback heating_controller::reload_config_file()
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
    _heating_params.heating_server_ip = config["heating_server_ip"].as<std::string>();
    _heating_params.heating_server_port = config["heating_server_port"].as<uint16_t>();
    return sub_success;
}

void heating_controller::sendCmd(std::string& cmd, sockpp::tcp_connector* client, std::string args)
{
    if (client->write(cmd + args) != ssize_t(std::string(cmd + args).length())) {
        std::cerr << "Error writing to the TCP stream: "
            << client->last_error_str() << std::endl;
    }
    std::cout << "command " << cmd + args << " sent" << std::endl;
}

