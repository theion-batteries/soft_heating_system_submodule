#include <gtest/gtest.h>

#include "heating_controller.h"

class heatingControllerTest : public ::testing::Test {
protected:
    heating_controller* heatingControl ;

    void SetUp() override {
        heatingControl = new heating_controller ("127.0.0.1", 8881);
       heatingControl->heating_controller_connect();
    }

    void TearDown() override {
       heatingControl->disconnect();
       delete heatingControl;
    }
};

TEST_F(heatingControllerTest, Connect) {
    EXPECT_EQ(wgm_feedbacks::enum_sub_sys_feedback::sub_success, heatingControl->heating_controller_connect());
}
TEST_F(heatingControllerTest, Disconnect) {
    EXPECT_EQ(wgm_feedbacks::enum_sub_sys_feedback::sub_success, heatingControl->disconnect());
}
TEST_F(heatingControllerTest, IsConnected) {
    EXPECT_TRUE(heatingControl->get_heating_controller_status());
}
TEST_F(heatingControllerTest, heating_controller_activate) {
    EXPECT_EQ(wgm_feedbacks::enum_sub_sys_feedback::sub_success, heatingControl->heating_controller_activate());
}
TEST_F(heatingControllerTest, heating_controller_deactivate) {
    EXPECT_EQ(wgm_feedbacks::enum_sub_sys_feedback::sub_success, heatingControl->heating_controller_deactivate());
}
TEST_F(heatingControllerTest, heating_controller_settemperature) {
    EXPECT_EQ(wgm_feedbacks::enum_sub_sys_feedback::sub_success, heatingControl->heating_controller_settemperature(150));
}
TEST_F(heatingControllerTest, heating_controller_setpaltetemperature) {
    EXPECT_EQ(wgm_feedbacks::enum_sub_sys_feedback::sub_success, heatingControl->heating_controller_setpaltetemperature(120));
}
TEST_F(heatingControllerTest, get_heating_plate_temperature) {
    EXPECT_EQ(100, heatingControl->get_heating_plate_temperature());
}
TEST_F(heatingControllerTest, get_heating_sulfur_temperature) {
    EXPECT_EQ(120, heatingControl->get_heating_sulfur_temperature());
}
TEST_F(heatingControllerTest, reload_config_file) {
    EXPECT_EQ(sub_success, heatingControl->reload_config_file());
}
