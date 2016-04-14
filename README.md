# Thoth

An operating system inspired by the Unix philosophy and design.

## Objectives

The project has the following objectives...

- To create a lightweight multi-platform monolithic kernel
- To create a user-space environment for guest programs
- To create a user-space interface to the OS inspired by Unix/POSIX
- To create a robust set of drivers for commonly used hardware

## Why?

This operating system is not designed for real-world use. It exists only as a way through which I may become more familiar with OS development.

## Getting a copy

## Building

Thoth uses the 'tup' build system. Make sure you install tup before attempting to build the project.

Navigate to the top-level directory of Thoth and run the following commands:

```
mkdir build-default
cp tup.config build-default/tup.config
```

*NOTE: If you wish to build for a target architecture other than x86_64, edit the file 
`build-default/tup.config` accordingly*

Build Thoth by running the following command:

`
tup build-default
`

## Running

## Credits

- A lot of people on IRC, most notably 'sortie' on #osdev (irc.freenode.net)