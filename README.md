OculusHmdOrientation
====================

Minimal application to get orientation of the Oculus Rift HMD.

Mostly inspired from the [Minimal Oculus Application](https://developer.oculusvr.com/wiki/Minimal_Oculus_Application) of the official OculusVR Wiki.

### License

Copyright (c) 2014 Sébastien Rombauts (sebastien.rombauts@gmail.com)

Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
or copy at http://opensource.org/licenses/MIT)

### Getting and Building the dependencies

1. Get the submodule (OculusSDK)

```bash
git submodule init
git submodule update
```

### Building the application

On Linux :

```bash
cmake .
cmake --build .     # of simply "make"
```

On Windows :

```bash
cmake . -G "Visual Studio 10"
cmake --build .     # or simply [open and build solution]
```
