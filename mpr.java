import java.util.*;
public class mpr{
    public static int[][] matread(int m,int n)
    {   Scanner sc = new Scanner(System.in);

        int [][] a= new int[m][n];
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                a[i][j]= sc.nextInt();
            }
        }
        return a;



    }
    public static int[][] matdisplay(int [][] a,int m,int n)
    {

        int i,j;
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                System.out.printf("%d\t",a[i][j]);
            }
            System.out.println("\n");
        }
        return a;
    }
    public static int[][] transpose(int a[][],int m, int n)
    {
        int [][] b= new int[m][n];
        int i,j;
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                b[j][i]=a[i][j];
            }

        }
        return b;
    }
    public static int[][] diagonal(int m, int n)
    {
        Scanner sc= new Scanner(System.in);
        int [][] a = new int[m][n];
        int i,j;

        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i==j)
                {
                    a[i][j]=sc.nextInt();
                }
                else{
                    a[i][j]=0;
                }
            }

        }
        return a;
    }
    public static int[][] matsubtract(int[][] a, int [][] b, int m , int n)
    {
        int i,j;
        int [][] c= new int[m][n];
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                c[i][j]=a[i][j]-b[i][j];
            }
        }
        return c;

    }
    public static int[][] matmultiply(int[][] a, int[][] b,int m, int n)
    {
        Scanner sc = new Scanner(System.in);
        int [][] c = new int[m][n];
        int i,j,k;
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                for(k=0;k<n;k++)
                {
                    c[i][j]+=a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }

    public static void main(String args[])
    {
        int determinant;
        Scanner sc= new Scanner(System.in);
        System.out.println("Consider the problem statement:\n Min: 1/2(Xk * c-d)^2\n Subject to A *Xk * d ");

        System.out.println(" Enter the number of Rows:");
        int m=sc.nextInt();
        System.out.println("Enter the number of Columns:");
        int n=sc.nextInt();

        int [][] A= new int[m][n];
        int [][] Xk= new int[m][n];
        int [][] transA = new int[m][n];
        int [][] c= new int[m][n];
        int [][] Xkc=new int[m][n];
        int [][] Xk2=new int[m][n];
        int [][] AXk2= new int[m][n];
        int [][] AXk2c= new int[m][n];
        int [][] AXk2At= new int [m][n];
        int [][] mu= new int [m][n];
        int [][] XkAt= new int[m][n];
        int [][] XkAtmu= new int[m][n];
        int [][] d= new int[m][n];
        System.out.println("Enter the matrix A:\n");
        A=matread(m,n);
        matdisplay(A,m,n);
        System.out.println("transpose of A is :");
        transA=transpose(A,m,n);
        matdisplay(transA,m,n);
        System.out.println("Enter the matrix c:\n");
        c=matread(m,n);
        matdisplay(c,m,n);

        System.out.println("Enter the diagonal matrix Xk:\n");
        Xk=diagonal(m,n);
        matdisplay(Xk,m,n);
        System.out.println("In order to solve the problem we find the lagrangian of the equation consisting of 2 parameters(d and mu) to determine the minimum value\n");
        System.out.println("Therefore L(d,mu)= 1/2(XK * c - d)^2 + mu^T (A * Xk * d)");
        System.out.println("In order to obtain the gradient, we must differentiate the problem with respect to d\n The gradient= Zero");
        System.out.println(" We get: -(Xk * c- d) + Xk * A^T * mu");
        System.out.println("Thus d = Xk * c - Xk * A^T * mu\n However we need to obtain the value of mu first\n");


        System.out.println("To obtain mu multiplying A on both sides, on doing so we get \n A * Xk^2 * c = A * Xk^2 * AT * mu");
        System.out.println("Obtaining Xk^2\n");
        Xk2=matmultiply(Xk,Xk,m,n);
        matdisplay(Xk2,m,n);
        System.out.println("Solving the LHS");
        System.out.println("A * Xk2 is:\n");
        AXk2=matmultiply(A,Xk2,m,n);
        matdisplay(AXk2,m,n);
        System.out.println("AXk2 * c will give us the solution of the LHS:\n ");
        AXk2c=matmultiply(AXk2,c,m,n);
        System.out.println("The LHS is : \n");
        matdisplay(AXk2c,m,n);
        System.out.println("Solving the RHS:\n Since we have obtained the product of AXk2 already, the required answer can be obtained by multiplying it with AT");
        AXk2At=matmultiply(AXk2,transA,m,n);
        matdisplay(AXk2At,m,n);
        System.out.printf("The elements of AXk2At are %d %d %d %d ",AXk2At[0][0],AXk2At[0][1],AXk2At[1][0],AXk2At[1][1]);
        determinant = (AXk2At[0][0] * AXk2At[1][1]) - (AXk2At[0][1] * AXk2At[1][0]);

        if (determinant != 0) {

            AXk2At[0][0] = AXk2At[1][1] / determinant;
            AXk2At[0][1] = -AXk2At[0][1] / determinant;
            AXk2At[1][0] = -AXk2At[1][0] / determinant;
            AXk2At[1][1] = AXk2At[0][0] / determinant;


            System.out.println("Inverse of the matrix:");
            for(int i=0;i<m;i++)
            {
                for(int j=0;j<n;j++)
                {
                    System.out.printf("%d\t",AXk2At[i][j]);
                }
                System.out.println("\n");
            }
        } else {
            System.out.println("The matrix is not invertible (determinant is zero).");
        }
        System.out.println("Now the matrix mu can be obtained by multplying the inverse of RHS with LHS i.e AX^2C * inverse of AXk^2");
        mu=matmultiply(AXk2c,AXk2At,m,n);
        matdisplay(mu,m,n);
        System.out.println("Obtaining the valueo of d= Xk * c - Xk * A^T * mu");
        System.out.println("Multiplication of Xk and c");
        Xkc= matmultiply(Xk,c,m,n);
        matdisplay(Xkc,m,n);
        System.out.println("Obtaining Xk * A^t");
        XkAt=matmultiply(Xk,transA,m,n);
        matdisplay(XkAt,m,n);
        System.out.println("Obtaining Xk * A^T * mu");
        XkAtmu=matmultiply(XkAt,mu,m,n);
        matdisplay(XkAtmu,m,n);
        System.out.println("Now d = Xk * c- Xk * A^T * mu");
        d=matsubtract(Xkc,XkAtmu,m,n);
        matdisplay(d,m,n);

    }
}