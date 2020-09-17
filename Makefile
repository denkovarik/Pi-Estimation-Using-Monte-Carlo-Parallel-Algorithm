

main:
	gcc -g -Wall -fopenmp -o pi util.c main.c -lm

test:
	gcc -g -Wall -fopenmp -o runTests util.c runAllTests.c -lm

clean:
	rm pi_redox pi_critical runTests
