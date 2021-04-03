int self_recursion(int count) {
    if (count == 5) {
        return 42;
    } else {
        return self_recursion(count+1);
    }
}
