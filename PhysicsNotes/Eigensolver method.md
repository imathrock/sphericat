# Creating an Eigensolver

These are my notes on how to make an eigensolver. This is the simplest part of the project and can be used to solve for the TISE.

## Infinite Square Well Context

Here I assume that the particle is in an infinite square well. The potential $V$ is $0$ everywhere except at the edges where the potential is infinite, given by the following:

$$V(x) = \begin{cases} 

0 & 0 < x < L \\

\infty & \text{otherwise}

\end{cases}$$

This means that there are boundary conditions that force the wavefunction to be $0$ at the edges.

## Discretization (Finite Difference Method)

The idea is that we try to express the wavefunction as a system of equations by using the following approximation for the second derivative:

$$\frac{\partial^2 \psi}{\partial x^2} \approx \frac{\psi_{n-1}-2\psi_{n}+\psi_{n+1}}{dx^2}$$

Replace the second derivative in TISE with this expression:

$$E\psi = -\frac{\hbar^2}{2m}\frac{\psi_{n-1}-2\psi_{n}+\psi_{n+1}}{dx^2}$$

Making stuff cleaner, we take $\hbar = 1$, because $\hbar = 1.0545\times 10^{-34} J\cdot s$. A REALLY small value; 32-bit float ain't got that much horsepower and it would basically make our operations slower. So we multiply that later.

Now we have a system of equations:

$$\begin{align*}

E\psi_1 &= -\frac{1}{2m}\frac{\psi_{0}-2\psi_{1}+\psi_{2}}{dx^2} \\

E\psi_2 &= -\frac{1}{2m}\frac{\psi_{1}-2\psi_{2}+\psi_{3}}{dx^2} \\

&\vdots \\

E\psi_N &= -\frac{1}{2m}\frac{\psi_{N-1}-2\psi_{N}+\psi_{N+1}}{dx^2}

\end{align*}$$

## Matrix Formulation

We can rewrite this as a matrix of coefficients!

$$-\frac{1}{2m (dx)^2}

\begin{bmatrix}

-2 & 1 & 0 & \cdots & 0 \\

1 & -2 & 1 & \cdots & 0 \\

0 & 1 & -2 & \cdots & 0 \\

\vdots & \vdots & \vdots & \ddots & \vdots \\

0 & 0 & 0 & \cdots & -2

\end{bmatrix}

\begin{bmatrix}

\psi_1 \\

\psi_2 \\

\psi_3 \\

\vdots \\

\psi_N

\end{bmatrix}

=

E

\begin{bmatrix}

\psi_1 \\

\psi_2 \\

\psi_3 \\

\vdots \\

\psi_N

\end{bmatrix}$$

Since the potential is $0$ inside the well, the Hamiltonian matrix does not have a potential value in it.

If we look at the Schrödinger equation closely, it is an eigenvalue problem. The eigenvalue is the energy level and the eigenvector is our piecewise wavefunction. In the real thing, there are an infinite number of energy levels since the potential is infinite, but we only have finite unique eigenvalues. At $\lim_{N\to \infty}$, the total number of eigenvalues (energy levels) is countably infinite just like the analytical solutions say.

## Adding Potential

If we DID have a potential, we would discretize it the same way and simply add it to the existing Hamiltonian matrix to get the new Hamiltonian as the following:

$$\left(

-\frac{\hbar^2}{2m (dx)^2}

\begin{bmatrix}

-2 & 1 & 0 & \cdots & 0 \\

1 & -2 & 1 & \cdots & 0 \\

0 & 1 & -2 & \cdots & 0 \\

\vdots & \vdots & \vdots & \ddots & \vdots \\

0 & 0 & 0 & \cdots & -2

\end{bmatrix}

+

\begin{bmatrix}

V_1 & 0 & 0 & \cdots & 0 \\

0 & V_2 & 0 & \cdots & 0 \\

0 & 0 & V_3 & \cdots & 0 \\

\vdots & \vdots & \vdots & \ddots & \vdots \\

0 & 0 & 0 & \cdots & V_N

\end{bmatrix}

\right)

\begin{bmatrix}

\psi_1 \\

\psi_2 \\

\psi_3 \\

\vdots \\

\psi_N

\end{bmatrix}

=

E

\begin{bmatrix}

\psi_1 \\

\psi_2 \\

\psi_3 \\

\vdots \\

\psi_N

\end{bmatrix}$$

How would we handle this in 2D and 3D? No idea yet but we will figure it out.

## Implementation Notes

Now I need to find the eigenvalues of this Hamiltonian matrix. This matrix is a variation of a Toeplitz matrix; the notable characteristic is that it has a diagonal and also has 2 other diagonals filled with the same values. The rest of the values are 0.

To begin with, I would implement these matrices as a flat index and write a macro that can access these using i and j.