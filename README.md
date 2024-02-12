# FileMapping.cpp - C++ Library for Managing File Mappings in Windows

This is a C++ library for managing file mappings in Windows using the WinAPI.

## Overview

The `FileMapping` class provided in this library allows you to create, open, and manage file mappings in Windows. File mapping is a mechanism for mapping a file into memory, allowing for efficient file access and sharing between processes.

## Features

- Create file mappings
- Open existing file mappings
- Map files into memory
- Retrieve file size
- Access memory-mapped file data

## Installation

To use this package, you can clone the repository and compile it using a C++ compiler:

```bash
git clone https://github.com/NIR3X/FileMapping.cpp
cd FileMapping.cpp
make
```

## Usage

To use the `FileMapping` class in your project, include the `FileMapping.h` header file and link against `FileMapping.a`.

```cpp
#include "FileMapping.h"
#include <iostream>

int main() {
	// Example usage
	CFileMapping fileMapping(L"path_to_file");
	LPVOID mapView = fileMapping.getMapView();
	// Use the memory-mapped file...
	return 0;
}
```

## License
[![GNU AGPLv3 Image](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.html)  

This program is Free Software: You can use, study share and improve it at your
will. Specifically you can redistribute and/or modify it under the terms of the
[GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html) as
published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
