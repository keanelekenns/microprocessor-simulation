#include "memory.h"
#include "decode.h"
#include "devices.h"
#include "ALU.h"
#include "execute.h"
#include <stdio.h>

#define H 6
#define L 7

DecodeControl control = {0};

// Reset memory, registers, address pointer, etc
void reset_memory() {
    for (int i = 0; i < 16384; mem.memory[i] = 0, i++);
    for (int i = 0; i < 7; mem.scratch_pad[i] = 0, i++);
    for (int i = 0; i < 8; mem.address_stack[i] = 0, i++);

    mem.program_counter = 0;
    mem.mem_low = 0;
    mem.mem_high = 0;
    mem.reg_a = 0;
    mem.reg_b = 0;
    mem.flip_flops = 0;
    mem.instruction_reg = 0;
}

void test_t1_execute() {
    // Test PCL_OUT
    puts("Testing T1_execute().");
    control = init_decode_control(control);
    reset_memory();

    // Set current instruction to index 5 in memory
    mem.address_stack[0] = 5;

    // Execute T1 to get low byte of instruction address
    T1_execute(control.t1_control[0]);
    if (mem.mem_low != 5) {
        puts("PCL_OUT test failed.");
        exit(0);
    }

    // Test REGL_OUT
    // Set control signal and provide test value for register H
    control.t1_control[0] = REGL_OUT;
    mem.scratch_pad[L] = 17;
    // Execute T1 to get byte from register H
    T1_execute(control.t1_control[0]);
    if (mem.mem_low != 17) {
        puts("REGL_OUT test failed.");
        exit(0);
    }
    puts("All T1_execute() tests passed.");
}

int main () {
    test_t1_execute();
    return 0;
}
