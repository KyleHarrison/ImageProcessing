KYLE HARRISON
HRRKYL008
Assignment 4 Image Processing:

The following files are present in my submittion:

	catch.hpp:	Default file used to run unit tests
	Image.cpp:	The class associated with an image detailing its width, height, and operations
	Image.h:	The header file detailing its corresponding .cpp
	main.cpp:	The driver file containing main used to run
	testdriver.cpp	The driver file used for running unit tests

	*.pgm		Default image files used for testing

To make the application do the following:
	make
	make unittest

To run the application the following commands are avaliable:
	-a I1.pgm I2.pgm output.pgm (add I1 and I2)
	-s I1.pgm I2.pgm output.pgm (subtract I2 from I1)
	-i I1.pgm output.pgm (invert I1)
	-l I1.pgm I2.pgm output.pgm (mask I1 with I2)
	-t I1.pgm f output.pgm (threshold I1 with integer value f)
	Image names must be specified with their extensions.

To run default values the following run commands are avaliable:
	run+
	run-
	run!
	run/
	run*

To run the unit tests use the following command:
	make runtest
