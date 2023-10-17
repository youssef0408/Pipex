#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int	main(void)
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	int		num1;
	int		num2;

	if (pipe(fd) < 0)
		return (1);

     // 1er exec   === child process
	fd_in = open("./input.txt", O_RDONLY, 0777);
	if (fd_in == -1)
		fprintf(stderr, "error  file input not found");
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);



    
    // parsing of the cmd from arg[2]
    
    scanf("%d %d",&num1, &num2);
	
    
    //2eme exec == parent process
    fd_out = open("./output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		fprintf(stderr, "error output not found");

	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
// exec command from arg[3]
	printf("salut = %d", num1+num2);

	return (0);
}


















// int main()
// {

// int		filein;

// 	filein = open(argv[1], O_RDONLY, 0777);
// 	if (filein == -1)
// 		error();
// 	dup2(fd[1], STDOUT_FILENO);
// 	dup2(filein, STDIN_FILENO);
// 	close(fd[0]);


//     int		fileout;

// 	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (fileout == -1)
// 		error();
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(fileout, STDOUT_FILENO);
// 	close(fd[1]);
// 	execute(argv[3], envp);
// }