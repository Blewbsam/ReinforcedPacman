import sys
import os
import numpy
import matplotlib.pyplot as plt
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'build')) # relative path to build folder used for import
import pacman





def main():
    gs = pacman.GameState()
    display = pacman.Display(gs)
    k = 0
    arr = None

    while display.running():
        k += 1
        display.update()
        display.render()
        if k == 200:
            arr = display.get_screenshot()
            break

    print(arr.shape)

    plt.imshow(arr)
    plt.axis('off') 
    plt.show()
            

if __name__ == "__main__":
    main()