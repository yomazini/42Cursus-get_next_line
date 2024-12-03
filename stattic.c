
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//static Variable Example:
// const char *append_string(const char *new_part)
// {
// 	static char static_str[100] = "";
// 	strcat(static_str,new_part);
// 	return static_str;
// }

// int main()
// {
// 	printf("Res 1 %s\n",append_string("Hello"));
// 	printf("Res 1 %s\n",append_string("World"));
// 	printf("Res 1 %s\n",append_string("of"));
// 	printf("Res 1 %s\n",append_string("Linux"));
// }

// open and close Examples 

// int main()
// {
// 	int fd = open("testFile.txt",O_CREAT | O_RDWR, 0644);
// 	//close (fd);
// 	int len = strlen("Hi How are you doing hoop you doing Great today and not tomorrow");

// 	//int i = write(fd,"Hi How are you doing hoop you doing Great today and not tomorrow",len);
// 	int i = 9999;
// 	//sleep(10);
// 	printf("%d",i);
// 	if (i == -1)
// 	{
// 		perror("open");
// 		return 1;
// 	}
// 	char buffer[500];
// 	ssize_t bytes_read = read(fd, buffer, sizeof(buffer)-1);
// 	if (bytes_read == -1)
// 	{
// 		perror("Read");
// 		close(fd);
// 		return 1;
// 	}
// 	buffer[bytes_read] = '\0';
// 	printf("\n%s",buffer);
// 	printf("\nFd is:%d\n",fd);
// 	close(fd);
// 	return 0;
// }

// int main()
// {
// 	int fd = open("test00.txt",O_CREAT | O_RDWR);
// 	write(fd, "Hello",5);
// 	write(fd, "sir",3);
// 	sleep(5);
// 	//int fd1 = open("test00.txt",O_CREAT | O_RDWR);
// 	write(fd, "tEst",4);
// 	close (fd);
// }


