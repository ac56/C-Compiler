x = 5
y = 0

def positive(x):
    if (0 < x):
        return 1;
    else:
        return 0;


def main():
    y =  not positive(x)


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
