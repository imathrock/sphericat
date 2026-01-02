# QR decomposition
QR decomposition is a method of decomposing a matrix into 2 different matrix such that $$A = QR$$
There are different types of QR decomposition. The one we are concerened with is thin QR decomposition and so Q has the same dimensions as A and R is a upper triangular matrix. 

$A \in \R^{m\times n}$, $Q \in \R^{m\times n}$ and $R \in \R^{n\times n}$

The Q matrix's columns are orthogonal, which is the main purpose of a QR decomposition, to get an orthonormal basis in the range of A. The main algorithm is as follows:

### Classical Gram-Schmidt (CGS)

In CGS, we compute the -th orthogonal vector by subtracting the projections of  onto all *previously computed* orthogonal basis vectors .

**Pseudocode Implementation:**

```python
function QR_decomposition(A):
    m, n = dimension(A)
    Q = zeros(m, n)
    R = zeros(n, n)

    for i from 0 to n-1:
        v = A[:, i] # Start with original column

        for j from 0 to i-1:
            # Project onto previous basis vectors
            R[j, i] = dot(Q[:, j], A[:, i])
            v = v - R[j, i] * Q[:, j]

        R[i, i] = norm(v)
        Q[:, i] = v / R[i, i]

    return Q, R

```

The problem with this is that since floating point numbers have a rounding error, the matrix Q loses orthogonality as the input matrix becomes larger. To counter that a neat trick is to instead orthogonalize against the current basis as opposed to against A. This means we use a "fresher" vector that is more likely to hold orthogonality as matricies get larger.

### Modified Gram-Schmidt Algorithm

Given a matrix , we compute  and  such that the columns of  are orthonormal and  is upper triangular.

**Pseudocode Implementation:**

```python
function M_QR_Decomposition(A):
    m, n = dimension(A)
    Q = copy(A)
    R = zeros(n, n)

    for i from 0 to n-1:
        # 1. Normalize the current column
        R[i, i] = norm(Q[:, i])
        Q[:, i] = Q[:, i] / R[i, i]

        # 2. Orthogonalize remaining columns against the current one
        for j from i+1 to n-1:
            R[i, j] = dot(Q[:, i], Q[:, j])
            Q[:, j] = Q[:, j] - R[i, j] * Q[:, i]

    return Q, R

```

But even this method is not numerically stable for larger matrices. So some genius came up with an idea to use householder reflections. 

---

### Householder Reflections

This method is numerically stable. It zeroes out sub-column elements using reflection matrices . We store the Householder vectors  to implicitly represent , while  is transformed into .

**Pseudocode Implementation:**

```python
function Householder_QR(A):
    m, n = dimension(A)
    R = copy(A)
    Q = identity(m)

    for k from 0 to n-1:
        # 1. Create the reflector vector v for the current column
        x = R[k:m, k]
        alpha = -sign(x[0]) * norm(x)
        
        u = x
        u[0] = u[0] - alpha
        v = u / norm(u)

        # 2. Apply reflector to R (from the left): R = H * R
        # Optimization: H*A = A - 2*v*(v^T * A)
        # We only work on the submatrix R[k:m, k:n]
        R[k:m, k:n] -= 2 * outer_product(v, dot(v, R[k:m, k:n]))

        # 3. Accumulate Q (optional, if explicit Q is needed)
        # Apply reflector to Q (from the right): Q = Q * H^T = Q * H
        # Update columns k through m
        Q[:, k:m] -= 2 * outer_product(dot(Q[:, k:m], v), v)

    return Q, R

```