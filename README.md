# Cluster Demo

This is a demo project that implements a simple automotive instrument cluster UI and related imaginary infrastructure.


# Components

Individual components of the project are:
+ 'ipc' (Simple local socket based client-server IPC library)
+ 'bus' (Simple communication bus service that can pass direct messages or broadcasts between clients)
+ 'busclient' (Client library for 'bus')
+ 'simulator' (Simulator app that broadcasts telemetry data to 'bus')
+ 'application' (Instrument cluster app that visualises telemetry data sent by 'simulator')
+ 'gfx' (A tool to generate static graphics assets for the project mainly from QML sources)

All binaries have "cluster" prefix.


# Some design choices

IPC uses local sockets and 'bus & 'busclient' use JSON as a message format. Naturally these decision sacrifice some performance over portability, maintainability & ease of use.

'simulator' is the "main" executable that automatically launches also 'bus' and 'application'. It can be used to manually control the telemetry data using arrow keys. Up & down increase & decrease speed, left & right toggle respective turning signals on & off. All telemetry data is sent to the 'bus' every 100ms. In addition, individual states of turn signals are updated immediately when changed.

'application' runs IPC in a separate thread to prevent communication blocking the UI. For maximum startup speed, 'application' first shows just a background image and only after that loads the rest of the UI.

It is possible to run multiple 'application' instances connecting to the same 'bus'. There is also currently no prevention mechanism to run multiple 'simulator' or 'bus' instances.


# Improvement areas

+ Automatic testing support (none at the moment)
+ A more complex UI could benefit from a separate UI library
+ A more complex UI would of course need more structuring also
+ More performant IPC (binary, shared memory perhaps?)
+ Better graphics
+ Prevent multiple 'bus' & 'simulator' instances
+ Get rid of makefile warnings related to automatic translation files
+ Add random simulation mode to 'simulator'


# Dependencies

+ Qt 5.10 (mainly dictated by QML import statements)

