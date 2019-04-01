#include "main.h"
#include "memory.h"
#include "decode.h"
#include "devices.h"
#include "execute.h"
#include "ALU.h"

DecodeControl control;
uint32_t number_tstates_executed = 0;

int main() {
    control = init_decode_control(control);
    uint8_t current_cycle = control.current_cycle;
    // Loop until program execution halts
    for (;;) {
    	T1_execute(control.t1_control[current_cycle]);

    	T2_execute(control.t2_control[current_cycle]);

        T3_execute(control.t3_control[current_cycle]);
        // Conditional jump check
        if (*(control.t3_control) == HIGH_ADDR_TO_REGA_COND && (get_flip_flops() & control.condition)) {
            // Reset control and skip T4/T5
            control = init_decode_control(control);
            continue;
        }

        T4_execute(control.t4_control[current_cycle]);

        T5_execute(control.t5_control[current_cycle]);

        control.current_cycle++;
        // Instruction complete
        if (control.current_cycle == control.cycle_length) {
            control = init_decode_control(control);
        }
    }

	exit(0);
}
