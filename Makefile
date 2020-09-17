

main:
	gcc -g -Wall -fopenmp -o pi utilities.c quart_pi_estimation_parallel.c -lm

test:
	gcc -g -Wall -fopenmp -o runTests utilities.c runAllTests.c -lm

clean:
	rm pi runTests
