def main():
    return (10 - 10);


if __name__ == '__main__':
    try:
        import sys
        sys.exit(main())
    except NameError:
        sys.exit(0)
