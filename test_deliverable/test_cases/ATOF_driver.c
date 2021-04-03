#include <stdlib.h>

extern double test_atof();

int main() {
    return !(test_atof() == 42);
}
