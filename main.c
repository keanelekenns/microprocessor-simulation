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
    
	// Check if machine code file specified on command line
    if (argc == 2){
      printf("Printing initial memory contents.\n");
      print_all_contents();
      if(read_file(argv[1]) == -1){
		  //failed to read file
		  exit(1);
	  }
    } else {
      fprintf(stderr, "Usage: ./main <machine_code_file>\n");
      exit(1);
    }
    printf("Loading test program into memory.\n");
    print_all_contents();

    // Counter to let us track which instruction we're executing
    int instruction_count = 1;
    int take_jump = 0;
    int execution_cycles = 0;

    control = init_decode_control(control);
    control_swap = init_decode_control(control);
    control_save = init_decode_control(control);
    // Loop until program execution halts

    for (;;) {
        //STAGE 1 - control IF/ID
        T1_execute(control.t1_control[control.current_cycle]);
        T2_execute(control.t2_control[control.current_cycle]);
        T3_execute(control.t3_control[control.current_cycle]);

        execution_cycles++;

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

        printf("Finished IF/ID of instruction %d. System state:\n", instruction_count);
		print_all_contents();
		printf("Press enter to continue.\n");
		getchar();

        //STAGE 2 - control IF/ID
		T1_execute(control.t1_control[control.current_cycle]);
        T2_execute(control.t2_control[control.current_cycle]);
        T3_execute(control.t3_control[control.current_cycle]);
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
        control_save = init_decode_control(control_save);
        control_save = control_swap;
		
		//set program counter to point to value(s) needed by the EX/WB stage of previous instruction
        mem.address_stack[0] -= control.byte_size;

        printf("Finished IF/ID of instruction %d. System state:\n", instruction_count+1);
		print_all_contents();
		printf("Press enter to continue.\n");
		getchar();

        //STAGE 3 - control EX
        T4_execute(control.t4_control[control.current_cycle]);
        T5_execute(control.t5_control[control.current_cycle]);
        control.current_cycle++;
        //execute up to 2 more cycles of control instruction
        for(;control.current_cycle < control.cycle_length; control.current_cycle++) {
            T1_execute(control.t1_control[control.current_cycle]);
            T2_execute(control.t2_control[control.current_cycle]);
            T3_execute(control.t3_control[control.current_cycle]);
			//check if this is a conditional jump on its third cycle
            if(control.t3_control[control.current_cycle] == HIGH_ADDR_TO_REGA_COND) {
				// Check for JTc
				if (control.jump_test && !(get_flip_flops() & control.condition)) {
					// Reset control and skip T4/T5
					control = init_decode_control(control);
					//we do not want to take the jump, so skip T4/T5 and continue normally
					break;
				}
				// Check for JFc
				if (!control.jump_test && (get_flip_flops() & control.condition)) {
					// Reset control and skip T4/T5
					control = init_decode_control(control);
					//we do not want to take the jump, so skip T4/T5 and continue normally
					break;
				}
				//this indicates we want to take the jump,
				//so we must scrap the next instruction to be executed (stall on branch)
                take_jump = 1;
            }else if(control.t3_control[control.current_cycle] == HIGH_ADDR_TO_REGA) {//check if this is an unconditional jump
				take_jump = 1;
			}
			//These load the program counter with the jump address if this is cycle three of a jump instruction
            T4_execute(control.t4_control[control.current_cycle]);
            T5_execute(control.t5_control[control.current_cycle]);
        }
		printf("Finished EX/WB of instruction %d. System state:\n", instruction_count);
		print_all_contents();
		instruction_count++;
		printf("Press enter to continue.\n");
		getchar();

		execution_cycles++;
		printf("")
        if(take_jump == 1) {//jump is taken so skip over next instruction's execution
            take_jump = 0;
            control = init_decode_control(control);
            control_swap = init_decode_control(control);
            control_save = init_decode_control(control);
            continue;
        }

        //move program counter past instruction opcode that has already been fetched
        mem.address_stack[0]++;

        //restore control registers
        mem.reg_a = reg_a_save;
        mem.reg_b = reg_b_save;
        mem.instruction_reg = instruction_reg_save;


        control = init_decode_control(control);
        control = control_save;

        //STAGE 4 - control EX
        T4_execute(control.t4_control[control.current_cycle]);
        T5_execute(control.t5_control[control.current_cycle]);
        control.current_cycle++;
        //execute up to 2 more cycles of control instruction
        for(;control.current_cycle < control.cycle_length; control.current_cycle++) {
            T1_execute(control.t1_control[control.current_cycle]);
            T2_execute(control.t2_control[control.current_cycle]);
            T3_execute(control.t3_control[control.current_cycle]);
			//check if this is a conditional jump on its third cycle
            if(control.t3_control[control.current_cycle] == HIGH_ADDR_TO_REGA_COND) {
				// Check for JTc
				if (control.jump_test && !(get_flip_flops() & control.condition)) {
					// Reset control and skip T4/T5
					control = init_decode_control(control);
					//we do not want to take the jump, so skip T4/T5 and continue normally
					break;
				}
				// Check for JFc
				if (!control.jump_test && (get_flip_flops() & control.condition)) {
					// Reset control and skip T4/T5
					control = init_decode_control(control);
					//we do not want to take the jump, so skip T4/T5 and continue normally
					break;
				}
            }
			//These load the program counter with the jump address if this is cycle three of a jump instruction
            T4_execute(control.t4_control[control.current_cycle]);
            T5_execute(control.t5_control[control.current_cycle]);
        }
		printf("Finished EX/WB of instruction %d. System state:\n", instruction_count);
		print_all_contents();
		instruction_count++;
		printf("Press enter to continue.\n");
		getchar();
		
        //Stages done so repeat
        control = init_decode_control(control);
        control_swap = init_decode_control(control);
        control_save = init_decode_control(control);

    }
	exit(0);
}

