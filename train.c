#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define BUFSIZE 1024


//TODO: //open file with different flags 
// error handling // write on it // read from it what you write each 10 words per line untill EOF //  


// https://www.youtube.com/watch?v=scXWLP8uhDU
// practice it, 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

// int main() {
//     // Open file with different flags
//     int fd = open("test.txt", O_RDONLY);
//     if (fd == -1) {
//         // Comprehensive error handling
//         printf("Error opening file: \n");
//         return 1;
//     }

//     char buffer[100];
//     ssize_t bytes_read;

//     // Read in chunks
//     while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
//         buffer[bytes_read] = '\0';
//         printf("Read %zd bytes: %s\n\n", bytes_read, buffer);
//     }

//     // Check for read errors
//     if (bytes_read == -1) {
//         printf("Error reading file: \n");
//     }

//     close(fd);
//     return 0;
// }

// Exercise 1: Basic File Opening
	/*Objective: Open a file in read-only mode and handle errors.

	Write a program to:
	Open a text file (example.txt) using open() with the O_RDONLY flag.
	Check if the file was opened successfully. If not, print an error message using perror() and exit the program.
	If successful, print: "File opened successfully!"
	Close the file descriptor using close().
	*/
#define Chucksize 20

// int main()
// {
// 	int fd = open("Exercice1.txt",O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("ERROR HAPPEND opening the file:");
// 		return 1;
// 	}
	
// 	char Buff[Chucksize + 1];
// 	size_t bytes_read;
// 	while((bytes_read = read(fd , Buff, Chucksize)) > 0)
// 	{	Buff[bytes_read] = '\0';
// 		if (write(STDOUT_FILENO, Buff, bytes_read) == -1)
// 		{
// 			perror("Error writin to output");
// 			close(fd);
// 			return 1;
// 		}

// 		if (write(STDOUT_FILENO,"\n",1) == -1)
// 		{
// 			perror("Error writing newline.");
// 			close(fd);
// 			return 1;
// 		}
// 	}
// 	if (bytes_read == -1 )
// 		perror("Error reading file");
// 	close(fd);
// }

// fopen vs open 

