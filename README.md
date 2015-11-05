# filesentry

A small and modern C++ wrapper for OS file monitoring systems. Currently it uses Win32 `ReadDirectoryChangesW` for monitoring changes in Windows and `inotify` in Linux. OSX is supported via `kqueue`s and directory scans.

`filesentry` is a modern C++ wrapper for the `SimpleFileWatcher` library originally built by James Wynn.

## Getting started

### Build

Use one of the build scripts or project files provided in `build/`, or generate your own using premake5.

### Use

Here is the demo, provided in `SimpleDemo.cpp`.

```cpp
#include <filesentry/FileWatcher.h>
#include <iostream>

int main(int argc, char** argv) {
	try  {
		// create the file watcher object
		fs::FileWatcher fileWatcher;

		// add a directory watch to the system
        // this scans the `test/` directory for any changes 
        fs::WatchID watchID = fileWatcher.addWatch("test", [](
            fs::WatchID watchID, const std::string& dir, const std::string filename, fs::Action action
        ) -> void {
            std::cout << "DIR ( " << dir << " ) FILE ( " << filename << " ) has event " << action << std::endl;
        });
        
		std::cout << "Press ^C to exit demo" << std::endl;

		// loop until a key is pressed
		while( true ) {
			fileWatcher.update();
		}
	} 
	catch( std::exception& e ) {
		fprintf(stderr, "An exception has occurred: %s\n", e.what());
	}

	return 0;
}
```

A separate project is provided for the demo in the build script.

## Caveats

When some programs write data in Win32, they will generate both an Add and Modify event. This is likely because the program is actually using two separate calls to write its data.

Because of the time it takes to write the data to the file, it may be necessary in some cases to wait a few milliseconds after the event to be able to safely access the file's contents.

## TODO

* remove extraneous `#pragma`s.
