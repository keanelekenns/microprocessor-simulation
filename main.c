#include "memory.h"
#include "decode.h"
#include "devices.h"
#include "ALU.h"

#define PCL_MASK 0xFF
#define L 5
#define H 6

void T1_execute(uint8_t control) {
    uint8_t out_value;
    switch (control) {
        case PCL_OUT:
            out_value = (uint8_t) (mem.program_counter & PCL_MASK);
            break;
        case REGL_OUT:
            out_value = mem.scratch_pad[L];
    }

    mem.mem_low = out_value;
}

void T2_execute(uint8_t control) {
    uint8_t out_value;
    switch (control) {
        case PCH_OUT:
            out_value = (uint8_t) (mem.program_counter >> 8);
            break;
        case REGH_OUT:
            out_value = mem.scratch_pad[H];
    }

    mem.mem_high = out_value;
}

void T3_execute() {
}

void T4_execute() {
}

void T5_execute() {
}

DecodeControl decode_control;

int main() {
    decode_control = init_decode_control(decode_control);
    uint8_t current_cycle = decode_control.current_cycle;
	// Main program loop; each iteration of the loop is one processor state.
	T1_execute(decode_control.t1_control[current_cycle]);

    T2_execute(decode_control.t2_control[current_cycle]);

	exit(0);
}
