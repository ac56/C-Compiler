extern int self_recursion(int);

int main() {
    return !(self_recursion(0) == 42);
}
