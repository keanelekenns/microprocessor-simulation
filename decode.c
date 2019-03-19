#include "decode.h"

// Initialize control to defaults for first first cycle
DecodeControl init_decode_control(DecodeControl decode_control) {
    decode_control.current_cycle = 0;
    decode_control.alu_operation = 0;
    decode_control.source_register = 0;
    decode_control.destination_register = 0;

    // Set first cycle to default memory fetch
    decode_control.t1_control[0] = PCL_OUT;
    decode_control.t2_control[0] = PCH_OUT;
    decode_control.t3_control[0] = FETCH;
    decode_control.t1_control[0] = 0;
    decode_control.t1_control[0] = 0;

    // Set remaining cycles to no operation
    decode_control.cycle_length = 1;
    for (uint8_t i = 2; i < 3; i++) {
        decode_control.t1_control[i] = 0;
        decode_control.t2_control[i] = 0;
        decode_control.t3_control[i] = 0;
        decode_control.t4_control[i] = 0;
        decode_control.t5_control[i] = 0;
    }

    return decode_control;
}

// Decode opcode and generate control
DecodeControl decode(DecodeControl decode_control, uint8_t opcode) {
    decode_control = init_decode_control(decode_control);

    // Decode and control generation for instructions
    if (opcode <= 0xFE && opcode >= 0xC0) {
        // Lr1r2, LrM, LMr
        // Byte format
        // 11 DDD SSS
        // Covers all values of DDD SSS
        decode_control.source_register = opcode & SSS_MASK;
        decode_control.destination_register = (DDD_MASK & opcode) >> DDD_SHIFT;

        if (decode_control.source_register == 0b00000111) {
            // LrM
            decode_control.t1_control[1] = REGL_OUT;
            decode_control.t2_control[1] = REGH_OUT;
            decode_control.t3_control[1] = REGB_OUT;
            decode_control.t5_control[1] = REGB_TO_DDD;
        } else if (decode_control.destination_register == 0b00111000) {
            // LMr
            decode_control.t4_control[0] = SSS_TO_REGB;
            decode_control.t1_control[1] = REGL_OUT;
            decode_control.t2_control[1] = REGH_OUT;
            decode_control.t3_control[1] = REGB_OUT;
        } else {
            // Lr1r2
            decode_control.t4_control[0] = SSS_TO_REGB;
            decode_control.t5_control[0] = REGB_TO_DDD;
        }
    }

    return decode_control;
}
