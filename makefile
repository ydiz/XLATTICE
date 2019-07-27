CC = clang++
CXX = clang++

CXXFLAGS = -mavx -mf16c -std=c++11 -Wall -O3 -MT GF_heatbath.o -DHAVE_CONFIG_H -I. -I/home/yz/Grid/include -I/usr/lib/x86_64-linux-gnu/include

#-fopenmp=libomp

#LINK.o = $(CXX) $(LDFLAGS)
LDFLAGS = -mavx -mf16c -std=c++11 -O3 -I. -I/home/yz/Grid/include -I/usr/lib/x86_64-linux-gnu/include
#-fopenmp=libomp
#LDFLAGS = -mavx -mf16c -fopenmp  -O3  -std=c++11
LDLIBS = -lGrid -lz -lmpfr -lgmp -lstdc++ -lm  -lz


test_grid: test_grid.o
	clang++ -g -I/home/yz/Grid/include -I/usr/lib/x86_64-linux-gnu/include -mavx -mf16c  -O3 -std=c++11 -L/home/yz/Grid/lib -L/usr/lib/x86_64-linux-gnu/lib  -o test_grid test_grid.o -lGrid -lnuma -lz -lfftw3f -lfftw3 -lmpfr -lgmp -lstdc++ -lm  -lz -lnuma

test_grid.o: test_grid.cc
	clang++ -g -DHAVE_CONFIG_H -I.    -I/home/yz/Grid/include -I/usr/lib/x86_64-linux-gnu/include -mavx -mf16c -O3 -std=c++11 -MT test_grid.o  -c -o test_grid.o test_grid.cc


clean:
	- rm *.o
