Tasteful Framework
============

Tasteful Framework is web framework library written in C++ based on Tasteful Server.
It provides an MVC-architecture with routes, controllers, models and views as well as a datamapper and an activerecord as an object-relational mappers.

An example application is a simple blog in [/examples/blog/](https://github.com/scheibel/tasteful-framework/tree/master/examples/blog).

As it is now, only Linux is tested as development and deployment environment, so no build information for Windows, MacOS or any other OS is provided.
Since all platform-dependent features of the Tasteful Framework are provided through Qt, it should also run on any other OS to which Qt was ported.

Content
------------

 * [Requirements](#requirements)
 * [Building Tasteful Framework](#building-tasteful-framework)
 * [Installation](#installation)
 * [Example Blog](#example-blog)
 * [Webapplication Configuration Format](#webapplication-configuration-format)
 * [License](#license)

Requirements
---------------------

 * [Qt 5.0](http://qt.nokia.com/)
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

Example Blog
---------------------------------

There is a simple example blog included with Tasteful Framework.
To test this blog, you have to compile Tasteful Framework with examples first.
The following commands assume you are in the build directory which is the direct subdirectory of the root of Tasteful Framework.

    > cmake .. -DWITH_EXAMPLES=ON
    > make

Then you have to create the database.

    > sqlite3 ../examples/blog/blog.sqlite < ../examples/blog/blog.sqlite.sql

Then you can start the blog.

    > ./examples/blog/Blog ../examples/blog/blog.xml

The blog will then be available at [localhost:9000](http://localhost:9000).

Webapplication Configuration Format
-----------------------------------

The Webapplication Configuration Format is an XML derivate to configure the servers and databases of a web application.
Public and resource directories are also specified in such a configuration file.
Instead of using an xml configuration, the setup can also be done using methods on the WebApplication instance.
The format is described in detail in the [wiki](https://github.com/scheibel/tasteful-framework/wiki/Webapplication-Configuration-Format).

License
-----------

Tasteful Framework is licensed under the LPGL-3.
