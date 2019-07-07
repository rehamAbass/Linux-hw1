#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{

	input();

	return 0;
}
int input()//main shell
{
	char s[256];
	printf("shell$** ");
	scanf("%s", s);
	while (strcmp(s, "exit") != 0)
	{
		if (strcmp(s, "shell1") == 0)
			shell1();
		else if (strcmp(s, "shell2") == 0)
			shell2();
		else if (strcmp(s, "shell3") == 0)
			shell3();
		else
		{
			printf("Not supported\n");
			input();
		}
	}
	exit(0);
}
int shell1()
{
	int id, wid, status;
	char s[256];
	printf("shell1$** ");
	scanf("%s", s);
	if (strcmp(s, "jobs") == 0)
	{
		if ((id = fork()) == 0) {//check if the process child  success
			execl("/bin/ps", "ps", 0);//operate the child process
		}
		wid = wait(&status);// wait until process finish  
		shell1();//recursive call
	}
	else if (strcmp(s, "by") == 0)//if the command = “by” so get back to the input function
		input();
	else {
		printf("Not supported\n");
		shell1();//return again to the function try another command 
	}

}

int shell2()
{
	int id, wid, status;
	char s[256];
	printf("shell2$** ");
	scanf("%s", s);
	if (strcmp(s, "mydate") == 0) {
		if ((id = fork()) == 0) {
			execl("/bin/date", "date", 0);//activate the process with “date”command in the shell
		}
		wid = wait(&status);
		shell2();
	}
	else if (strcmp(s, "by") == 0)
		input();
	else {
		printf("Not supported\n");
		shell2();// try again another command
	}

}

int shell3()
{
	int fd_from, rbytes, i = 0, id, wid, status, j;
	char s[256], buff[256], temp[30] = "/bin/";
	char* fname[4];
	char *token, *par0, *par1, *par2, *par3;

	printf("shell3$** ");
	scanf("%s", s);//get command :”read file ”||”by"
	if (strcmp(s, "by") == 0)
		input();
	scanf("%s", fname[0]);//get the file name
	while (1) {
		if (strcmp(s, "readFile") == 0)
		{


			if ((fd_from = open(fname[0], O_RDONLY)) == -1)//if file didn’t open leave a message
			{
				printf("error");
				return(-1);
			}
			if ((rbytes = read(fd_from, buff, 256)) == -1)//return the number of characters he success to read from the file
			{
				printf("error");
				return(-1);
			}


			token = strtok(buff, "\n");//token= first statement
			while (token != NULL)
			{
				fname[i] = (char*)malloc(strlen(token) * sizeof(char));
				strcpy(fname[i], token);//save in a string arrey 
				i++;
				token = strtok(NULL, "\n");//token=next line
			}

			
			for (j = 0; j < i - 1; j++)
			{//saving parameters
				par0 = strtok(fname[j], " ");
				par1 = strtok(NULL, " ");
				par2 = strtok(NULL, " ");
				par3 = strtok(NULL, " ");

				strcat(temp, par0);//temp="/bin/filename"
				if ((id = fork()) == 0)
				{
					execl(temp, par0, par1, par2, par3);//execute the process
				}
				else wait();//wait until process finishes
				strcpy(temp, "/bin/");

			}
			shell3();
		}
		else
		{
			printf("Not supported\n");
			shell3();
		}

		close(fd_from);
	}
}
