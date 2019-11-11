Huff: main.o huffman.o minHeap.o inout.o
	gcc main.o inout.o huffman.o minHeap.o  -o Huff

main.o: main.c
	gcc -c main.c

huffman.o: huffman.c
	gcc -c huffman.c

minHeap.o: minHeap.c
	gcc -c minHeap.c

inout.o: inout.c
	gcc -c inout.c

clean:
	rm main.o huffman.o minHeap.o inout.o Huff