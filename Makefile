# Specify object files
obj-m += ldd.o

# Default target
all: 
	@echo "Building the kernel module..."
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Clean target
clean:
	@echo "Cleaning up module..."
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

.PHONY: all clean
