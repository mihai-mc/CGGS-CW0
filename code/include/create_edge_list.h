#ifndef CREATE_EDGE_LIST_HEADER_FILE
#define CREATE_EDGE_LIST_HEADER_FILE

#include <Eigen/Dense>
#include "unique.h"
#include "sort_rows.h"

void create_edge_list(const Eigen::MatrixXi& F,
                      Eigen::MatrixXi& H,
                      Eigen::MatrixXi& E,
                      Eigen::VectorXi& boundEMask){
  H.resize(0,2);  //halfedges
  E.resize(0,2);
  boundEMask.resize(0);
 
  // Compute halfedges
  H.resize(3 * F.rows(), 2);
  for (int y = 0; y < F.rows(); y++) {
      H.row(3 * y + 0) << F(y, 0), F(y, 1); // ij
      H.row(3 * y + 1) << F(y, 1), F(y, 2); // jk
      H.row(3 * y + 2) << F(y, 2), F(y, 0); // ki
  }

  // Get a sorted copy of H
  MatrixXi H_copy = H;
  sort_rows(H_copy);

  std::vector<int> uniqueIndices, counts, inverse;
  unique(H_copy, uniqueIndices, counts, inverse);

  E.resize(uniqueIndices.size(), 2);
  boundEMask.resize(E.rows());
  for (int i = 0; i < uniqueIndices.size(); i++) {
    E.row(i) = H_copy.row(uniqueIndices[i]);
    boundEMask[i] = counts[i] == 1 ? 1 : 0;
  }
}



#endif
