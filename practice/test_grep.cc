#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv)
{
	if( argc != 4 )
		return 0;

	int default_in = dup(0);
	int default_out = dup(1);
	//int default_err = dup(2);

	int pipefd[2];
	
	if( pipe(pipefd) == -1 )
	{
		perror("Pipe Error!!\n");
		exit(1);
	}
	
	int infd = open(argv[2], O_RDONLY);
	if( infd < 0 )
	{
		perror("Error inputfile\n");
		exit(1);
	}

	dup2(infd, STDIN_FILENO);
	close(infd);

	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	int ret = fork();
	if( ret == 0 )
	{
		close(pipefd[0]);

		char *args[3];
		args[0] = "grep";
		args[1] = strdup(argv[1]);
		args[2] = NULL;

		execvp(args[0], args);
		perror("execvp\n");
		_exit(-1);
	} 
	else if( ret < 0 )
	{
		perror("fork\n");
		exit(1);
	}

	int outfd = open(argv[3], O_CREAT|O_WRONLY|O_APPEND, 0666);
	if( outfd < 0 )
	{
		perror("Error outputfile\n");
		exit(1);
	}
	
	dup2(outfd, STDOUT_FILENO);
	close(outfd);

	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);

	ret = fork();
	if( ret == 0 )
	{
		close(pipefd[1]);

		char *args[2];
		args[0] = "sort";
		args[1] = NULL;
		
		execvp(args[0], args);
		perror("Execvp failed\n");
		_exit(-1);		
	}
	else
	{
		perror("fork\n");
		exit(1);
	}

	dup2(default_in, 0);
	close(default_in);
	dup2(default_out, 1);
	close(default_out);
	
	waitpid( ret, 0, 0 );

	return 0;
}
