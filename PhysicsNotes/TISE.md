# Time Independent Schrödinger Equation

## What does the Schrödinger equation tell us now?

$$
i\hbar\frac{\partial \Psi}{\partial t} = -\frac{\hbar^2}{2m}\frac{\partial^2 \Psi}{\partial x^2} + V\Psi
$$

Solving this Sturm-Liouville partial differential equation will give us $\Psi(x,t)$. Why are we solving the Schrödinger equation though? What would be the meaning of the result? $|\Psi|^2$ is the probability distribution of the electron. We can get all kinds of information from the wavefunction, stay with me now.

## Analytic Solution: Separation of Variables

Let's start by trying to solve this equation. To attack this problem we will use separation of variables (SOV). We represent the wavefunction as a product of 2 functions:

$$
\Psi(x,t) = \psi(x)\phi(t)
$$

We can then write the equation as:

$$
i\hbar\psi\frac{\partial \phi}{\partial t} = -\phi\frac{\hbar^2}{2m}\frac{\partial^2 \psi}{\partial x^2} + V\psi\phi
$$

Divide by $\psi\phi$:

$$
i\hbar\frac{1}{\phi}\frac{\partial \phi}{\partial t} = -\frac{\hbar^2}{2m}\frac{1}{\psi}\frac{\partial^2 \psi}{\partial x^2} + V
$$

Now this is a more solvable state because the LHS and RHS are completely independent of each other. So we can solve them separately by setting them both equal to a constant, $E$ (Energy).

### 1. The Time Function

$$
\frac{\partial\phi(t)}{\partial t} = \frac{-iE}{\hbar}\phi(t)
$$

Which yields the solution:

$$
\phi(t) = e^{-iEt/\hbar}
$$

### 2. The Position Function

$$
E = -\frac{\hbar^2}{2m}\frac{1}{\psi}\frac{\partial^2 \psi}{\partial x^2} + V
$$

Rearranging for the second derivative:

$$
-\frac{2m}{\hbar^2}(E-V)\psi = \frac{\partial^2 \psi}{\partial x^2}
$$

With this, we can not proceed any further without knowing what the potential function $V(x)$ looks like.

---

## Numerical Solution: Finite Difference Method

At this point, I am basically revising for my quantum mechanics final by writing about basic stuff but this is basically solving the Schrödinger equation analytically. We need to solve it numerically! So let's break up this problem into parts, literally.

We can represent the derivatives of the wavefunction using the finite difference approximation:

$$
\frac{\partial^2 \psi}{\partial x^2} \approx \frac{\psi_{n-1}-2\psi_{n}+\psi_{n+1}}{dx^2}
$$

What we have done here is broken up the equation into a total of $N$ parts (a discrete grid), turning the differential equation into a linear algebra eigenvalue problem:

$$
\mathbf{H}\psi = E\psi
$$