libBlinkStick
=============

A [blinkstick](http://www.blinkstick.com/) library in C with few dependencies.

## [API Documentation](http://ebenoist.github.io/libblinkstick/html/libblinkstick_8h.html)

## Requirements
- [hidapi](https://github.com/signal11/hidapi)
- [clang](https://clang.llvm.org/)
- [cmake](https://cmake.org/)

## Getting Started
- `cmake .` to generate the Makefiles for your system
- `make` to build the library and CLI tool

## The CLI tool
Mostly a proof of concept for the library, the blinkstick CLI allows you to turn on and off any number of connected devices, set their colors, or target specific LEDs.

After running make, you'll have a `blinkstick` binary in target/

```
$ blinkstick --help
USAGE:
  blinkstick [options...]
OPTIONS
  --color set the color using a three rgb values
  --count set the number of blinkstick devices to address
  --index which led should be set
  --debug turn on debug logging
```
