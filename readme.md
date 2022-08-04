# Scal
stands for Simplisitic Character Algorithim Langauge if you really care

This is a highly simplistic langauge based on BrainF**k

### Commands:

**+(num)**<br>
Add a number to the register

**-(num)**<br> 
Subtract a number from the register

**.(mem)**<br>
Set a value in memory to the register

**,(mem)**<br> 
Set the register to a value in memory

**=(num)**<br>
Set the register to a number

**<(num)**<br>
Go back (num) lines unless register is 0

**>(num)**<br>
Go forwards (num) lines unless register is 0

**;(mem)**<br>
Print value at memory

**!(num)**<br>
Trigger interupt

### Commands (Compiler)

**;\***<br>
Print the register

**<\***<br>
Go back by the number in register

'\*' is a constant for memory 0, the register is stored in memory 0

### Interupts

**!000**<br>
Interupts act as different events that do things according to what the machine or compiler has set up. 000 is globally to end the program.

### Usage
```
scal <filename>
```
Run the specified scal file<br>