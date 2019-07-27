#include "xlattice.h"

using namespace std;

int main(int argc, char **argv)
{
  // default_grid = {4,4,4,4};
  // default_grid_vol = 1;
  for(auto x: default_grid) default_grid_vol *= x;

  string file= "U_softly_fixed_4";
  GaugeField U;
  U = readField(file);
//
  cout << linkTrace(U);
  cout << plaq(U);
//
  test cshift
  Lattice<Vector<int, 4>> coor;
  // coor = coordinate(defaultLat());
  // cout << shiftF(coor, 2);


}
