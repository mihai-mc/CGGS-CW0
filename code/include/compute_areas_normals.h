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
  
  //TODO
}


#endif
