while True:
    try:
        height = int(input("Height: "))
        blankSpace = height
        if (1 <= height <= 8):
            for i in range(height):
                print(" " * (blankSpace-1), end="")
                print("#"*(i+1), end="")
                print("  ", end="")
                print("#"*(i+1))
                blankSpace -= 1
            break
        else:
            pass
    except ValueError:
        pass
