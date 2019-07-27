#include "xlattice.h"

using namespace std;


int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  Xlattice_init();



  MPI_Finalize();
}
