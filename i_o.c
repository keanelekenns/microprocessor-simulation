#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "stonylake/devices.h"


/*
 * Name: i_oGetInput
 * Description: This takes an eight bit value of to determine which device to get
 *              input from
 * @params
 * uint8_t device = a binary value 0-7 of which device to get input from
 * @returns
 * uint8_t = a binary value that the 'device' inputs
 */
uint8_t i_oGetInput(uint8_t fromDeviceNum){
    uint8_t ret = devicesGiveInput(fromDeviceNum);
    if(ret == 0xff) printf("Bad value for device number\n");
    return ret;
};


/*
 * Name: i_oGiveOutput
 * Description: This gives one of the eight devices output
 * @params
 * uint8_t device = the binary value 0-7 of which device to give the output to
 * uint8_t output = output to give selected device
 * @returns
 * uint8_t = a binary value that the 'device' inputs
 */
void i_oGiveOutput(uint8_t toDeviceNum, uint8_t output){
    uint8_t rt = devicesGetOutput(toDeviceNum, output);
    assert(rt == 0b1111111);
    return;
};


/*
 * TESTER CODE
 */
int main(){
    uint8_t testDevice = 0b001;
    uint8_t testGiveOutput = 0b00000111;
    uint8_t testGetInput;

    testGetInput = i_oGetInput(testDevice);
    i_oGiveOutput(testDevice, testGiveOutput);
    printf("testGetInput %x", testGetInput);


    return 0;
}
