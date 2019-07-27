#ifndef XLATTICE_INIT_H
#define XLATTICE_INIT_H

// move to init.cc

static std::vector<int> _defaultMPI {1,1,2,2};
static std::vector<int> _defaultLat {8,8,8,8};
// static std::vector<int> _defaultLat {4,4,4,4};
static int _defaultLocalVol = 64;
static int _defaultGlobalVol = 256;

std::vector<int> defaultMPI(){
  return _defaultMPI;
}

std::vector<int> defaultLat(){
  return _defaultLat;
}

int defaultLocalVol(){
  return _defaultLocalVol;
}

int defaultGlobalVol(){
  return _defaultGlobalVol;
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


void Xlattice_init()
{
  quiesce_node();
}



#endif
