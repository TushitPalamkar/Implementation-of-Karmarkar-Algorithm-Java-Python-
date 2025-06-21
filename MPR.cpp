#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matread(int m, int n) {
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    return a;
}

vector<vector<int>> matdisplay(const vector<vector<int>>& a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", a[i][j]);
        }
        cout << "\n" << endl;
    }
    return a;
}

vector<vector<int>> transpose(const vector<vector<int>>& a, int m, int n) {
    vector<vector<int>> b(n, vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            b[j][i] = a[i][j];
        }
    }
    return b;
}

vector<vector<int>> diagonal(int m, int n) {
    vector<vector<int>> a(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cin >> a[i][j];
            }
        }
    }
    return a;
}

vector<vector<int>> matsubtract(const vector<vector<int>>& a, const vector<vector<int>>& b, int m, int n) {
    vector<vector<int>> c(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

vector<vector<int>> matmultiply(const vector<vector<int>>& a, const vector<vector<int>>& b, int m, int n) {
    vector<vector<int>> c(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

vector<vector<int>> project_to_null_space(const vector<vector<int>>& d, int m, int n) {
    // Create a matrix of all ones
    vector<vector<int>> ones(m, vector<int>(n, 1));
    
    // Calculate the sum of all elements in d
    int onetd = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            onetd += d[i][j];
        }
    }
    
    // Scaling factor calculation
    int onetone = 2; // This seems to be a constant in the Python code
    double scalingfactor = static_cast<double>(onetd) / onetone;
    
    // Create scaling matrix
    vector<vector<int>> scalematrix(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scalematrix[i][j] = static_cast<int>(scalingfactor * ones[i][j]);
        }
    }
    
    // Project d onto null space of 1^T
    vector<vector<int>> dproj = d;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            while (dproj[i][j] < 0) {
                dproj = matsubtract(dproj, scalematrix, m, n);
            }
        }
    }
    
    return dproj;
}

vector<vector<int>> calculate_objective(const vector<vector<int>>& Xk, 
                                       const vector<vector<int>>& C, 
                                       const vector<vector<int>>& dproj, 
                                       int m, int n) {
    // Calculate Xk * dproj
    vector<vector<int>> xkd = matmultiply(Xk, dproj, m, n);
    
    // Calculate transpose of C
    vector<vector<int>> transC = transpose(C, m, n);
    
    // Calculate objective function value
    return matmultiply(transC, xkd, m, n);
}

int main() {
    int determinant;
    cout << "Consider the problem statement:\n Min: 1/2(Xk * c-d)^2\n Subject to A *Xk * d = 0 " << endl;

    cout << " Enter the number of Rows:" << endl;
    int m;
    cin >> m;
    
    cout << "Enter the number of Columns:" << endl;
    int n;
    cin >> n;

    vector<vector<int>> A(m, vector<int>(n));
    vector<vector<int>> Xk(m, vector<int>(n));
    vector<vector<int>> transA(m, vector<int>(n));
    vector<vector<int>> c(m, vector<int>(n));
    vector<vector<int>> Xkc(m, vector<int>(n));
    vector<vector<int>> Xk2(m, vector<int>(n));
    vector<vector<int>> AXk2(m, vector<int>(n));
    vector<vector<int>> AXk2c(m, vector<int>(n));
    vector<vector<int>> AXk2At(m, vector<int>(n));
    vector<vector<int>> mu(m, vector<int>(n));
    vector<vector<int>> XkAt(m, vector<int>(n));
    vector<vector<int>> XkAtmu(m, vector<int>(n));
    vector<vector<int>> d(m, vector<int>(n));
    
    cout << "Enter the matrix A:\n" << endl;
    A = matread(m, n);
    matdisplay(A, m, n);
    
    cout << "transpose of A is :" << endl;
    transA = transpose(A, m, n);
    matdisplay(transA, m, n);
    
    cout << "Enter the matrix c:\n" << endl;
    c = matread(m, n);
    matdisplay(c, m, n);

    cout << "Enter the diagonal matrix Xk:\n" << endl;
    Xk = diagonal(m, n);
    matdisplay(Xk, m, n);
    
    cout << "In order to solve the problem we find the lagrangian of the equation consisting of 2 parameters(d and mu) to determine the minimum value\n" << endl;
    cout << "Therefore L(d,mu)= 1/2(XK * c - d)^2 + mu^T *A * Xk * d" << endl;
    cout << "In order to obtain the gradient, we must differentiate the problem with respect to d\n The gradient= Zero" << endl;
    cout << " We get: -(Xk * c- d) + Xk * A^T * mu = 0" << endl;
    cout << "Thus d = Xk * c - Xk * A^T * mu\n However we need to obtain the value of mu first\n" << endl;
    cout << "Multiplying A * Xk on both sides as d should satisfy the feasibility" << endl;
    cout << "A * Xk *d = A * Xk^2 * c - A * Xk * A^T * mu\n " << endl;
    cout << "Therefore A * Xk^2 * c = A * Xk^2 * A^T * mu\n" << endl;
    cout << "Obtaining Xk^2\n" << endl;
    
    Xk2 = matmultiply(Xk, Xk, m, n);
    matdisplay(Xk2, m, n);
    
    cout << "Solving the LHS" << endl;
    cout << "A * Xk2 is:\n" << endl;
    AXk2 = matmultiply(A, Xk2, m, n);
    matdisplay(AXk2, m, n);
    
    cout << "AXk2 * c will give us the solution of the LHS:\n " << endl;
    AXk2c = matmultiply(AXk2, c, m, n);
    cout << "The LHS is : \n" << endl;
    matdisplay(AXk2c, m, n);
    
    cout << "Solving the RHS:\n Since we have obtained the product of AXk2 already, the required answer can be obtained by multiplying it with AT" << endl;
    AXk2At = matmultiply(AXk2, transA, m, n);
    matdisplay(AXk2At, m, n);
    
    printf("The elements of AXk2At are %d %d %d %d\n ", AXk2At[0][0], AXk2At[0][1], AXk2At[1][0], AXk2At[1][1]);
    determinant = (AXk2At[0][0] * AXk2At[1][1]) - (AXk2At[0][1] * AXk2At[1][0]);

    if (determinant != 0) {
        AXk2At[0][0] = AXk2At[1][1] / determinant;
        AXk2At[0][1] = -AXk2At[0][1] / determinant;
        AXk2At[1][0] = -AXk2At[1][0] / determinant;
        AXk2At[1][1] = AXk2At[0][0] / determinant;

        cout << "Inverse of the matrix:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d\t", AXk2At[i][j]);
            }
            cout << "\n" << endl;
        }
        
        cout << "Now the matrix mu can be obtained by multplying the inverse of RHS with LHS i.e AX^2C * inverse of AXk^2" << endl;
        mu = matmultiply(AXk2c, AXk2At, m, n);
        matdisplay(mu, m, n);
        
        cout << "Obtaining the valueo of d= Xk * c - Xk * A^T * mu" << endl;
        cout << "Multiplication of Xk and c" << endl;
        Xkc = matmultiply(Xk, c, m, n);
        matdisplay(Xkc, m, n);
        
        cout << "Obtaining Xk * A^t" << endl;
        XkAt = matmultiply(Xk, transA, m, n);
        matdisplay(XkAt, m, n);
        
        cout << "Obtaining Xk * A^T * mu" << endl;
        XkAtmu = matmultiply(XkAt, mu, m, n);
        matdisplay(XkAtmu, m, n);
        
        cout << "Now d = Xk * c- Xk * A^T * mu" << endl;
        d = matsubtract(Xkc, XkAtmu, m, n);
        matdisplay(d, m, n);
        
        // Add this after calculating d
        cout << "Projecting d onto the null space of 1^T..." << endl;
        vector<vector<int>> dproj = project_to_null_space(d, m, n);
        cout << "Projected d:" << endl;
        matdisplay(dproj, m, n);

        cout << "Calculating objective function value..." << endl;
        vector<vector<int>> objFunc = calculate_objective(Xk, c, dproj, m, n);
        cout << "Objective function value:" << endl;
        matdisplay(objFunc, m, n);
    } else {
        cout << "The matrix is not invertible (determinant is zero)." << endl;
    }
    
    return 0;
}
