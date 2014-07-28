#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	int def_in = fileno(stdin);
	int def_out = fileno(stdout);

	char *hello = strdup("HELLO");

	int pin[2];
	int pout[2];

	int rc = pipe(pin);
	if( rc == -1 )
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}

	rc = pipe(pout);
	if( rc == -1 )
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}

	pid_t pid = fork();
	if( pid == 0 )
	{
		// Child Process

		printf("CHILD PROCESS!\n");

		close(pout[1]);
		if( pout[0] != STDIN_FILENO )
		{
			printf("MAKING pout[0] = STDIN_FILENO\n");
			if( dup2(pout[0], STDIN_FILENO) != STDIN_FILENO )
				perror("PIPE: pout[0]\n");
			// close(pout[0]);
		}

		char ch;
		int i = 0;
		char *msg_read = (char *)calloc(strlen(hello) + 1, sizeof(char));

		int n;

		while( (n = read(pout[0], &ch, 1)) > 0 )
		{
			printf("%d %c", n, ch);
			msg_read[i] = ch;
			i++;
		}

		printf("\nPARENT SENT: %s SENDING PARENT BACK: %s\n", msg_read, msg_read);

		char *arg[] = { strdup("echo"), strdup("hello\n"), NULL };

		execvp(arg[0], arg);
		perror("execvp");
		_exit(EXIT_FAILURE);
	}
	else if( pid < 0 )
	{
		// Error

		fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}
	else /*if( pid > 0 )*/
	{
		// Parent process

		printf("PARENT PROCESS! SENDING CHILD\n");
		
		close(pout[0]);
		close(pin[1]);

		for( int i = 0; i < strlen(hello); i++ )
			write(pout[1], &hello[i], 1);

		close(pout[1]);

		/*char ch;

		int n;

		dup2(pin[0], 0);

		while( (n = read(pin[0], &ch, 1)) > 0 )
			printf("%c", ch);*/
		// close(pin[0]);
	}
}