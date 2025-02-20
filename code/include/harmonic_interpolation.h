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

  // Construct differential matrix d0
  std::vector<Eigen::Triplet<double>> triplets(E.rows() * 2); // COO format
  for (int ei = 0; ei < E.rows(); ei++) {
    triplets[2 * ei] = {ei, E(ei, 0), -1.0}; // (ei, source(ei), -1)
    triplets[2 * ei + 1] = {ei, E(ei, 1), +1.0}; // (ei, target(ei), +1)
  }
  Eigen::SparseMatrix<double> d0(E.rows(), V.rows());
  d0.setFromTriplets(triplets.begin(), triplets.end());

  // Compute I as the complement of B
  Eigen::VectorXi I = set_diff(Eigen::VectorXi::LinSpaced(V.rows(), 0, V.rows() - 1), B);

  // Slice sparse matrices
  Eigen::SparseMatrix<double> d0I = slice_columns_sparse(d0, I);
  Eigen::SparseMatrix<double> d0B = slice_columns_sparse(d0, B);

  // Construct LHS and RHS of the equation
  Eigen::VectorXd rhs = -1.0 * d0I.transpose() * d0B * xB;
  Eigen::SparseMatrix<double> lhs = d0I.transpose() * d0I;

  // Solver for xI
  Eigen::SimplicialLDLT solver(lhs);
  Eigen::VectorXd xI = solver.solve(rhs);

  // Combine xI and xB into the final results
  Eigen::VectorXd x(V.rows());
  for (int i = 0; i < B.rows(); i++)
    x(B(i)) = xB(i); // fixed points
  for (int i = 0; i < I.rows(); i++)
    x(I(i)) = xI(i); // interpolated points

  return x;
}


#endif
