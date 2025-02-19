#ifndef COMPUTE_AREAS_NORMALS_HEADER_FILE
#define COMPUTE_AREAS_NORMALS_HEADER_FILE

#include <Eigen/Dense>

void compute_areas_normals(const Eigen::MatrixXd& V,
                          const Eigen::MatrixXi& F,
                          Eigen::VectorXd& areas,
                          Eigen::MatrixXd& normals){
  using namespace Eigen;
  areas.resize(F.rows());
  normals.resize(F.rows(),3);

  for (int y = 0; y < F.rows(); y++) {
    // Get indices for vertices
    const int idx_v0 = F(y,0);
    const int idx_v1 = F(y,1);
    const int idx_v2 = F(y,2);

    // Get vertices
    const auto v0 = (RowVector3d)V.row(idx_v0).reshaped();
    const auto v1 = (RowVector3d)V.row(idx_v1).reshaped();
    const auto v2 = (RowVector3d)V.row(idx_v2).reshaped();

    // Compute unnormalised norm and its magnitude
    const auto unnormalised_norm = (v1 - v0).cross( v2 - v0);
    const auto magnitude = unnormalised_norm.norm();

    normals.row(y) = unnormalised_norm / magnitude;
    areas(y) = 0.5 * magnitude;
  }
}


#endif
