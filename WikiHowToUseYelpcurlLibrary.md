## How to use yelpcurl library? ##
yelpcurl is an open-source pure C++ library for Yelp.com APIs. yelpcurl uses cURL library for handling HTTP requests and responses. Building applications using yelpcurl is quite easy:
  * Compile yelpcurl source files (yelpcurl.h and yelpcurl.cpp) and link with cURL library (libcurl.lib) to build static library yelpcurl.lib.
  * Include yelpcurl.h and cURL headers (present in /include/curl/ directory in cURL source) in your Yelp based application and link to yelpcurl.lib and also libcurl.lib/libcurl.dll.
  * Instantiate an object of yelpCurl class and use the Yelp API wrappers that are exposed as public methods.
  * yelpcurl works on all OS (Windows, Linux, Mac etc.) as it is written completely in C++ and the only dependency is cURL (which works on all OSes mentioned earlier).

## UNIX/Linux ##
Will add a Makefile soon!

## Windows ##
The yelpcurl.lib library that is present in the "Download" section is built using Visual C++ 6.0. If you are using a newer version of Visual C++ to build your application, then you may encounter linker errors if you link yelpcurl.lib built on older Visual C++ version (as mentioned here: http://code.google.com/p/twitcurl/issues/detail?id=4 ). To overcome these link errors, please download the source of yelpcurl and build the library using your (newer) Visual C++ IDE. Later, use this newly built library to link with your application.

**Note:** Currently Microsoft Visual C++ 6.0 workspace (dsw) file is provided with the yelpcurl source. This workspace can be used to compile and build yelpcurl on Windows using any of the Visual C++ applications (6.0 or later). If you are using any other Windows based C++ IDE, then you can create new "workspace" and just add yelpCurl header/source files to this new "workspace".