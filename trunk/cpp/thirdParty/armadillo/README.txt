=== Contents ===

1. General Caveats
   1.1. Windows Specific Caveats
2. Installation
   2.1. Manual Installation
   2.2. Installation via CMake
   2.3. Support for Intel MKL
   2.4. Old versions of the ATLAS library
3. Example Programs and Linking
4. Reference Manual / User Documentation
5. Technical Documentation
6. Using Armadillo in Conjunction with IT++
7. License
8. Bug Reports
9. Credits



=== 1. General Caveats ===

While this library has gone through testing, not all possible
cases have been covered yet.  As such, its functionality may
not be 100% correct.  If you find a bug, either in the library
or the documentation, we are interested in hearing about it.

Armadillo makes extensive use of template metaprogramming,
recursive templates and template based function overloading.
As such, C++ compilers which do not fully implement the C++
standard may not work correctly.



=== 1.1. Windows Specific Caveats ===

The development and testing has so far been mainly done on UNIX-like 
platforms (Linux and Mac OS X), however there should be little or no 
platform specific code.  While rudimentary tests were done on a 
Windows machine, the developers are interested in hearing how well 
Armadillo works in more thorough tests.

If you're having trouble with the 'MS Visual C++ 2008 Express Edition'
compiler (due to its incomplete support for the C++ standard),
you may want to try the following alternative free compilers:

  - Intel's C++ compiler
    http://software.intel.com/en-us/intel-compilers/

  - GCC (part MinGW)
    http://www.mingw.org/

  - GCC (part of CygWin)
    http://www.cygwin.com/

If using Intel's C++ compiler, you'll need version 10.0 or better.
If using GCC, you'll need version 4.0 or better.



=== 2. Installation ===

If you have installed Armadillo using an RPM or DEB package,
you don't need to do anything else.  Otherwise read on.

There are two ways of installing Armadillo:
  (a) manual installation
  (b) via CMake

The functionality of Armadillo is partly dependent on other libraries,
which should be available on your system before installing Armadillo.
Armadillo can work without external libraries, but its functionality
will be reduced.

On a Linux system it is recommended that the following libraries are
present: LAPACK, BLAS, ATLAS and Boost.  LAPACK and BLAS are the most
important. If you have ATLAS and Boost, it's also necessary to have 
the corresponding header files installed.

NOTE: the minimum recommended version of ATLAS is 3.8.
See section 2.4 for more details.

On a Mac OS X system it's recommended that the Boost libraries are
present.  This includes the Boost header files.

For Windows systems, precompiled BLAS and LAPACK libraries can be
obtained from:  http://www.stanford.edu/~vkl/code/libs.html

See the "Example Programs" section for more info.



=== 2.1. Manual installation ===

Copy the entire "include" directory to a convenient location
and tell your compiler to use that location for header files
(in addition to the locations it uses already).
Alternatively, you can use the "include" directory directly.

You may also want to modify "include/armadillo_bits/config.hpp" 
to indicate which libraries are currently available on your system.
For example, if you have LAPACK present, uncomment the line
#define ARMA_USE_LAPACK

Note that to use the ATLAS and Boost libraries, their header files
also need to be present.



=== 2.2. Installation via CMake ===

"cmake" (version 2.6 or later) needs to be present on your system.
CMake can be downloaded from http://www.cmake.org

On major Linux systems (such as Fedora, Ubuntu, Debian, etc),
cmake is available as a pre-built package, though it may need
to be explicitly installed (using a tool such as PackageKit,
yum, rpm, apt, aptitude, etc).

If you have BLAS and/or LAPACK, install them before installing Armadillo
(under Mac OS X this is not necessary).

Under Linux or Mac OS X, open a shell with administrator privileges
(e.g. root), change into the directory that was created by unpacking
the armadillo archive, and type the following commands:

  cmake .
  make 
  make install

CMake will figure out what other libraries are currently installed
and will modify Armadillo's configuration correspondingly.

If you don't have administrator privileges, change
  make install
to
  make install DESTDIR=another_location

where "another_location" is a directory where you have write access.



=== 2.3. Support for Intel MKL ===

Armadillo can work with the Intel Math Kernel Library (MKL),
however there are several caveats.

MKL is actually a set of libraries, and they are typically installed
in a non-standard location. This can cause problems during linking.
Before installing Armadillo, the system should know where MKL libraries
are located (for example, "/opt/intel/mkl/10.2.2.025/lib/em64t/").
This can be achieved by setting the LD_LIBRARY_PATH environment variable,
or, for a more permanent solution, adding the location of MKL libraries
to "/etc/ld.so.conf".  It may also be possible to store a text file 
with the location in the "/etc/ld.so.conf.d" directory.  In the latter
two cases you will need to run "ldconfig" afterwards.

MKL version 10.2.2.025 is known to have issues with SELinux,
which is turned on by default in Fedora.  The problem appears
to be in MKL, not SELinux.

If you want to enable support for MKL within Armadillo,
uncomment the line with "INCLUDE(ARMA_FindMKL)" in the 
"CMakeLists.txt" file and run the CMake based installation.



=== 2.4. Old versions of the ATLAS library ===

Old versions of the ATLAS library (e.g. 3.6) can produce incorrect
results as well as corrupting memory, leading to random crashes.

The minimum recommended version is 3.8.  Users of Ubuntu and
Debian based systems should explicitly check that version 3.6
is not installed.



=== 3. Example Programs and Linking ===

The "examples" directory contains several quick example programs 
that use the Armadillo library. Please see "examples/Makefile", 
which may may need to be configured for your system.

If Armadillo header files were installed in a non-standard location,
you will need to modify "examples/Makefile" to tell tell the compiler
where they are.

If Armadillo was installed manually, you will also need to explicitly 
link your programs with the libraries that were specified in
"include/armadillo_bits/config.hpp".  If you specified that LAPACK and
BLAS are available, instead of using "-larmadillo", use the following:
 - under Linux, use "-llapack -lblas"
 - under Mac OS X, use "-framework Accelerate"
 - under the Sun Studio compiler, try "-library=sunperf"

"example1.cpp" doesn't need any external libraries.
"example2.cpp" requires the LAPACK library or its equivalent
(e.g. the Accelerate framework on Mac OS X).  You may get errors
at compile or run time if LAPACK functions are not available.

NOTE: on Ubuntu and Debian based systems you may need to add 
"-lgfortran" to the compiler flags.



=== 4. User Documentation / Reference Manual ===

A quick reference manual is available at http://arma.sourceforge.net
or in the "docs_user" directory.  Use a web browser to open the 
"docs_user/index.html" file.  The documentation explains the classes
and functions, with snippets of example code. 



=== 5. Technical Documentation ===

The technical documentation (produced with the aid of Doxygen) is
available in the "docs_tech" directory.  Use a web browser to open
the "docs_tech/index.html" file.

The technical documentation helps in understanding the internals 
of Armadillo.



=== 6. Using Armadillo in Conjunction with IT++ ===

If you wish to use the IT++ library in conjunction with Armadillo,
use #include "armadillo_itpp" instead of #include "armadillo"
in your code.  See also the "examples/example_itpp.cpp" file.



=== 7. License ===

Please see the "LICENSE.txt" file.



=== 8. Bug Reports ===

If you find a bug, either in the library or the documentation,
we are interested in hearing about it.  Please send a report to:
Conrad Sanderson <conradsand at ieee dot org>



=== 9. Credits ===

Main developers:
- Conrad Sanderson, http://www.itee.uq.edu.au/~conrad/
- Ian Cullinan
- Dimitrios Bouzas

Contributors:
- Eric R. Anderson
- Benoît Bayol
- Salim Bcoin
- Justin Bedo
- Darius Braziunas
- Ted Campbell
- Chris Davey
- Charles Gretton
- Edmund Highcock
- Kshitij Kulshreshtha
- Oka Kurniawan
- David Lawrence
- Carlos Mendes
- Artem Novikov
- Martin Orlob
- Ken Panici
- Adam Piątyszek
- Vikas Reddy
- Ola Rinta-Koski
- Laurianne Sitbon
- Paul Torfs
- Yong Kang Wong


