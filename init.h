#ifndef XLATTICE_INIT_H
#define XLATTICE_INIT_H

// move to init.cc

// static std::vector<int> _defaultMPI {1,1,2,2};
static std::vector<int> _defaultMPI {1,1,1,1};
// static std::vector<int> _defaultLat {8,8,8,8};
static std::vector<int> _defaultLat {4,4,4,4};

std::vector<int> defaultMPI(){
  return _defaultMPI;
}

std::vector<int> defaultLat(){
  return _defaultLat;
}


void quiesce_node()
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(rank!=0) std::cout.clear(std::ios_base::badbit);
}

void unquiesce_node()
{
  std::cout.clear();
}


void init(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  quiesce_node();
}



#endif
