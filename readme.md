# Scal
stands for Simplisitic Character Algorithim Langauge if you really care

This is a highly simplistic langauge based on BrainF**k

### Commands:
- '>' - Increment the pointer
- '<' - Decrement the pointer
- '+' - Increment the register
- '-' - Decrement the register
- '.' - Load the pointed number into the register
- ',' - Set the pointed number to the number in the register
- ';' - Display the register
- ':' - Get input to the register
- '*' - Set the register to the pointer
- '&' - Set the pointer to the register
- '[]' - Loop back to '[' unless the number pointed to is 0
- '#' - Wait for the duration pointed to
- '0' - Reset the register
- '!' - Exit the program

### Usage:
```
scal <filename>
```
Run the specified scal file<br>
```
scal -b <filename>
```
Compile the specified scal file into an executable binary
```
scal -d <filename>
```
Compile the specified scal file into a hexidecimal file
```
scal -c <filename>
```
Compile the specified scal file into a C file