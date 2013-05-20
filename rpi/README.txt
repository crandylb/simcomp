README.txt -- For simcmp, the simple compiler, CRB, Sep 8, 2012
05/19/2013 CRB Revised for Raspberry Pi implementation.

Files in this directory

      README.txt	original
      simcmp.c		complete source code for simple compiler
      simcmp		executable compiled for x86_64 Linux
      simtst.txt	test file for simcmp
      simtst.out	expected output for simtst.txt
      rpi		subdirectory for Raspberry Pi
      	simcmp		  executable compiled for Raspberry Pi ARMv6
	README.txt	  this revised version of README for rpi

Installation

The simple compiler, called simcmp, is a limited macro processor used to
translate the machine independent Stage2 source code to a procedural language
such as Fortran or C, or even to an assembly language. Because simcmp is so
limited the translation may be somewhat crude and lack any optimization. Once
a running version of Stage2 is obtained it can be used to translate its source
code again with any number of optimizations to refine its performance.

Compiling and testing simcmp on RPi is exactly the same as for regular
Linux. Note that the executables for x86_64 and ARM are not processor
compatible.

Compile the simcmp.c program using:

	gcc simcmp.c -o simcmp

Verify that simcmp compiled without errors. Then use it run its test file:

        ./simcmp simtst.txt mysimtst.out

The first argument to simcmp is its input file and the second is the output
file. Be sure you do not name your output file simtst.out or you will
overwrite the expected output version. When you have verified your output file
exists, compare it to the expected version with:

	cmp mysimtst.out simtst.out

If the files are identical simcmp is working properly. If they are not
identical use diff to identify the differences. Some differences may be due to
different system architectures or environment and it may be that simcmp is
working correctly even with some differences.

	diff mysimtst.out simtst.out

What You Need

To compile and run simcmp you need an ANSI Standard C compiler such as gcc,
the Gnu C compiler and tools, or even Microsoft C, although that has not been
tested recently.

SIMCMP

The simcmp macro processor performs simple pattern matching of text strings to
macro templates and generates output from code body lines. The result is a
limited form of translation suitable for a bootstrap compiler to convert an
abstract program description to a target programming language. Details are
described in [1].

The simtst.txt file contains a set of macros and test input to verify that
simcmp is working properly. The output, simtst.out, is in the form of Fortran
statements. The translation of the input text to output strings demonstrates
the capabilities of simcmp.

What's Next

The purpose of simcmp is to produce a first working version of Stage2, the
general purpose macro processor which is the central component of the Mobile
Programming System. This next step requires a set of simcmp macros to
translate the Stage2 source code, and, of course, the Stage2 source
code. These two files will be supplied in the stage2 repository when it is
available.

References

 1. Waite, W. M., Implementing Software for Non-Numeric Applications,
 Prentice-Hall, New Jersey, 1973.

 2. Waite, W. M., The Mobile Programming System: STAGE2, CACM, 13 (July 1970),
 p. 415.
