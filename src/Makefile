KERNEL = kernel.elf

CXX = g++
LD = ld

CXXFLAGS = -Wall -Wextra -O2 -pipe -std=c++20  -mno-red-zone\
           -fno-rtti -fno-exceptions -ffreestanding -fno-threadsafe-statics -fpermissive -fno-stack-protector \
           -fno-omit-frame-pointer -l -I.

LDFLAGS = -nostdlib -nostartfiles -z max-page-size=0x1000 -T linker.ld

CXXFILES := $(shell find ./ -type f -name '*.cpp')
OBJ    := $(CXXFILES:.cpp=.o)

.PHONY: all clean

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(KERNEL) $(OBJ)