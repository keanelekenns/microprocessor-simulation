#include "main.h"
#include "memory.h"
#include "decode.h"
#include "devices.h"
#include "ALU.h"

#define PCL_MASK 0xFF
#define L 5
#define H 6

DecodeControl control;

void T1_execute(uint8_t t1_control) {
    uint8_t out_value;
    switch (t1_control) {
        case PCL_OUT:
            out_value = (uint8_t) (mem.address_stack[0] & PCL_MASK);
            break;
        case REGL_OUT:
            out_value = mem.scratch_pad[L];
    }

    mem.mem_low = out_value;
}

void T2_execute(uint8_t t2_control) {
    uint8_t out_value;
    switch (t2_control) {
        case PCH_OUT:
            out_value = (uint8_t) (mem.address_stack[0] >> 8);
            break;
        case REGH_OUT:
            out_value = mem.scratch_pad[H];
    }

    mem.mem_high = out_value;
}

void T3_execute(uint8_t t3_control) {
    uint8_t data_from_memory;
    uint16_t address = mem.mem_low + (mem.mem_high << 8);
    switch (t3_control) {
        case FETCH:
            data_from_memory = mem.memory[address];
            mem.reg_b = data_from_memory;
            mem.instruction_reg = data_from_memory;

            init_decode_control(control);
            control = decode(control, data_from_memory);
            mem.address_stack[mem.program_counter] += 1;
            break;
        case FETCH_HALT:
            data_from_memory = mem.memory[address];
            exit(0); // Halt used as end program
            break;
        case REGB_TO_OUT:
            mem.memory[address] = mem.reg_b;
            break;
        case DATA_TO_REGB:
            mem.reg_b = mem.memory[address];
            break;
        case LOW_ADDR_TO_REGB:
            mem.reg_b = mem.memory[address];
            break;
        case HIGH_ADDR_TO_REGA:
            mem.reg_a = mem.memory[address];
            break;
        case HIGH_ADDR_TO_REGA_COND:
            mem.reg_a = mem.memory[address];
            break;
    }
}

void T4_execute(uint8_t t4_control) {
    switch (t4_control) {
        case SSS_TO_REGB:
            mem.reg_b = mem.scratch_pad[control.source_register];
            break;
        case REG_A_TO_PCH:
            // Clear PCH then copy value from reg a to PCH
            mem.address_stack[0] = mem.address_stack[0] & PCL_MASK;
            mem.address_stack[0] += ((uint16_t) mem.reg_a) << 8;
            break;
    }
}

void T5_execute(uint8_t t5_control) {
    uint16_t memory_address;
    switch (t5_control) {
        case REGB_TO_DDD:
            mem.scratch_pad[control.destination_register] = mem.reg_b;
            break;
        case ALU_OP:
            execute_alu_operation();
            break;
        case REGB_TO_PCL:
            // Clear low bits
            memory_address = mem.address_stack[0] & 0xFF00;
            // Copy value of reg_b to PCL
            memory_address += (uint16_t) mem.reg_b;
            mem.address_stack[0] = memory_address;
            break;
    }
}

void execute_alu_operation() {
    uint8_t result;
    switch (control.alu_operation) {
        case ADD_OP:
            // Value to add to accumulator is already in reg_b
            result = ADD(mem.scratch_pad[0], mem.reg_b);
            // Store result in accumulator
            mem.scratch_pad[0] = result;
            break;
        case ADD_C:
            // Value to add to accumulator is already in reg_b
            result = ADD_with_carry(mem.scratch_pad[0], mem.reg_b);
            // Store result in accumulator
            mem.scratch_pad[0] = result;
            break;
        case SUB_OP:
            // Value to subtract from accumulator is already in reg_b
            result = SUBTRACT(mem.scratch_pad[0], mem.reg_b);
            // Store result in accumulator
            mem.scratch_pad[0] = result;
            break;
        case SUB_B:
            // Value to subtract from accumulator is already in reg_b
            result = SUBTRACT_with_borrow(mem.scratch_pad[0], mem.reg_b);
            // Store result in accumulator
            mem.scratch_pad[0] = result;
            break;
        case L_AND:
            AND(mem.scratch_pad[0], mem.reg_b);
            break;
        case L_XOR:
            EXCLUSIVE_OR(mem.scratch_pad[0], mem.reg_b);
            break;
        case L_OR:
            OR(mem.scratch_pad[0], mem.reg_b);
            break;
        case CMP:
            COMPARE(mem.scratch_pad[0], mem.reg_b);
            break;
        case INC:
            mem.scratch_pad[control.source_register] = INCREMENT(mem.reg_b);
            break;
        case DEC:
            mem.scratch_pad[control.source_register] = DECREMENT(mem.reg_b);
            break;
        case RLC_OP:
            result = RLC(mem.scratch_pad[0]);
            mem.scratch_pad[0] = result;
            break;
        case RRC_OP:
            result = RRC(mem.scratch_pad[0]);
            mem.scratch_pad[0] = result;
            break;
        case RAL_OP:
            result = RAL(mem.scratch_pad[0]);
            mem.scratch_pad[0] = result;
            break;
        case RAR_OP:
            result = RAR(mem.scratch_pad[0]);
            mem.scratch_pad[0] = result;
            break;
    }
}

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
