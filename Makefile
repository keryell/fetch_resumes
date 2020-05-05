world: fetch_talemetry_resumes

# To compile the modern C++ programs
CXX = clang++-11
CXXFLAGS = -std=c++2a -stdlib=libc++
LDLIBS += -lboost_system -lboost_filesystem -lpthread
