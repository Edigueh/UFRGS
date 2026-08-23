#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// Precision tolerance.
const double EPSILON = 1e-7; 

// Calculates the volume of the box given the initial dimensions and the cutout size.
double calculateVolume(double sideA, double sideB, double cutoutSize) {
    return (sideA - 2.0 * cutoutSize) * (sideB - 3.0 * cutoutSize) / 2.0 * cutoutSize;
}

void solve() {
    double sideA, sideB;
    cin >> sideA >> sideB;

    // The cutout size cannot be negative, and neither can the resulting sides of the box.
    // Therefore, 2*x <= a (x <= a/2) and 3*x <= b (x <= b/3).
    double leftBound = 0.0;
    double rightBound = min(sideA / 2.0, sideB / 3.0); 
    
    double maxVolume = 0.0;

    // Ternary search loop to find the peak of the unimodal volume function.
    while (abs(rightBound - leftBound) > EPSILON) {
        
        // Divide the current search space into three equal parts.
        double leftThird = leftBound + (rightBound - leftBound) / 3.0;
        double rightThird = rightBound - (rightBound - leftBound) / 3.0;

        // Calculate the volume at both one-third marks.
        double volumeAtLeftThird = calculateVolume(sideA, sideB, leftThird);
        double volumeAtRightThird = calculateVolume(sideA, sideB, rightThird);

        // Narrow down the search space based on which volume is larger.
        if (volumeAtLeftThird >= volumeAtRightThird) {
            // The peak cannot be to the right of rightThird, discard the rightmost third.
            rightBound = rightThird;
        } else {
            // The peak cannot be to the left of leftThird, discard the leftmost third.
            leftBound = leftThird;
        }

        maxVolume = max({maxVolume, volumeAtLeftThird, volumeAtRightThird});
    }

    cout << fixed << setprecision(12);
    
    // At the end of the loop, leftBound and rightBound converge on the optimal cutout size.
    cout << leftBound << ' ' << maxVolume << '\n';
}

int main() {
    // Optimize standard I/O operations for performance in competitive programming
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}