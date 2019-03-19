#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "devices.h"

uint8_t deviceZero  = 0b0000000;
uint8_t deviceOne   = 0b0000001;
uint8_t deviceTwo   = 0b0000010;
uint8_t deviceThree = 0b0000100;
uint8_t deviceFour  = 0b0001000;
uint8_t deviceFive  = 0b0010000;
uint8_t deviceSix   = 0b0100000;
uint8_t deviceSeven = 0b1000000;

uint8_t devicesGiveInput(uint8_t device){
    switch(device) {
        case 0b000:
            return deviceZero;
            break;
        case 0b001:
            return deviceOne;
            break;
        case 0b010:
            return deviceTwo;
            break;
        case 0b011:
            return deviceThree;
            break;
        case 0b100:
            return deviceFour;
            break;
        case 0b0101:
            return deviceFive;
            break;
        case 0b110:
            return deviceSix;
            break;
        case 0b111:
            return deviceSeven;
            break;
    }
    printf("Input incorrect %x\n", device);
    return device;
}
uint8_t devicesGetOutput(uint8_t device, uint8_t output){
    printf("Output put into device\n");
    return 0b1111111;
}
