#include <Grid/Grid.h>
// #include "xlattice.h"

using namespace std;

int main(int argc, char **argv)
{
  Grid::Grid_init(&argc, &argv);
  std::vector<int> latt({8,8,8,8});
  std::vector<int> mpi({1,1,2,2});

  // Grid::GridCartesian * grid =  Grid::QCD::SpaceTimeGrid::makeFourDimGrid(latt,
  // 						Grid::GridDefaultSimd(Nd,Grid::vComplex::Nsimd()),
  // 						Grid::GridDefaultMpi());
  Grid::GridCartesian * grid =  Grid::QCD::SpaceTimeGrid::makeFourDimGrid(latt,
  						Grid::GridDefaultSimd(4,Grid::vComplex::Nsimd()),
  						mpi);

  // // Grid_LatticeGaugeField  U(grid);
  // Grid::QCD::LatticeGaugeField U(grid);
  //
  //
  // Grid::FieldMetaData header;
  // std::string file("./U_softly_fixed_4");
  // Grid::QCD::NerscIO::readConfiguration(U, header,file);
  // cout << U ;


  std::vector<int> v;
  grid.Broadcast(0, v);
  // Lattice<Matrix3> latm(grid);
  // latm = 3.0;
  // cout << Grid_LatticeColourMatrix(latm) << endl;



}
