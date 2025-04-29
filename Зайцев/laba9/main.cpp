#include <iostream>
#include <cmath>

using namespace std;

double countSqrt(int now, int n) {
    if (now > n)
        return 0;
    return sqrt(now + countSqrt(now + 1, n));
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    double result = countSqrt(1, n);
    cout << "Result: " << result << endl;

    return 0;
}
