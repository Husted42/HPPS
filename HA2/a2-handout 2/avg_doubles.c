#include <stdio.h>

int main() {
    double sum = 0.0;
    int count = 0;

    double num;
    while (fread(&num, sizeof(double), 1, stdin) == 1) {
        sum += num;
        count++;
    }

    if (count > 0) {
        double mean = sum / count;
        printf("%lf\n", mean);
    }

    return 0;
}