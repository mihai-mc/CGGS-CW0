#ifndef HARMONIC_INTERPOLATION_HEADER_FILE
#define HARMONIC_INTERPOLATION_HEADER_FILE

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "set_diff.h"
#include "slice_columns_sparse.h"

Eigen::VectorXd harmonic_interpolation(const Eigen::MatrixXd& V,
                                       const Eigen::MatrixXi& E,
                                       const Eigen::VectorXi& B,
                                       const Eigen::VectorXd& xB){
  
  //TODO
  return Eigen::VectorXd::Zero(V.rows());
  
  
}


#endif
