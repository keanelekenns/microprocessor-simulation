#include "main.h"
#include "memory.h"
#include "decode.h"
#include "devices.h"
#include "execute.h"
#include "ALU.h"
#include "print_contents.h"
#include "file_reader.h"

uint32_t number_tstates_executed = 0;
DecodeControl control_1;
DecodeControl control_2;

uint8_t swap_reg;
uint8_t reg_a_save;
uint8_t reg_b_save;
uint8_t instruction_reg_save;

int main() {

    printf("Printing initial memory contents.\n");
    print_all_contents();


    read_file("test_programs/single_instruction.asm");
    printf("Loading test program into memory.\n");
    print_all_contents();

    // Counter to let us track which instruction we're execution
    int instruction_count = 1;

    control_1 = init_decode_control(control_1);
    control_2 = init_decode_control(control_2);
    // Loop until program execution halts

    for (;;) {
        //STAGE 1 - control_1 IF/ID
        T1_execute(control_1.t1_control[control_1.current_cycle], control_1);
        T2_execute(control_1.t2_control[control_1.current_cycle], control_1);
        T3_execute(control_1.t3_control[control_1.current_cycle], control_1);
        //save registers
        reg_a_save = mem.reg_a;
        reg_b_save = mem.reg_b;
        instruction_reg_save = mem.instruction_reg;
        //move program counter to next instruction
        mem.program_counter += control_1.byte_size - 1;

        //STAGE 2 - control_2 IF/ID
        T1_execute(control_2.t1_control[control_2.current_cycle], control_2);
        T2_execute(control_2.t2_control[control_2.current_cycle], control_2);
        T3_execute(control_2.t3_control[control_2.current_cycle], control_2);
        //restore registers for control_1 registers and save registers for control_2
        swap_reg = mem.reg_a;
        mem.reg_a = reg_a_save;
        reg_a_save = swap_reg;

        swap_reg = mem.reg_b;
        mem.reg_b = reg_b_save;
        reg_b_save = swap_reg;

        swap_reg = mem.instruction_reg;
        mem.instruction_reg = instruction_reg_save;
        instruction_reg_save = swap_reg;
        //move program counter back to last instruction
        mem.program_counter -= control_1.byte_size;
        //STAGE 3 - control_1 EX
        T4_execute(control_1.t4_control[control_1.current_cycle], control_1);
        T5_execute(control_1.t5_control[control_1.current_cycle], control_1);
        control_1.current_cycle++;
        //execute up to 2 more cycles of control_1 instruction
        for(;control_1.current_cycle < control_1.cycle_length; control_1.current_cycle++) {
            T1_execute(control_1.t1_control[control_1.current_cycle], control_1);
            T2_execute(control_1.t2_control[control_1.current_cycle], control_1);
            T3_execute(control_1.t3_control[control_1.current_cycle], control_1);
            T4_execute(control_1.t4_control[control_1.current_cycle], control_1);
            T5_execute(control_1.t5_control[control_1.current_cycle], control_1);
        }
        printf("Finished instruction %d. System state:\n", instruction_count);
        print_all_contents();
        instruction_count++;
        getchar();



        //Does not execute control_2 instruction if any of the three jmp instructions
        if(control_1.cycle_length == 3 && control_1.t3_control[1] != DATA_TO_REGB) {
            control_1 = init_decode_control(control_1);
            control_2 = init_decode_control(control_2);
            continue;
        }

        //restore control_2 registers
        mem.reg_a = reg_a_save;
        mem.reg_b = reg_b_save;
        mem.instruction_reg = instruction_reg_save;

        //move program counter back to where IF/ID for control_2 left it
        mem.program_counter++;

        //STAGE 4 - control_2 EX
        T4_execute(control_2.t4_control[control_2.current_cycle], control_2);
        T5_execute(control_2.t5_control[control_2.current_cycle], control_2);
        control_2.current_cycle++;
        //execute up to 2 more cycles of control_1 instruction
        for(;control_2.current_cycle < control_2.cycle_length; control_2.current_cycle++) {
            T1_execute(control_2.t1_control[control_2.current_cycle], control_2);
            T2_execute(control_2.t2_control[control_2.current_cycle], control_2);
            T3_execute(control_2.t3_control[control_2.current_cycle], control_2);
            T4_execute(control_2.t4_control[control_2.current_cycle], control_2);
            T5_execute(control_2.t5_control[control_2.current_cycle], control_2);
        }
        printf("Finished instruction %d. System state:\n", instruction_count);
        print_all_contents();
        instruction_count++;
        getchar();


        //Stages done so repeat
        control_1 = init_decode_control(control_1);
        control_2 = init_decode_control(control_2);

    }
	exit(0);
}

