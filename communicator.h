// usually use cartComm
class Communicator{
public:
  static MPI_Comm worldComm;
  static int worldRank;
  static int worldSize; // this one is needed, should not be deleted.

  static MPI_Comm shmComm;
  static int shmRank;
  static int shmSize;

  static int Nnodes; // number of nodes
  static std::string node;

  static int isShmLeader; //didn't use bool; need to sum over isShmLeader to get Nnodes.
  static int isWorldLeader;

  // in Grid, processors should actually be processes. _ldimensions[d] = _gdimensions[d] / _processors[d];
  static MPI_Comm cartComm;
  static int cartRank;  //FIXME: redundant; cartRank == worldRank
  static int _ndims;
  static std::vector<int> _processes_grid;
  static std::vector<int> _process_coor;
  // static int cartRank;
  Communicator(const std::vector<int> &processes_grid);
  int rankFromProcessCoor(const std::vector<int> &process_coor) const;
  std::vector<int> processCoorFromRank(int rank) const;

  template<typename T>
  typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type Bcast(int root, T &data) const;
  template<typename T> void Bcast(int root, std::vector<T> &data) const;

  template<typename T> T sumMPI(T x) const;
};

template<typename T>
T Communicator::sumMPI(T x) const
{
  T ret;
  MPI_Allreduce(&x, &ret, 1, MPI_Type<T>::value, MPI_SUM, cartComm);
  return ret;
}


Communicator::Communicator(const std::vector<int> &processes_grid)
{
  worldComm = MPI_COMM_WORLD;  // ? each process has its own copy of worldComm; Is this what it should be?
  MPI_Comm_rank(worldComm, &worldRank);
  MPI_Comm_size(worldComm, &worldSize);

  MPI_Comm_split_type(worldComm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, &shmComm);
  MPI_Comm_rank(shmComm, &shmRank);
  MPI_Comm_size(shmComm, &shmSize);

  isWorldLeader = (worldRank == 0);
  isShmLeader = (shmRank == 0);
  // Nnodes; number of nodes
  MPI_Allreduce(&isShmLeader, &Nnodes, 1, MPI_INT, MPI_SUM, worldComm);

  // node; name of node // p.s. Grid use leader_xxx to assign a number to node
  int nodeNameLen=0;
  char nodeName[MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(nodeName, &nodeNameLen);
  node = std::string(nodeName, nodeName+nodeNameLen);

  //FIXME: don't understand: before doing this, Grid re-ranked worldComm in OptimalCommunicator. WorldCoor[d] = NodeCoor[d]*ShmDims[d]+ShmCoor[d];
  // Grid: //OptimalCommunicator: Turns MPI_COMM_WORLD into right layout for Cartesian; Create an optimal reordered communicator that makes MPI_Cart_create get it right
  _ndims = processes_grid.size();
  _processes_grid = processes_grid;
  MPI_Cart_create(worldComm, _ndims, _processes_grid.data(), std::vector<int>(_ndims,1).data(), 0, &cartComm); // "0" indicates no re-ordering
  MPI_Comm_rank(cartComm, &cartRank);

  _process_coor.resize(_ndims); // !!! this is necessary
  MPI_Cart_coords(cartComm, worldRank, _ndims, _process_coor.data());
}

inline int Communicator::rankFromProcessCoor(const std::vector<int> &process_coor) const
{
  int rank;
  MPI_Cart_rank(cartComm, process_coor.data(), &rank);
  return rank;
}

inline std::vector<int> Communicator::processCoorFromRank(int rank) const
{
  std::vector<int> process_coor(_ndims);
  MPI_Cart_coords(cartComm, rank, _ndims, process_coor.data());
  return process_coor;
}

template<typename T>
typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type
Communicator::Bcast(int root, T &data) const {
  MPI_Bcast(&data, sizeof(data), MPI_BYTE, root, cartComm); // ? (void *)&data is unnecessary
}

template<typename T>
inline void Communicator::Bcast(int root, std::vector<T> &data) const {
  MPI_Bcast(data.data(), data.size() * sizeof(T), MPI_BYTE, root, cartComm);
}

// template<typename T>
// typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type
// Communicator::Isend(int root, T &data) const
// {
//
// }



std::ostream& operator<<(std::ostream& out, const Communicator &comm)
{
  std::cout << "worldRank " << comm.worldRank << " of " << comm.worldSize << " running on " << comm.node
        << "; shmRank " << comm.shmRank << " of " << comm.shmSize << "; coor " << comm._process_coor << std::endl;
  // if(comm.isWorldLeader) std::cout << "there are " << comm.Nnodes << " nodes in all" << std::endl;
  return out;
}

// static variables
MPI_Comm Communicator::worldComm;
int Communicator::worldRank;
int Communicator::worldSize;

MPI_Comm Communicator::shmComm;
int Communicator::shmRank;
int Communicator::shmSize;

int Communicator::Nnodes;
std::string Communicator::node;

int Communicator::isShmLeader;
int Communicator::isWorldLeader;

MPI_Comm Communicator::cartComm;
int Communicator::_ndims;
int Communicator::cartRank;
std::vector<int> Communicator::_processes_grid;
std::vector<int> Communicator::_process_coor;
