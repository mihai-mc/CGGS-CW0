#include "readOFF.h"
#include "harmonic_interpolation.h"
#include "create_edge_list.h"
#include "serialization.h"
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <random>

using namespace Eigen;
using namespace std;

//The mesh quantities
MatrixXi F, H, E;
VectorXi boundEMask;
MatrixXd V;
VectorXd x;

double tolerance = 1e-8;

namespace fs = std::filesystem;

int main()
{
  
  std::string folderPath(DATA_PATH); // Replace with your folder path
  for (const auto& entry : fs::directory_iterator(folderPath)) {
    if (entry.is_regular_file() && entry.path().extension() == ".off") {
      cout<<"Working on file "<<entry.path().filename()<<endl;
      std::string dataName = entry.path();
      dataName.erase(dataName.size() - 4, 4);
      std::ifstream ifs(dataName+"-section3.data", std::ofstream::binary);
      VectorXd fixedValues;
      VectorXi fixedIndices;
      readOFF(entry.path(), V, F);
      VectorXd xGT;
      deserializeVector(fixedIndices, ifs);
      deserializeVector(fixedValues, ifs);
      deserializeVector(xGT, ifs);
      ifs.close();
      
      create_edge_list(F, H, E, boundEMask);
      x = harmonic_interpolation(V, E, fixedIndices, fixedValues);
      
      //comparisons and feedback
      if ((x.rows()!=xGT.rows())||(x.cols()!=xGT.cols())){
        cout<<"x is of the wrong size!"<<endl;
        continue;
      }
      int row, col;
      double maxDiff = (x-xGT).cwiseAbs().maxCoeff(&row, &col);
      if (maxDiff>tolerance){
        cout<<"The difference between x and ground truth is "<<maxDiff<<" at ("<<row<<","<<col<<")"<<endl;
        continue;
      }
      
      cout<<"Result is good!"<<endl;
      
    }
  }
}

