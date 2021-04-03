x = 5
y = 6
def swap(x, y):
    z = x
    x = y
    y = z

def main():
    return 0;


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
