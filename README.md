# sphericat

C++ implementation of numerical eigensolvers for the time-independent Schrodinger equation using finite differences and Krylov methods.

## Implementation

- Dense matrix (column-major) and tridiagonal matrix types with AVX2-optimized operations
- QR decomposition via Modified Gram-Schmidt and Householder reflection
- QR algorithm for eigenvalue computation
- Arnoldi iteration for general matrices
- Lanczos iteration for symmetric tridiagonal systems
- Hamiltonian builder for 1D potentials via finite differences

## Tests

`main.cpp` validates Arnoldi against known eigenvalues for matrices up to 500x500 with M < 10 Krylov vectors.

## Build

```bash
make
./main
```

Requires C++17 and AVX2 support.

## Structure

- `matrix/` - linear algebra core
- `main.cpp` - Arnoldi tests
- `PhysicsNotes/` - derivations and theory
- `programmingnotes/` - implementation notes
