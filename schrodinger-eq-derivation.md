# Where does the schrodinger equation originate from? And  what is a wavefunction?

In the book by DJ griffiths, on the first page he explains that the schrodinger equation is that to quantum mechanics what \(F=ma\) is to classical mechanics. Just how most of classical mechanics can be derived from the fact that \(F=ma\), most of quantum mechanics relies on the schrodinger equation. 

#### **But where does it exactly come from?**
Most textbooks just plonk this on your head:

\[
i\hbar \frac{\partial}{\partial t} \Psi(\mathbf{r}, t) = \left[ -\frac{\hbar^2}{2m} \nabla^2 + V(\mathbf{r}, t) \right] \Psi(\mathbf{r}, t)
\]

Most of them assume you are smarter, but if you are dumb like me this isn't helpful. Our DJ had nothing to say about this in the textbook I have so I had to dig around. \(F=ma\) can't exactly be derived from some common known axioms, it itself is an axiom. Similarly the schrodinger equation is kind of an axiom of QM. 

Before getting into that we should know what each of the components are. \(i=\sqrt{-1}\), \(\hbar\) is reduced planck's constant, \(\frac{\partial}{\partial t}\Psi(\mathbf{r}, t)\) is the time derivative of the wavefunction.  
For RHS, In classical mechanics we have seen that \(E = K+U\) where \(K\) is kinetic energy and \(U\) is potential energy, The RHS is exactly the same but in a QM context. The first term \(-\frac{\hbar^2}{2m} \nabla^2\) is "kinetic energy"(not in the sense of classical mechanics because we have a wave instead of particle.) and \(V(\mathbf{r}, t)\) is the potential function, and obviously \(\Psi(\mathbf{r}, t)\) is the wavefunction. 

[This video by physics with todd springer](https://www.youtube.com/watch?v=J_S4NESrq2I) provides a pretty good explaination of how it originates but I will provide an overview here:

The classical wave equation as a partial differential equation is given by 

\[
\frac{\partial^2 \Psi}{\partial t^2} = \alpha^2\frac{\partial^2 \Psi}{\partial x^2},\qquad \Psi(x,t)
\]

And the known solutions to it are 

\[
\Psi(x,t)=Ae^{i(kx-\omega t)}
\]

\[
\Psi(x,t) = A\cos(kx-\omega t),A\sin(kx-\omega t)
\]

Looking at this in context of photons, we need this to follow the following rules:

\[
E=h\nu \quad \text{or} \quad E = pc
\]

where \(p\) is the momentum and \(c\) is the speed of light. In our wave-equation \(k=\frac{2\pi}{\lambda}\) is the wavenumber, \(\omega=2\pi\nu\) is the frequency.  
Let's rewrite the wavenumber in terms of momentum and the frequency in terms of energy. 

\[
k=\frac{2\pi}{\lambda}=\frac{2\pi}{h}\cdot p = \frac p\hbar
\]

\[
\omega = 2\pi\nu=\frac{2\pi E}{h}=\frac E\hbar
\]

So our wavefunction becomes:

\[
\Psi = Ae^{\frac i\hbar (Px-Et)}
\]

Check to make sure this is a soln to the classical wave equation:

\[
\frac{\partial^2 \Psi}{\partial t^2} = \left(\frac{-iE}{\hbar}\right)^2\Psi
\]

\[
\frac{\partial^2 \Psi}{\partial x^2} = \left(\frac{iP}{\hbar}\right)^2\Psi
\]

substituting in:

\[
\left(\frac{-iE}{\hbar}\right)^2\Psi=c^2\left(\frac{iP}{\hbar}\right)^2\Psi
\]

\[
E^2=c^2P^2
\]

And we see that it satisfies the \(E=pc\) rule here. 

Now photons are massless, what if we have something that has a mass and is classically a particle? An electron. This equation describes all quantum systems where speeds are non relativistic, particle mass is not really small and creation/annihilation is not taken into consideration.  
For a particle, We have the following energy expression:

\[
E = \frac{p^2}{2m}+V
\]

Let's assume that the wave equation stays the same (treat the particle as a wave with de broglie wavelength), what we have to do is find a PDE whose solution is our wave equation. 

Let's take a time derivative:

\[
\frac{\partial\Psi}{\partial t} = \frac{-iE}{\hbar}\Psi
\]

\[
E = \frac{\hbar}{-i}\frac{\partial \Psi}{\partial t}\cdot \frac{1}{\Psi}
\]

Let's take the second position derivative:

\[
\frac{\partial^2\Psi}{\partial x^2} = \left(\frac{iP}{\hbar}\right)^2\Psi
\]

\[
P^2=\hbar^2\frac{\partial^2\Psi}{\partial x^2}\frac{1}{\Psi}
\]

Writing these energy terms in the classical energy expression:

\[
\frac{\hbar}{-i}\frac{\partial \Psi}{\partial t}\cdot \frac{1}{\Psi}
=
\frac{\hbar^2}{2m}\frac{\partial^2\Psi}{\partial x^2}\frac{1}{\Psi}+V
\]

Multiplying by \(\Psi\) and rearranging:

\[
i\hbar\frac{\partial \Psi}{\partial t} = \frac{\hbar^2}{2m}\frac{\partial^2\Psi}{\partial x^2}+V\Psi
\]

Nice! This is the schrodinger equation in 1D, If we were to extrapolate this into 3D we would get the previously mentioned schrodinger equation with the laplacian operator in place of a single second derivative. 

Now that we have found the schrodinger equation we should talk about the wave function and what that represents.

### What is a wavefunction?
A wavefunction is a mathematical function that describes the quantum state of a particle, as in if we were to square this function \(|\Psi|^2\) we would get a function that describes the probability of finding the particle at a given position \((x,y,z)\). Thus it is not a physical wave but more so a probabilistic representation or the particle's position, hence a wavefunction is not a measurable quantity.

Because it provides only a probabilistic representation, the wavefunction always needs to be normalized otherwise the probability at certain places would be greater than 1, making it unrealistic. A wavefunction is normalized if the following condition is met:

\[
\int^{+\infty}_{-\infty} \left|\Psi(\mathbf{r},t)\right|^2 d\mathbf{r} = 1
\]

This ensures that the probability across space is always \(<1\). This also limits the allowed wavefunction to only square integrable functions.  
*Square integrable* functions are functions that have a similar constraint:

\[
\int^{+\infty}_{-\infty} \left|X(\mathbf{r},t)\right|^2 d\mathbf{r} < \infty
\]

Or simply that they have a positive finite integral when they are squared.

The purpose of this project is to create a schrodinger equation solver, which means atleast to begin with we will not cover the bra ket notation and Hilbert spaces n stuff right now but I will have a post explaining all of that too.
