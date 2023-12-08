#include <stdio.h>

// To check if it works correctly run: 
// echo 1.2 2.3 3.4 4.5 5.6 6.7 | ./double_ascii_to_double_bin | ./avg_doubles
// and get 3.950000

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