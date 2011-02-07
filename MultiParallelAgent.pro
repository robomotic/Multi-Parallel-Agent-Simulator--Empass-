CONFIG += console
SOURCES += Main.cpp \
    Controllers/IcoSiso.cpp \
    Filters/LowPassFilter.cpp \
    World/Coordinate2D.cpp \
    Agents/DiskAgent.cpp \
    World/Steppable.cpp \
    World/World2DCartesian.cpp \
    World/velocityvector2d.cpp \
    World/geometry/RectangularBox.cpp \
    World/geometry/CircularBox.cpp \
    Logger/CSVExporter.cpp \
    World/simparameters.cpp
HEADERS += LowPassFilter.h \
    Controllers/IcoSiso.h \
    Filters/LowPassFilter.h \
    World/Coordinate2D.h \
    Agents/DiskAgent.h \
    World/Steppable.h \
    World/World2DCartesian.h \
    Test/TestRoutines.h \
    Entropy/SampleSetWriter.h \
    Entropy/SampleSetReader.h \
    Entropy/Entropy.h \
    Entropy/AleatoryVariable.h \
    Entropy/include/Entropy.h \
    Entropy/include/AleatoryVariable.h \
    Entropy/include/JointVariable.h \
    Logger/CSVDatabase.h \
    Entropy/include/Histogram.h \
    MatrixUtil/MatrixOperations.h \
    Logger/CSVExporter.h \
    World/velocityvector2d.h \
    World/geometry/RectangularBox.h \
    World/geometry/CircularBox.h \
    World/simparameters.h
LIBS += -fopenmp \
    -lm \
    -lboost_iostreams-mt
QMAKE_CXXFLAGS += -fopenmp \
    -lm \
    -Wall \
    -Wextra
INCLUDEPATH += /usr/local/include/gnuplot-iostream/
INCLUDEPATH += /usr/include/boost/iostreams
INCLUDEPATH += /usr/include/boost/numeric/ublas/
