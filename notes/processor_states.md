# Processor States

-*Processor states*: take a fixed number of clock cycles except for WAIT and STOPPED which take 2n clock cycles.
	-T1I
	-T1
	-T2
	-WAIT
	-T3
	-STOPPED
	-T4
	-T5

-*Processor cycle*: includes variable number of processor states and thus clock cycles.

- I'm confused by the state diagram of our processor. (Page 50 8008UM.pdf). Maybe all these possible states are all just things that can happen within a single clock cycle?

- How are we going to "clock" our processor? What will the loop like in our main.c?