# ------------------------------

HIPCC    = hipcc
HIPFLAGS = --offload-arch=gfx90a

# ------------------------------

diffusion: main.o diffusion.o diffusion_kernel.o
	${HIPCC} ${HIPFLAGS} main.o diffusion.o diffusion_kernel.o -o diffusion

main.o: main.cpp
	${HIPCC} ${HIPFLAGS} -c main.cpp

diffusion.o: diffusion.cpp
	${HIPCC} ${HIPFLAGS} -c diffusion.cpp

diffusion_kernel.o: diffusion_kernel.hip
	${HIPCC} ${HIPFLAGS} -c diffusion_kernel.hip


.PHONY: clean

clean:
	rm -f diffusion *.o
