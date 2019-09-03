# for hadron, add -fpermissive to CXXFLAGS

CXX = mpicxx

# CXXFLAGS = -I/home/ydzhao/cuth/install/boost/include -I/home/ydzhao/cuth/install/Grid/include -I/home/ydzhao/cuth/install/openmpi-3.1.0/include -I/home/ydzhao/cuth/install/hdf5-1.8.20/include -I/home/ydzhao/cuth/install/LIME/include -I/home/ydzhao/cuth/install/fftw-3.3.8/include -fopenmp -O3 -std=c++11
CXXFLAGS = -I/home/ydzhao/cuth/XLATTICE -I/home/ydzhao/cuth/install/boost/include -I/home/ydzhao/cuth/install/Grid/include -I/home/ydzhao/cuth/install/openmpi-3.1.0/include -I/home/ydzhao/cuth/install/hdf5-1.8.20/include -I/home/ydzhao/cuth/install/LIME/include -I/home/ydzhao/cuth/install/fftw-3.3.8/include -fopenmp -std=c++17

LDFLAGS = -L/home/ydzhao/cuth/install/boost/lib -L/home/ydzhao/cuth/install/Grid/lib -L/home/ydzhao/cuth/install/openmpi-3.1.0/lib -Wl,-rpath -Wl,/home/ydzhao/cuth/install/openmpi-3.1.0/lib -L/home/ydzhao/cuth/install/hdf5-1.8.20/lib -L/home/ydzhao/cuth/install/LIME/lib -L/home/ydzhao/cuth/install/fftw-3.3.8/lib -fopenmp

LIBS = -lboost_program_options -lGrid -lmpi_cxx -lmpi -Wl,-rpath -Wl,/home/ydzhao/cuth/install/openmpi-3.1.0/lib  -lhdf5_cpp -lz -lcrypto -llime -lfftw3f -lfftw3 -lmpfr -lgmp -lstdc++ -lm -lrt -lz -lhdf5

# TARGET = test
# TARGET = test_mpi
# TARGET = test_cshift
TARGET = test_hmc
# TARGET = test_grid

$(TARGET): FORCE
	$(CXX) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).cc
	$(CXX) $(LDFLAGS) -o $@ $(TARGET).o $(LIBS)
    
clean:
	-rm *.o

.PHONY: FORCE
