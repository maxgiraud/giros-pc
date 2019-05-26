# GirOS PC

Simulation and conception of an 8 bit programmable computer featuring :
* 256 instruction max
* 8-bit ALU capable of adding and substracting
* 8-bit bus
* 5 8-bit registers
* 64 kB of ram


## Simulation

A working simulation made with logisim can be found in this project just launch simu.circ with logisim.
Populate RAM memory with a program (for example compiler/hello_world.bin) and run.

![alt text](https://github.com/maxgiraud/giros-pc/blob/master/simu/screenshot_simu.png)

## Conception

This project will be for the moment realised on breadboards, at this time the clock module, 2 registers, the ALU and the output register controlling 7-segments displays have been made.


### Decoder

The instruction decoder is made with EEPROM
* input : 8 bit instruction , 2 bit flags (ZF and CF) , 3 bit for machine cycle
* output : 23 control signals

decrom_gen will output the EEPROM decoder content.
Each instruction drives the control signals during 8 machine cycles.

### Compiler

The compiler will transcript the "gin" code (custom poor assembly-like programmation language) to binary code that will be decoded by the EEPROM instruction decoder

2 simple examples of compiled gin codes are available in the compiler folder : hello_world.bin and inc.gin
These can be executed in the logisim simulation, for this to work just populate ram memory with compiled gin program.

Usage :
```sh
$ ./g2b code.gin > code.bin
```
## Note

This is a work in progresse you'll see more to come and my project may change/improve with time !
Coming soon :
* Documentation on the gin programming language
* Schematics
* Pictures/videos of the computer in action
