x = 5
y = 6
def f():
    if ((x < y) and (0 < x)):
        return 0;
    else:
        pass
    return 1;


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
