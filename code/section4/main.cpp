#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>
#include "readOFF.h"
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <set>
#include <array>

using namespace Eigen;
using namespace std;

//The mesh quantities
MatrixXi F;
MatrixXd origV, currV, displacement, velocity;
bool isAnimating = false;
polyscope::SurfaceMesh* pMesh;

double timeStep = 0.02; //assuming 50 fps


void callback_function() {
  ImGui::PushItemWidth(50);
  
  ImGui::TextUnformatted("Animation Parameters");
  ImGui::Separator();
  bool changed = ImGui::Checkbox("isAnimating", &isAnimating);
  ImGui::PopItemWidth();
  if (!isAnimating)
    return;
  
  
  //TODO
  
  pMesh->updateVertexPositions(currV);
}


int main()
{
  readOFF(DATA_PATH "/spherers.off",origV, F);
  polyscope::init();
  
  currV = origV;
  velocity = MatrixXd::Zero(origV.rows(),3);
  RowVector3d origDisplacement; origDisplacement<<0.0,2.0,0.0;
  displacement = origDisplacement.replicate(origV.rows(),1);
  currV  = origV + displacement;
  
  // Visualization
  pMesh = polyscope::registerSurfaceMesh("mesh", currV, F);
  polyscope::state::lengthScale = 1.;
  //polyscope::state::boundingBox =
  //    std::tuple<glm::vec3, glm::vec3>{ {-5., 0., -5.}, {5., 5., 5.} };
  
  polyscope::options::groundPlaneHeightMode = polyscope::GroundPlaneHeightMode::Manual;
  polyscope::options::groundPlaneHeight = 0.; // in world coordinates along the up axis
  polyscope::state::userCallback = callback_function;
  
  polyscope::show();
  
}

