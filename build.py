# Script to build the project for Windows and Linux.

import sys
import subprocess
import shutil
import os

print('Building...')

if (sys.platform == 'win32'):
    dependencies = ['cmake', 'git', 'nmake']

    for tool in dependencies:
        if shutil.which(tool) == None:
            print('Please, install', tool)
            sys.exit(1)

    pdcurses_dir = 'PDCurses'

    if not os.path.exists(pdcurses_dir):
        print("Downloading PDCurses...")
        try: 
            subprocess.run(['git', 'clone', 'https://github.com/wmcbrine/pdcurses.git', pdcurses_dir], check=True)
            print("Download successful.")
        except subprocess.CalledProcessError:
            print('Failed to download PDCurses.')
            sys.exit(1)
    else:
        print('PDCurses already downloaded.')

    print("Building PDCurses...")
    wincon_dir = os.path.join(pdcurses_dir, 'wincon')
    try:
        subprocess.run(['nmake', '-f', 'Makefile.vc'], cwd=wincon_dir, capture_output=True, text=True, check=True)
        print('Build successful.')
    except subprocess.CalledProcessError:
        print("Unable to build PDCurses.")
        print("Error code:", e.returncode)
        print("Error message:", e.stderr)
        sys.exit(1)

    try:
        subprocess.run(['cmake', '-S', '.', '-B', 'build', f'-DPDCURSES_DIR={pdcurses_dir}'], capture_output=True, text=True, check=True)
        print('CMake configured successfully.')
    except subprocess.CalledProcessError as e:
        print('CMake Config Error code:', e.returncode)
        print('Output:\n', e.stderr)
        sys.exit(1)
        
    try:
        subprocess.run(['cmake', '--build', 'build'], capture_output=True, text=True, check=True)
        print('The game has been built. Enjoy!')
    except subprocess.CalledProcessError as e:
        print('CMake Build Error code:', e.returncode)
        print('Output:\n', e.stderr)
    
elif (sys.platform == 'linux'):

        dependencies = ['gcc', 'cmake']

        for tool in dependencies:
            if shutil.which(tool) == None:
                print('Please, install', tool)
                sys.exit(1)

        try:
            output = subprocess.run(['cmake', '-S', '.', '-B', 'build'], capture_output=True, text=True, check=True)

            print('CMake configured successfully.')
        except subprocess.CalledProcessError as e:
            print('Error code:', e.returncode)
            print('Output:\n', e.stderr)
            sys.exit(1)
        
        try:
            output = subprocess.run(['cmake', '--build', 'build'], capture_output=True, text=True, check=True)
            print('The game has been built. Enjoy!')
        except subprocess.CalledProcessError as e:
            print('Error code:', e.returncode)
            print('Output:\n', e.stderr)
            sys.exit(1)