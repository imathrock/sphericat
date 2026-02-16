# sphericat

A C++ project to discretize and solve the time-independent Schrödinger equation, then visualize spherical harmonics and wavefunctions—inspired by [qmsolve](https://github.com/quantum-visualizations/qmsolve), with a smaller scope and a custom linear algebra stack.

This project ties together ideas from my fourth-year courses: **advanced linear algebra**, **partial differential equations**, and **quantum mechanics**. In QM we solved the Schrödinger equation; in PDEs we discretized differential operators. The link is that the Schrödinger equation is a Sturm–Liouville-type PDE, so we can discretize it and solve for eigenfunctions numerically. I wanted to learn OpenGL and C++, so I started this as a way to implement and visualize those solutions myself.

There will be a devblog post series documenting the project and how the methods were derived. One constraint: I limit my use of AI to minor bug fixes and syntax help; the rest is hand-written code and posts.

---

## Project goal

- **Numerical:** Solve the TISE (1D now; 3D hydrogen next) via finite differences and Krylov eigensolvers.
- **Visual:** Eventually visualize wavefunctions and spherical harmonics (e.g. isosurfaces, slices).

---

## What’s implemented

- **1D TISE:** Finite-difference discretization of \( -\frac{1}{2}\psi'' + V\psi = E\psi \) on a 1D grid, yielding a tridiagonal Hamiltonian.
- **Hamiltonian builder:** `generate_hamiltonian(N, L, offset, V)` for arbitrary 1D potential \(V(x)\).
- **Linear algebra (current):**
  - Dense `matrix` (column-major), tridiagonal `tri_diag_matrix`, and `fvec` (float vector).
  - Basic ops: add, sub, mul, norm, transpose; QR (Gram–Schmidt), QR algorithm for eigenvalues.
  - Tridiagonal matvec `TDmat_vec_mul`, dot, normvec, axpy-style helpers.
- **Krylov solvers:**
  - **Arnoldi:** Builds orthonormal basis \(Q\) and upper Hessenberg \(H\) with \(AQ \approx QH\).
  - **Lanczos:** For symmetric (tridiagonal) \(A\), builds \(Q\) and symmetric tridiagonal \(T\) with \(AQ \approx QT\).
- **Tests:** `main` and `clankerfuncs.h` run small/larger systems and check orthogonality of \(Q\) and the relations \(AQ \sim QH\) and \(AQ \sim QT\).

---

## Currently in progress: matrix library reimplementation

A **functional reimplementation** of the matrix layer is planned (not a full production GEMM):

- **Robust structs:** Single dense type (column-major, one buffer), clear tridiagonal type, vector-as-column or thin wrapper so indexing is consistent.
- **Minimal core API:** `gemm`, `gemv` (dense + tridiagonal), `dot`, `nrm2`, `axpy`, `scal`, `copy`, plus column views so that algorithms don’t need many one-off helpers.
- **Goal:** Simpler, easier-to-reason-about code so that implementing QR, Arnoldi, and Lanczos stays short and maintainable, while remaining correct and fast enough for 3D hydrogen (moderate grid sizes).

---

## Next steps (solver and 3D hydrogen)

1. **Stabilize the new matrix API** and port QR, Arnoldi, and Lanczos to it; keep tests green.
2. **Radial 3D hydrogen:** In spherical coordinates, \(V(r) = -1/r\). Separation gives a radial equation per \(\ell\) with \(V_{\text{eff}}(r) = -1/r + \ell(\ell+1)/(2r^2)\). Discretize in \(r\) → tridiagonal (or banded) Hamiltonian per \(\ell\); solve with the same Lanczos/Arnoldi pipeline to get \(R_{n\ell}(r)\) and \(E_{n\ell}\).
3. **Spherical harmonics:** Implement or plug in \(Y_{\ell m}(\theta,\phi)\) and form \(\psi(r,\theta,\phi) = R_{n\ell}(r)\,Y_{\ell m}(\theta,\phi)\) for chosen \((n,\ell,m)\).
4. **Visualization:** Evaluate \(|\psi|^2\) on a 3D grid, export (e.g. VTK) and view in Paraview/PyVista, or render in C++ (e.g. OpenGL) with isosurfaces or slices.

---

## Build

```bash
make
./main
```

Requires a C++17 compiler; the makefile uses `g++` with `-O3 -mavx2 -mfma` (and includes `immintrin.h` where used).

---

## Layout

- `matrix/` — matrix types, QR, Arnoldi, Lanczos, Hamiltonian builder.
- `main.cpp` — driver and tests for Arnoldi and Lanczos.
- `clankerfuncs.h` — printing and test helpers (orthogonality, \(AQ \sim QH\), \(AQ \sim QT\)).
- `PhysicsNotes/` — notes on TISE, finite differences, eigensolvers (Arnoldi/Lanczos), QR.
- `programmingnotes/` — build/implementation notes (e.g. CMake).
