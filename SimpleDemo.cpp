/**
	Demo app for FileWatcher. FileWatcher is a simple wrapper for the file
	modification system in Windows and Linux.

	@author James Wynn
	@date 2/25/2009

	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

#include <filesentry/FileWatcher.h>
#include <iostream>

int main(int argc, char** argv)
{
	try 
	{
		// create the file watcher object
		fs::FileWatcher fileWatcher;

		// add a directory watch to the system
        // this scans the `test/` directory for any changes
        fs::WatchID watchID = fileWatcher.addWatch( "test", [](
            fs::WatchID watchID, const std::string& dir, const std::string filename, fs::Action action
        ) -> void {
            std::cout << "DIR ( " << dir << " ) FILE ( " << filename << " ) has event " << action << std::endl;
        } );
        
		std::cout << "Press ^C to exit demo" << std::endl;

		// loop until a key is pressed
		while( true )
		{
			fileWatcher.update();
		}
	} 
	catch( std::exception& e ) 
	{
		fprintf(stderr, "An exception has occurred: %s\n", e.what());
	}

	return 0;
}
