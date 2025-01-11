#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>
#include <polyscope/curve_network.h>
#include "unique.h"
#include "sort_rows.h"
#include "readOFF.h"
#include "create_edge_list.h"
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <set>
#include <array>

using namespace Eigen;
using namespace std;

//The mesh quantities
MatrixXi F;
MatrixXd V;
MatrixXi H, E;
VectorXi boundEMask;

int main()
{
  readOFF(DATA_PATH "/TrainStation.off",V, F);
  polyscope::init();
  polyscope::registerSurfaceMesh("mesh", V, F);
  create_edge_list(F, H, E, boundEMask);
  
  //Visualizing boundary edges
  vector<RowVector3d> boundNodes;
  vector<RowVector2i> boundEdges;
  
  for (int i=0;i<E.rows();i++){
    if (!boundEMask(i))
      continue;
    
    boundNodes.push_back(V.row(E(i,0)));
    boundNodes.push_back(V.row(E(i,1)));
    RowVector2i boundEdge; boundEdge<<boundNodes.size()-2, boundNodes.size()-1;
    boundEdges.push_back(boundEdge);
  }
  
  polyscope::registerCurveNetwork("boundary edges", boundNodes, boundEdges);
  polyscope::show();
  
}

