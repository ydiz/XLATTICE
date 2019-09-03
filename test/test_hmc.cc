#include <xlattice.h>

using namespace std;

int main(int argc, char **argv)
{
  init(argc, argv);

  // GaugeField U = 1.0;
  GaugeField U = readField("U_softly_fixed_4");

  WilsonAction action(6.0);
  std::cout << action.S(U) << std::endl;
  std::cout << action.deriv(U) << std::endl;

  return 0;
}
