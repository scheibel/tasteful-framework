Tasteful Framework
============

Tasteful Framework is web framework library written in C++ based on Tasteful Server.
It provides an MVC-architecture with routes, controllers, models and views as well as a datamapper and an activerecord as an object-relational mappers.

An example application is a simple blog in [/source/examples/blog/](https://github.com/scheibel/tasteful-framework/tree/master/source/examples/blog).

Platform independency is provided through [cmake-init](https://github.com/hpicgs/cmake-init).
Currently supported platforms are:
 * Windows
 * Linux
 * OS X

Requirements
---------------------

 * [Qt 5.0](http://qt.nokia.com/)
 * [gcc 4.7](http://gcc.gnu.org/)
 * [CMake 2.8.9](http://www.cmake.org/)
 * [Tasteful Server](https://github.com/scheibel/tasteful-server)

Example Blog
---------------------------------

There is a simple example blog included with Tasteful Framework.
To test this blog, you have to compile Tasteful Framework with examples first.
Then you have to create the database.

    > sqlite3 ../source/examples/blog/blog.sqlite < ../source/examples/blog/blog.sqlite.sql

Then you can start the blog.

    > ./blog ../source/examples/blog/blog.xml

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
