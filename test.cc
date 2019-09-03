#include "xlattice.h"

using namespace std;

int main(int argc, char **argv)
{
  init(argc, argv);
  RealField rf = -9;
  cout << sum(rf);

  // string file= "U_softly_fixed_4";
  // GaugeField U;
  // U = readField(file);
  //
  // cout << linkTrace(U);
  // cout << plaq(U);

  // test cshift
  // Lattice<Vector<int, 4>> coor;
  // coor = coordinate(defaultLat());
  // cout << shiftF(coor, 2);


}
