CXX = C:/TDM-GCC-32/bin/g++.exe

TARGET = main.exe

SRC = main.cpp

CXXFLAGS = -IC:/TDM-GCC-32/include
LDFLAGS  = -LC:/TDM-GCC-32/lib -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	del /Q $(TARGET)