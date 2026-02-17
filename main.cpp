#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>

float potential(float x) {
    return x * x;
}

using namespace std;

int main() {
    // QR decompose test
    cout << "\n========== QR decompose test ==========\n\n";
    const int n = 4;
    matrix A(n, n);
    A.at(0,0)=1; A.at(0,1)=2; A.at(0,2)=3; A.at(0,3)=4;
    A.at(1,0)=2; A.at(1,1)=1; A.at(1,2)=0; A.at(1,3)=1;
    A.at(2,0)=0; A.at(2,1)=2; A.at(2,2)=1; A.at(2,3)=0;
    A.at(3,0)=1; A.at(3,1)=0; A.at(3,2)=2; A.at(3,3)=1;
    QR_thin qr(A);
    QR_decompose(qr, A);
    // Check Q^T Q ≈ I
    float max_qtq_err = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            float d = dot(qr.Q, qr.Q, i, j);
            float want = (i == j ? 1.0f : 0.0f);
            max_qtq_err = max(max_qtq_err, std::abs(d - want));
        }
    cout << "[QR] max |Q^T Q - I| = " << max_qtq_err << "\n";
    // Check A ≈ Q*R
    matrix QR = mul(qr.Q, qr.R);
    float max_res_err = 0;
    for (int c = 0; c < n; c++)
        for (int r = 0; r < n; r++)
            max_res_err = max(max_res_err, std::abs(A.at(c,r) - QR.at(c,r)));
    cout << "[QR] max |A - Q*R| = " << max_res_err << "\n";

    cout << "\nAll tests completed.\n";
    return 0;
}
