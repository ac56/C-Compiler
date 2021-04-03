x = 2
y = 6
def main():
    i = 5
    while (i > 0):
        i = (i - 1)

    return i;


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
