CC=g++
CFLAGS=-I.
DEPS = propagation/Propagation.h propagation/Tracklet.h propagation/PixelHit.h utils/Hits_input.h
OBJ = Reconstruction.o propagation/Propagation.o propagation/Tracklet.o propagation/PixelHit.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

voronoi_reconstruction: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean: 
	rm -f **/*.o
	