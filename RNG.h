#ifndef XLATTICE_RNG_H
#define XLATTICE_RNG_H

//two ways to call RNG: 1. rng(); 2. rng.rand()
template<typename DIST>
class RNG {
  std::default_random_engine eng;
  DIST dist;
public:
  using result_type = typename DIST::result_type;

  std::function<result_type()> rand; // not necessary; identical to operator()

  template<class... T> RNG(T... args);
  result_type operator()();

  void fill(Lattice<result_type> &lat);
};

// constructor
template<typename DIST>
template<class... T>
RNG<DIST>::RNG(T... args) : dist(args...)
{
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  eng.seed(seed);
  rand = [this]{return dist(eng);};  //"this" can only be captured by copy, i.e. [this] or [=]
}

// operator()
template<typename DIST>
inline typename DIST::result_type RNG<DIST>::operator()()
{
  return dist(eng);
}

template<typename DIST>
void RNG<DIST>::fill(Lattice<result_type> &lat)
{
  std::generate(lat._data.begin(), lat._data.end(), rand);
}

// even if return LatticeMatrix, still need to pass grid as argument.
void gaussian(LatticeMatrix &ret)
{
  su3_generator ss;
  RNG<std::normal_distribution<>> rng;
  LatticeReal lat(ret.grid);
  ret = 0.0;
  for(int i=0; i<8; ++i)
  {
    rng.fill(lat);
    ret += lat * ss.ti[i];
  }
}

void gaussian(GaugeField &ret)
{
  for(auto &x: ret._data) gaussian(x);
}

#endif
