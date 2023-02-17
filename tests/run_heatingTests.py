import subprocess
import os

# Get the directory containing the Python script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the relative path to another file

# Replace with the path to your test executable
test_executable = os.path.join(script_dir, "../../../../../build/Debug/", "heatingTests.exe")

# Run the Connect test
connect_test_args = [test_executable, "--gtest_filter=heatingControllerTest.Connect"]
connect_test_result = subprocess.run(connect_test_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the Connect test
if connect_test_result.returncode == 0:
    print("Connect test passed!")
else:
    print("Connect test failed:")
    #print(connect_test_result.stdout.decode())
    #print(connect_test_result.stderr.decode())

# Run the Disconnect test
disconnect_test_args = [test_executable, "--gtest_filter=heatingControllerTest.Disconnect"]
disconnect_test_result = subprocess.run(disconnect_test_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the Disconnect test
if disconnect_test_result.returncode == 0:
    print("Disconnect test passed!")
else:
    print("Disconnect test failed:")
    #print(disconnect_test_result.stdout.decode())
    #print(disconnect_test_result.stderr.decode())

# Run the IsConnected test
isconnected_test_args = [test_executable, "--gtest_filter=heatingControllerTest.IsConnected"]
isconnected_test_result = subprocess.run(isconnected_test_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the IsConnected test
if isconnected_test_result.returncode == 0:
    print("IsConnected test passed!")
else:
    print("IsConnected test failed:")
    #print(isconnected_test_result.stdout.decode())
    #print(isconnected_test_result.stderr.decode())

# Run the heating_controller_activate test
heating_controller_activate_test_args = [test_executable, "--gtest_filter=heatingControllerTest.heating_controller_activate"]
heating_controller_activate_test_result = subprocess.run(heating_controller_activate_test_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the heating_controller_activate test
if heating_controller_activate_test_result.returncode == 0:
    print("heating_controller_activate test passed!")
else:
    print("heating_controller_activate test failed:")
    #print(heating_controller_activate_test_result.stdout.decode())
    #print(heating_controller_activate_test_result.stderr.decode())

# Run the heating_controller_deactivate test
heating_controller_deactivate_test_args = [test_executable, "--gtest_filter=heatingControllerTest.heating_controller_deactivate"]
heating_controller_deactivate_test_result = subprocess.run(heating_controller_deactivate_test_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the heating_controller_deactivate test
if heating_controller_deactivate_test_result.returncode == 0:
    print("heating_controller_deactivate test passed!")
else:
    print("heating_controller_deactivate test failed:")
    #print(heating_controller_deactivate_test_result.stdout.decode())
    #print(heating_controller_deactivate_test_result.stderr.decode())

# Run the heating_controller_settemperature test
heating_controller_settemperature_test_args = [test_executable, "--gtest_filter=heatingControllerTest.heating_controller_settemperature"]
heating_controller_settemperature_test_result = subprocess.run(heating_controller_settemperature_test_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the heating_controller_settemperature test
if heating_controller_settemperature_test_result.returncode == 0:
    print("heating_controller_settemperature test passed!")
else:
    print("heating_controller_settemperature test failed:")
    #print(heating_controller_settemperature_test_result.stdout.decode())
    #print(heating_controller_settemperature_test_result.stderr.decode())

# Run the heating_controller_setpaltetemperature test
heating_controller_setpaltetemperature_args = [test_executable, "--gtest_filter=heatingControllerTest.heating_controller_setpaltetemperature"]
heating_controller_setpaltetemperature_result = subprocess.run(heating_controller_setpaltetemperature_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the heating_controller_setpaltetemperature test
if heating_controller_setpaltetemperature_result.returncode == 0:
    print("heating_controller_setpaltetemperature test passed!")
else:
    print("heating_controller_setpaltetemperature test failed:")
    #print(heating_controller_setpaltetemperature_result.stdout.decode())
    #print(heating_controller_setpaltetemperature_result.stderr.decode())

# Run the get_heating_plate_temperature test
get_heating_plate_temperature_args = [test_executable, "--gtest_filter=heatingControllerTest.get_heating_plate_temperature"]
get_heating_plate_temperature_result = subprocess.run(get_heating_plate_temperature_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the get_heating_plate_temperature test
if get_heating_plate_temperature_result.returncode == 0:
    print("get_heating_plate_temperature test passed!")
else:
    print("get_heating_plate_temperature test failed:")
    #print(get_heating_plate_temperature_result.stdout.decode())
    #print(get_heating_plate_temperature_result.stderr.decode())

# Run the get_heating_sulfur_temperature test
get_heating_sulfur_temperature_args = [test_executable, "--gtest_filter=heatingControllerTest.get_heating_sulfur_temperature"]
get_heating_sulfur_temperature_result = subprocess.run(get_heating_sulfur_temperature_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the get_heating_sulfur_temperature test
if get_heating_sulfur_temperature_result.returncode == 0:
    print("get_heating_sulfur_temperature test passed!")
else:
    print("get_heating_sulfur_temperature test failed:")
    #print(get_heating_sulfur_temperature_result.stdout.decode())
    #print(get_heating_sulfur_temperature_result.stderr.decode())

# Run the reload_config_file test
reload_config_file_args = [test_executable, "--gtest_filter=heatingControllerTest.reload_config_file"]
reload_config_file_result = subprocess.run(reload_config_file_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the reload_config_file test
if reload_config_file_result.returncode == 0:
    print("reload_config_file test passed!")
else:
    print("reload_config_file test failed:")
    #print(reload_config_file_result.stdout.decode())
    #print(reload_config_file_result.stderr.decode())

# Run the sendDirectCmd test
sendDirectCmd_args = [test_executable, "--gtest_filter=heatingControllerTest.sendDirectCmd"]
sendDirectCmd_result = subprocess.run(sendDirectCmd_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Check the return code of the sendDirectCmd test
if sendDirectCmd_result.returncode == 0:
    print("sendDirectCmd test passed!")
else:
    print("sendDirectCmd test failed:")
    #print(sendDirectCmd_result.stdout.decode())
    #print(sendDirectCmd_result.stderr.decode())

