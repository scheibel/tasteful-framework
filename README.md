Tasteful Framework
============

Tasteful Framework is web framework library written in C++ based on Tasteful Server.
It provides an MVC-architecture with routes, controllers, models and views as well as a datamapper as an object-relational mapper.

An example application is a simple blog in [/examples/blog/](https://github.com/scheibel/tasteful-framework/tree/master/examples/blog).

As it is now, only Linux is tested as development and deployment environment, so no build information for Windows, MacOS or any other OS is provided.
Since all platform-dependent features of the Tasteful Framework are provided through Qt, it should also run on any other OS to which Qt was ported.

Content
------------

 * [Requirements](#requirements)
 * [Building Tasteful Framework](#building-tasteful-framework)
 * [Installation](#installation)
 * [License](#license)

Requirements
---------------------

 * [Qt 4.8](http://qt.nokia.com/)
 * [gcc 4.6](http://gcc.gnu.org/)
 * [CMake 2.6](http://www.cmake.org/)
 * [Tasteful Server](https://github.com/scheibel/tasteful-server)

Building Tasteful Framework
------------------------------------------

    > mkdir build && cd build
    > cmake ..
    > make

Installation
----------------

The Tasteful Framework library and its header files can be installed in your system using the following command:

    > sudo make install

License
-----------

Tasteful Framework is licensed under the LPGL-3.
