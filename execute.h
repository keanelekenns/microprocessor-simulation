#include <stdint.h>
#include "decode.h"

#ifndef __execute_h__
#define __execute_h__

#define PCL_MASK 0xFF
#define L 7
#define H 6

void T1_execute(uint8_t t1_control, DecodeControl control);

void T2_execute(uint8_t t2_control, DecodeControl control);

void T3_execute(uint8_t t3_control, DecodeControl control);

void T4_execute(uint8_t t4_control, DecodeControl control);

void T5_execute(uint8_t t5_control, DecodeControl control);

void execute_alu_operation(DecodeControl control);

#endif