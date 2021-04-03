def product(x, y):
    return (x * y);

def main():
    return product(0,42);


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
