/*
This is a client file which contains functions like open(), read(), write().... which are used to handle the driver code in the driver.c file
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h> 
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256          
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM

int main()
{
	int ret, fd;
	char stringToSend[BUFFER_LENGTH];
	printf("Starting device test code example...\n");
	
	//when from client application open() system call is invoked it will internally call dev_open() function from the device dreiver appliction
	
	fd = open("/dev/Marvellous_Driver_1", O_RDWR);             // Open the device with read/write access...... hey tya device driver la hANDLE karnar ahe... this is present in client file

	if (fd < 0)
	{
		perror("Failed to open the device...");
		return errno;
	}
	printf("Type in a short string to send to the kernel module:\n");
	scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
	printf("Writing message to the device [%s].\n", stringToSend);
	
	//when from client application write() system call is invoked it will internally call dev_write function from the device dreiver application
	
	ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
	if (ret < 0)
	{
		perror("Failed to write the message to the device.");
		return errno;
	}

	printf("Press ENTER to read back from the device...\n");
	getchar();

	printf("Reading from the device...\n");
	ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
	if (ret < 0)
	{
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("The received message is: [%s]\n", receive);
	printf("End of the program\n");


	//when from client application close() system call is invoked it will internally call dev_write function from the device dreiver application
	close(fd);
	return 0;
}