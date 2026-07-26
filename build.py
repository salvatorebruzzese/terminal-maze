# Script to build the project for Windows and Linux.

import sys
import subprocess
import shutil

print('Building...')

# TODO: download the PDCurses library, build it and link against it
if (sys.platform == 'win32'):
    print('Windows')
else:
    if (sys.platform == 'linux'):

        dependencies = ['gcc', 'cmake']

        for tool in dependencies:
            if shutil.which(tool) == None:
                print('Please, install', tool)
                sys.exit()

        try:
            output = subprocess.run(['cmake', '-S', '.', '-B', 'build'], capture_output=True, text=True, check=True)

            print('CMake configured succesfully')
        except subprocess.CalledProcessError as e:
            print('Error code:', e.returncode)
            print('Output:\n', e.stderr)
            sys.exit()
        
        try:
            output = subprocess.run(['cmake', '--build build'], capture_output=True, text=True, check=True)
            print('The game has been built. Enjoy!')
        except subprocess.CalledProcessError as e:
            print('Error code:', e.returncode)
            print('Output:\n', e.stderr)