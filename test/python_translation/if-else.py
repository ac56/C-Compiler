def main():
    if 1:
        return 0;
    else:
        return 1;

    return 1;


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
