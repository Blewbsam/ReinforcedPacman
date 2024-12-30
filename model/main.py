import sys
import os
import numpy
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'build')) # relative path to build folder used for import
import pacman

def main():
    gs = pacman.GameState()
    display = pacman.Display(gs)

    while display.running():
        display.update()
        display.render()

if __name__ == "__main__":
    main()