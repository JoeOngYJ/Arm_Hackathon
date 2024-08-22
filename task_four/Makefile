.phony: execute_fsm, clean

fsm:
	iverilog -o fsm fsm.v

execute_fsm: fsm
	vvp fsm

clean:
	rm -f fsm
