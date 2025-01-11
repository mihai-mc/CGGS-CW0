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
  
  //TODO
}

