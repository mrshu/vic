ViC
===

Short name, long story. Small footprint, big goals.

In memory of [VIC-20](https://en.wikipedia.org/wiki/Commodore_VIC-20) and
others who inspired us.

# How to use it?

ViC is primarily intended to be shell running in Arduino, which could help
debuging ang testing Arduino sketches. Although, it can be also built as shell
in your PC (with Linux system installed) and so here is how it works:

## PC

1. In directory of this repository (that you've downloaded) run command
   `make shell`
2. After succesful built, you can start shell by `./vic`. Kill by Ctrl+C
3. (Yes, we know that the funcionality is really poor)

## Arduino

1. Move whole directory to your Arduino libraries folder
   ([where is it?](https://www.arduino.cc/en/guide/libraries)
2. Open Arduino IDE and try example *vic_basic*. It contains all functions
   you'll need. We hope the interface is kind of straightforward, if not,
   I worry you have to look to source files. 

## Commands

ViC listens to these command:
* ls - list all commands
* lsv - list all variables
* set {name} {value} - set value to variable
* get {name} - returns value of variable
