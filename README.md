ViC
===

Short name, long story. Small footprint, big goals.

In memory of [VIC-20](https://en.wikipedia.org/wiki/Commodore_VIC-20) and
others who inspired us.

# How to use it?

ViC is primarily intended to be a shell running on an Arduino board, which could
help debug and test Arduino sketches. Furthermore, it can be also built as a 
POSIX-type shell on your Unix-based box and so here is how it works:

## PC

1. In the directory of this repository (that you've downloaded) run command
   `make shell`
2. After a succesful build, you can start the shell by `./vic`. Kill it by pressing
   Ctrl+C
3. (Yes, we know that the funcionality is really poor)

## Arduino

1. Move the whole directory to your Arduino libraries folder
   ([where is it?](https://www.arduino.cc/en/guide/libraries)
2. Open the Arduino IDE and try the *vic_basic* example. It contains all functions
   you'll need. We hope the interface is kind of straightforward. If not,
   looking at source files may help. 

## Commands

ViC by default listens to these command:
* ls - list all commands
* lsv - list all variables
* set {name} {value} - set value to variable
* get {name} - returns value of variable
