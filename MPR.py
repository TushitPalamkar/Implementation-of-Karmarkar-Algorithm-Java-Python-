import numpy as np


class Mpr:
    @staticmethod
    def matread(m, n):
        a = np.zeros((m, n), dtype=int)
        for i in range(m):
            for j in range(n):
                a[i, j] = int(input())
        return a

    @staticmethod
    def matdisplay(a, m, n):
        for i in range(m):
            for j in range(n):
                print(a[i][j], end="\t")
            print("\n")

    @staticmethod
    def transpose(a, m, n):
        b = np.zeros((n, m), dtype=int)
        for i in range(m):
            for j in range(n):
                b[j][i] = a[i][j]
        return b

    @staticmethod
    def diagonal(m, n):
        a = np.zeros((m, n), dtype=int)
        for i in range(m):
            for j in range(n):
                if i == j:
                    a[i][j] = int(input())
                else:
                    a[i][j] = 0
        return a

    @staticmethod
    def matsubtract(a, b, m, n):
        c = np.zeros((m, n), dtype=int)
        for i in range(m):
            for j in range(n):
                c[i][j] = a[i][j] - b[i][j]
        return c

    @staticmethod
    def matmultiply(a, b, m, n):
        c = np.zeros((m, n), dtype=int)
        for i in range(m):
            for j in range(n):
                for k in range(n):
                    c[i][j] += a[i][k] * b[k][j]
        return c


class Main:
    @staticmethod
    def main():
        print("Consider the problem statement:\n Min: 1/2(Xk * c-d)^2\n Subject to A *Xk * d = 0 ")

        print(" Enter the number of Rows:")
        m = int(input())
        print("Enter the number of Columns:")
        n = int(input())

        print("Enter the matrix A:\n")
        A = Mpr.matread(m, n)
        Mpr.matdisplay(A, m, n)
        print("transpose of A is :")
        transA = Mpr.transpose(A, m, n)
        Mpr.matdisplay(transA, m, n)

        print("Enter the matrix c:\n")
        c = Mpr.matread(m, n)
        Mpr.matdisplay(c, m, n)

        print("Enter the diagonal matrix Xk:\n")
        Xk = Mpr.diagonal(m, n)
        Mpr.matdisplay(Xk, m, n)

        print(
            "In order to solve the problem we find the lagrangian of the equation consisting of 2 parameters(d and mu) to determine the minimum value")
        print("Therefore L(d,mu)= 1/2(XK * c - d)^2 + mu^T *A * Xk * d")
        print(
            "In order to obtain the gradient, we must differentiate the problem with respect to d\n The gradient= Zero")
        print(" We get: -(Xk * c- d) + Xk * A^T * mu = 0")
        print("Thus d = Xk * c - Xk * A^T * mu\n However we need to obtain the value of mu first")

        print("Multiplying A * Xk on both sides as d should satisfy the feasibility")
        print("A * Xk *d = A * Xk^2 * c - A * Xk * A^T * mu\n ")

        print("Therefore A * Xk^2 * c = A * Xk^2 * A^T * mu\n")
        print("Obtaining Xk^2\n")
        Xk2 = Mpr.matmultiply(Xk, Xk, m, n)
        Mpr.matdisplay(Xk2, m, n)

        print("Solving the LHS")
        AXk2 = Mpr.matmultiply(A, Xk2, m, n)
        Mpr.matdisplay(AXk2, m, n)
        print("AXk2 * c will give us the solution of the LHS:\n ")
        AXk2c = Mpr.matmultiply(AXk2, c, m, n)
        print("The LHS is : \n")
        Mpr.matdisplay(AXk2c, m, n)

        print(
            "Solving the RHS:\n Since we have obtained the product of AXk2 already, the required answer can be obtained by multiplying it with AT")
        AXk2At = Mpr.matmultiply(AXk2, transA, m, n)
        Mpr.matdisplay(AXk2At, m, n)
        print(f"The elements of AXk2At are d{AXk2At[0][0]} {AXk2At[0][1]} {AXk2At[1][0]} {AXk2At[1][1]}")

        determinant = (AXk2At[0][0] * AXk2At[1][1]) - (AXk2At[0][1] * AXk2At[1][0])

        if determinant != 0:
            AXk2At[0][0] = AXk2At[1][1] / determinant
            AXk2At[0][1] = -AXk2At[0][1] / determinant
            AXk2At[1][0] = -AXk2At[1][0] / determinant
            AXk2At[1][1] = AXk2At[0][0] / determinant

            print("Inverse of the matrix:")
            Mpr.matdisplay(AXk2At, m, n)
        else:
            print("The matrix is not invertible (determinant is zero).")

        print(
            "Now the matrix mu can be obtained by multplying the inverse of RHS with LHS i.e AX^2C * inverse of AXk^2")
        mu = Mpr.matmultiply(AXk2c, AXk2At, m, n)
        Mpr.matdisplay(mu, m, n)

        print("Obtaining the value of d= Xk * c - Xk * A^T * mu")
        print("Multiplication of Xk and c")
        Xkc = Mpr.matmultiply(Xk, c, m, n)
        Mpr.matdisplay(Xkc, m, n)
        print("Obtaining Xk * A^t")
        XkAt = Mpr.matmultiply(Xk, transA, m, n)
        Mpr.matdisplay(XkAt, m, n)
        print("Obtaining Xk * A^T * mu")
        XkAtmu = Mpr.matmultiply(XkAt, mu, m, n)
        Mpr.matdisplay(XkAtmu, m, n)
        d = Mpr.matsubtract(Xkc, XkAtmu, m, n)
        Mpr.matdisplay(d, m, n)


if __name__ == "__main__":
    Main.main()
