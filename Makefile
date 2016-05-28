all: run

run:  brute.out backtrack.out
	

brute.out: brute.c	
		gcc -o brute.out brute.c -lm

backtrack.out: backtrack.c		
		gcc -o backtrack.out backtrack.c
	
clean: brute.c backtrack.c 
	rm brute.out backtrack.out backtrack_output.txt brute_output.txt
