#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

//The mesh quantities
MatrixXi F;
MatrixXd V;

MatrixXd null(const MatrixXd& A){
  JacobiSVD<Matrix4d, ComputeThinU | ComputeThinV> svd(A);
  double threshold = 1e-10;
  Eigen::VectorXd singularValues = svd.singularValues();
  Eigen::MatrixXd V = svd.matrixV();
  Eigen::MatrixXd nullA = V.block(0, svd.rank(), V.rows(), V.cols() - svd.rank());
  return nullA;
  
}

int main()
{
  
  Matrix4d C;
  
  C.row(0) << -2.8, -1.5, -3.6, -1.7;
  C.row(1) << -1.85, -1.2, -1.61, -4.24;
  C.row(2) << 0.4 * C.row(0) + 0.23 * C.row(1);
  C.row(3) << -0.5 * C.row(0) + 0.2 * C.row(2);

  // LU Decomposition (not used)
  const FullPivLU<Matrix4d> LU(C);
  // const auto x = LU.solve(d);
  // cout << "x: [" << x << " ]\n";
  // cout << "norm of x: " << x.norm() << endl;

  cout << "Rank of C: " << LU.rank() << endl;

  Vector4d d;
  d(0) = 5;
  d(1) = -6;
  d(2) = 0.4 * d(0) + 0.23 * d(1);
  d(3) = -0.5 * d(0) + 0.2 * d(2);

  // SVD
  const JacobiSVD<Matrix4d, ComputeThinU | ComputeThinV> svd(C);
  const auto x0 = svd.solve(d);
  cout << "x0: [" << x0 << " ]\n";
  cout << "norm of x0: " << x0.norm() << "\n\n";

  auto solution_error = (C * x0 - d).cwiseAbs().maxCoeff();
  cout << "Solution Error: " << solution_error << endl;

  // Check solution
  const auto nullC = null(C);
  cout << "x0.transpose() * nullC: " << x0.transpose() * nullC << "\n\n";

  // Varying null space
  const vector alpha_list = {0.5, -0.3, -3.981};
  const vector beta_list = {0.5, 10.2, 6.1};
  for (int i = 0; i < alpha_list.size(); ++i) {
    const auto alpha = alpha_list[i];
    const auto beta = beta_list[i];

    Vector2d scale;
    scale << alpha, beta;

    const auto x = x0 + nullC * scale;
    solution_error = (C * x - d).cwiseAbs().maxCoeff();
    cout << "Solution error for (alpha, beta) = (" << alpha << ", " << beta << "): " << solution_error << endl;
  }
  cout << endl;

  // Trying out an incompatible RHS
  d(3) = 0.3945;
  const auto xe = svd.solve(d);
  solution_error = (C * xe - d).cwiseAbs().maxCoeff();
  cout << "C*xe - d error: " << solution_error << endl;
  cout << "C.transpose()*C*xe - C.transpose()*d error: " << (C.transpose() * C * xe - C.transpose() * d).cwiseAbs().maxCoeff() << endl;
}

