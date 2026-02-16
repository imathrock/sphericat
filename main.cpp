#include "matrix\matrix.hpp"
#include <cstdlib>
#include <ctime>
#include "clankerfuncs.h"

float potential(float x) {
    return x * x;
}

using namespace std;

int main() {
    // Small test: easy to inspect
    const int N_small = 8;
    const int M_small = 5;

    tri_diag_matrix A_small = generate_hamiltonian(N_small, 5.0f, 2.5f, potential);

    cout << "========== Arnoldi solver tests ==========\n\n";
    cout << "--- Small system N=" << N_small << ", M=" << M_small << " ---\n";
    cout << "Tridiagonal A (first 8x8):\n";
    print_T_matrix(A_small);
    cout << "\n";

    Arnoldi_matrices arnoldi(M_small, A_small);
    print_Arnoldi(arnoldi);
    test_Arnoldi_orthogonality(arnoldi);
    test_Arnoldi_relation(A_small, arnoldi);

    cout << "\n========== Lanczos solver tests ==========\n\n";
    cout << "--- Small system N=" << N_small << ", M=" << M_small << " ---\n";

    Lanczos_result lanczos(M_small, A_small);
    print_Lanczos(lanczos);
    test_Lanczos_orthogonality(lanczos);
    test_Lanczos_relation(A_small, lanczos);

    // Larger run (no full print)
    const int N_big = 50;
    const int M_big = 12;
    tri_diag_matrix A_big = generate_hamiltonian(N_big, 5.0f, 2.5f, potential);

    cout << "\n--- Larger system N=" << N_big << ", M=" << M_big << " (numerical checks only) ---\n";
    Arnoldi_matrices arnoldi_big(M_big, A_big);
    test_Arnoldi_orthogonality(arnoldi_big);
    test_Arnoldi_relation(A_big, arnoldi_big);

    Lanczos_result lanczos_big(M_big, A_big);
    test_Lanczos_orthogonality(lanczos_big);
    test_Lanczos_relation(A_big, lanczos_big);

    cout << "\nAll tests completed.\n";
    return 0;
}
