int x = 42;
extern int global();

int main() {
    return !(global());
}
