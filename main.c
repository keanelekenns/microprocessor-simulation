#include "main.h"
#include "memory.h"
#include "decode.h"
#include "devices.h"
#include "execute.h"
#include "ALU.h"
#include "print_contents.h"
#include "file_reader.h"

uint32_t number_tstates_executed = 0;
DecodeControl control;
DecodeControl control_swap;
DecodeControl control_save;

uint8_t swap_reg;
uint8_t reg_a_save;
uint8_t reg_b_save;
uint8_t instruction_reg_save;



int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Wrong number of arguments WANT 1 <testprogramfilename.asm>\n");
        exit(1);
    }


//    printf("Printing initial memory contents.\n");
//    print_all_contents();

    read_file(argv[1]);
    printf("Loading test program into memory.\n");
//    print_all_contents();
    getchar();

    // Counter to let us track which instruction we're execution
    int instruction_count = 1;
    int halt_called = 0;
    int halt_check;
    int continue_main = 0;

    control = init_decode_control(control);
    control_swap = init_decode_control(control);
    control_save = init_decode_control(control);
    // Loop until program execution halts

    for (;;) {
        //STAGE 1 - control IF/ID
        T1_execute(control.t1_control[control.current_cycle]);
        T2_execute(control.t2_control[control.current_cycle]);
        T3_execute(control.t3_control[control.current_cycle]);
        //save registers
        reg_a_save = mem.reg_a;
        reg_b_save = mem.reg_b;
        instruction_reg_save = mem.instruction_reg;
        //move program counter to next instruction
        mem.address_stack[0] += control.byte_size - 1;

        //save control
        control_swap = control;
        control = control_save;
        control_save = control_swap;

        printf("STAGE - 1 -\n");
        print_program_counter();
        print_scratch_pad();
        print_control_bits();
        print_memory();
        getchar();

        //STAGE 2 - control IF/ID
        halt_check = mem.memory[mem.mem_low + (mem.mem_high << 8)];
        if(halt_check == 0xFF || (halt_check & 0xFE) == 0) {
            halt_called = 1;
            mem.address_stack[0] += 1;
        } else {
            T1_execute(control.t1_control[control.current_cycle]);
            T2_execute(control.t2_control[control.current_cycle]);
            T3_execute(control.t3_control[control.current_cycle]);
        }
        //restore registers for control registers and save registers for control
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



        //save control
        control_swap = control;
        control = control_save;
        control_save = control_swap;

        mem.address_stack[0] -= control.byte_size;

        printf("STAGE - 2 -\n");
        print_program_counter();
        print_scratch_pad();
        print_control_bits();
        print_memory();
        getchar();

        //STAGE 3 - control EX
        T4_execute(control.t4_control[control.current_cycle]);
        T5_execute(control.t5_control[control.current_cycle]);
        control.current_cycle++;
        //execute up to 2 more cycles of control instruction
        for(;control.current_cycle < control.cycle_length; control.current_cycle++) {
            //TODO add conditional jumps

            T1_execute(control.t1_control[control.current_cycle]);
            T2_execute(control.t2_control[control.current_cycle]);
            T3_execute(control.t3_control[control.current_cycle]);
            if(control.t3_control[current_cycle] == HIGH_ADDR_TO_REGA_COND) {
                if (control.jump_test && !(get_flip_flops() & control.condition)) {
                    break;
                }
                if (!control.jump_test && (get_flip_flops() & control.condition)) {
                    break;
                }
                continue_main = 1;

            }

            T4_execute(control.t4_control[control.current_cycle]);
            T5_execute(control.t5_control[control.current_cycle]);
        }
        if(continue_main == 1) {
            continue_main = 0;
            control = init_decode_control(control);
            control_swap = init_decode_control(control);
            control_save = init_decode_control(control);
            continue;
        }

        //move program counter back to where IF/ID for control left it
        mem.address_stack[0]++;
        printf("Finished instruction %d. System state:\n", instruction_count);
        printf("STAGE - 3 -\n");
        print_program_counter();
        print_scratch_pad();
        print_control_bits();
        print_memory();
        instruction_count++;
        getchar();


        //Does not execute control instruction if any of the three jmp instructions
        if((control.cycle_length == 3 && control.t3_control[1] != DATA_TO_REGB) ||(control.alu_operation == CMP)) {
            mem.address_stack[0]--;
            control = init_decode_control(control);
            control_swap = init_decode_control(control);
            control_save = init_decode_control(control);
            continue;
        }

        //restore control registers
        mem.reg_a = reg_a_save;
        mem.reg_b = reg_b_save;
        mem.instruction_reg = instruction_reg_save;

        control = control_save;

        //STAGE 4 - control EX
        T4_execute(control.t4_control[control.current_cycle]);
        T5_execute(control.t5_control[control.current_cycle]);
        control.current_cycle++;
        //execute up to 2 more cycles of control instruction
        for(;control.current_cycle < control.cycle_length; control.current_cycle++) {
            //TODO add conditional jumps
            T1_execute(control.t1_control[control.current_cycle]);
            T2_execute(control.t2_control[control.current_cycle]);
            T3_execute(control.t3_control[control.current_cycle]);
            if (control.t3_control[current_cycle] == HIGH_ADDR_TO_REGA_COND) {
                if(control.jump_test && !(get_flip_flops() & control.condition)) {

                }
            }

            T4_execute(control.t4_control[control.current_cycle]);
            T5_execute(control.t5_control[control.current_cycle]);
        }
        printf("Finished instruction %d. System state:\n", instruction_count);
        printf("STAGE - 4 -\n");
        print_program_counter();
        print_scratch_pad();
        print_control_bits();
        print_memory();
        instruction_count++;
        getchar();


        if(halt_called == 1)  {
            printf("halt called\n");
            exit(0);
        }
        //Stages done so repeat
        control = init_decode_control(control);
        control_swap = init_decode_control(control);
        control_save = init_decode_control(control);

    }
	exit(0);
}
control.jump_test && !(get_flip_flops() & control.condition)
