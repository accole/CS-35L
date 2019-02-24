Adam Cole

Assignment 6

README:

The SRT implementation traces the rays by performing calculations based
the colors off of spheres defined in the scene.

When first examining main.c, I notice the large amount of for loops
running in int main().  In order to parallelize the calculations as
much as possible, we want to pull this computation out of main() and
multithread the section.

My function definition was:
	void * pixelCalulation(void *pid) { ... }
which is pointer since I pass it into each thread creation to run.

At first, I tried to implement my multithreading function by passing in
parameters to communicate from the threads to main(), but ended up being
too complicated to eliminate race conditions and have main() output the
pixels in the correct order.

I used global variables in order to share information between the
multithreading function and the main function, which was only int nthreads,
the number of threads used to multithread, the scene, and a two dimensional
array of pixels.

I implement a pixel using a struct with three floats, since the printf
function call used in main() requires the three float colors.  

I modeled the creation and use of threads within the main() function after
the structure of the POSIX Wiki page given to us in the spec.  In this 
fashion, we create all the threads using a for loop, then repeat the process
and join all the threads until they finish, then finally print out each pixel
in order from the global array.

In the makefile, we must link the pthread library and I add -lpthread to the
LDLIBS line.  At first I was a little unsure where to add this, but Piazza
cleared it up for me.

Once finished with my additions, I test the edited program:

	$ make clean check

	time ./srt 1-test.ppm >1-test.ppm.tmp
	real	0m47.613s
	user	0m47.597s
	sys	0m0.002s
	mv 1-test.ppm.tmp 1-test.ppm

	time ./srt 2-test.ppm >2-test.ppm.tmp
	real	0m24.377s
	user	0m48.231s
	sys	0m0.003s
	mv 2-test.ppm.tmp 2-test.ppm

	time ./srt 4-test.ppm >4-test.ppm.tmp
	real	0m12.837s
	user	0m50.659s
	sys	0m0.002s
	mv 4-test.ppm.tmp 4-test.ppm

	time ./srt 8-test.ppm >8-test.ppm.tmp
	real	0m6.492s
	user	0m50.233s
	sys	0m0.004s
	mv 8-test.ppm.tmp 8-test.ppm

	for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
	  diff -u baseline.ppm $file || exit; \
	done

As we can see, the outputs using 1, 2, 4, and 8 threads output byte-for-byte
the same thing as the original, given by baseline.ppm.

Furthermore, the effects of parallelism are clearly demonstrated here.  As
each thread is added, the real time taken for the computation to run is
cut in half.  SEASNET servers can use up to 16 cores, therefore I run my own
test to examine if this trend continues.

	$ time ./srt 16-test.ppm >16-test.ppm.tmp
	real    0m6.280s
	user    1m28.845s
	sys     0m0.031s
	
The computation continues to get faster.  Uprgading from 8 threads to 16
threads saves the user only 0.212 seconds, so using more than 8 threads in this
example does not provide much benefit when taking the CPU overhead of using
16 threads into account.

