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
 
  //TODO
}



#endif
