# Modelviewer

An application which can display many 3d file formats, developed in C++.

## Supported formats

This application is based on the [Open Asset Import Library](https://github.com/assimp/assimp), and therefore supports many 3d formats, including FBX, 3DS, OBJ and BLEND.
A full list of supported formats can be found on [Assimp's GitHub page](https://github.com/assimp/assimp#supported-file-formats).

## Building

This project is built using [CMake](https://cmake.org/).

### Requirements

* cmake >= 3.0
* Qt5
* A C++ compiler with support for the C++17 standard

### Example

To build the project with the default CMake generator, use the following commands (calling the CMake configuration step two times is necessary due to limitations of the current project setup):
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cmake .
cmake --build .
```

## Running

The application can be run by typing
```
build/modelviewer <path-to-file>
```
from the repository root directory, whereas `<path-to-file>` is the path to the 3d model that should be opened.
If the parameter is left empty, no file is opened.
A file can also be opened from inside the program, via the File->Open menu entry.

Furthermore, this program can be set as the default application for 3d models by the operating system, which allows it to be used by doubleclicking on the 3d model file.

## License

This project is licensed under the **GPLv3**.
See [LICENSE.txt](LICENSE.txt) for the full license text.
Since the short license notice recommended by the GPLv3 is not present in the source files, it is displayed here instead:

```
    Modelviewer, an application to display various 3d file formats.
    Copyright (C) 2019  Markus Prettner

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
