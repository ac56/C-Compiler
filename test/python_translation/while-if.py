def main():
    i = 0
    while 1:
        if (i > 5):
            return 0;
        else:
            pass
        i = (i + 1)

    return 1;


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
