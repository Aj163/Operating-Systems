#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main()
{	
	int fd;
	char *filename = "/home/nitk/Desktop/16CO104/file.txt";
	char *filename2 = "/home/nitk/Desktop/16CO104/file2.txt";
		
	//CREAT
	fd = creat(filename, S_IRWXU);
	if(fd<0)
		printf("Error\n");
	else
		printf("\nCreated file.txt\n");

	//OPEN
	fd = open(filename, O_CREAT | O_RDWR,S_IRWXU);
	if(fd<0)
		printf("Error\n");
	else
		printf("File opened.\n");

	//WRITE
	char *str = "Hello World";
	int size_wrote = write(fd, str, strlen(str));
	if(size_wrote<0)
		perror("error");
	else
		printf("Content \"%s\" written to file of size %d bytes.\n", str, size_wrote);

	//LSEEK
	lseek(fd, 0, SEEK_SET);


	//READ
	char buf[100];
	int size_read = read(fd, buf, 100);

	buf[size_read]='\0';
	if(size_read<0)
		perror("error");
	else
		printf("\nFile contents read : %s\n", buf);


	//DUP
	int duplicated = dup(fd);

	if(duplicated<0)
		perror("error");
	else
		printf("Old Descriptor = %d\nNew Descriptor = %d\n", fd, duplicated);


	//LINK
	int linked = link(filename, filename2);
	if(linked!=0)
		perror("\nError");
	else
	{
		printf("\nLink created successfully\n");

		//UNLINK
		int stat = unlink(filename2);
		if(stat == 0)
			printf("Link removed successfully\n\n");
		else
			perror("\nError");
	}


	//ACCESS
	int existing = access(filename, F_OK);
	if(existing < 0)
		perror("error");
	else
		printf("File \"%s\" exists\n", filename);


	//CHMOD
	int chmod_permit = chmod(filename, S_IRWXG| S_IRWXU);
	if(chmod_permit<0)
		perror("error");
	else
		printf("\nRWX permission to group given\n");


	//CHOWN
	int chown_permit = chown(filename, 1000, -1);
	if(chown_permit < 0)
		perror("Error");
	else
		printf("Student is the new owner\n");


	//UMASK
	int old_mask = umask(S_IWOTH);
	if(old_mask<0)
		perror("error");
	else
		printf("Previous mask value: %d\n",old_mask );

	//CLOSE
	if(fd>=0)
	{
		printf("\nFile closed.\n\n");
		close(fd);
	}
}
