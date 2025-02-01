
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

//The mesh quantities
MatrixXi F;
MatrixXd V;

int main()
{
    Matrix3d A;
    Vector3d b;

    A << -12, -10.8, -13.4, -18.6, -12.1, -19.6, -15.8, -10.4, -11.5;
    b << -0.4, -0.6, -1.4;

    const FullPivLU<Matrix3d>  LU(A);
    const auto x = LU.solve(b);
    cout << "x = [" << x << " ]\n";

    const auto solution_error = (A * x - b).cwiseAbs().maxCoeff();

    cout << "Rank of A: " << LU.rank() << endl;
    cout << "Solution Error: " << solution_error << endl;
}

