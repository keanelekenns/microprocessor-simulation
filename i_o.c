#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "stonylake/devices.h"

uint8_t i_oGetInput(uint8_t fromDeviceNum){
    return devicesGiveInput(fromDeviceNum);
};
void i_oGiveOutput(uint8_t toDeviceNum, uint8_t output){
    uint8_t rt = devicesGetOutput(toDeviceNum, output);
    assert(rt == 0b1111111);
    return;
};

int main(){
    uint8_t testDevice = 0b001;
    uint8_t testGiveOutput = 0b00000111;
    uint8_t testGetInput;

    testGetInput = i_oGetInput(testDevice);
    i_oGiveOutput(testDevice, testGiveOutput);
    printf("testGetInput %x", testGetInput);


    return 0;
}