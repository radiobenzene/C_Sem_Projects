#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char **argv)
{
	if(argc != 3)
	{
		printf("Check Arguments\n");
		return -1;
	}
	pid_t pid1,pid2;
	int min,max;
	
	int fd0[2];
	int fd1[2];
	int fd2[3];
	
	pipe(fd0);
	pipe(fd1);
	pipe(fd2);
	
	min = atoi(argv[1]);//minimum
	max = atoi(argv[2]);//maximum
	
	if((pid1 = fork()))
	{
		if((pid2 = fork()))
		{
			//Parent
			int n = min;
			
			close(fd1[1]);
			close(fd1[0]);
			close(fd0[0]);
			close(fd2[1]);
			
			//fd0[1] - write
			//fd2[0] - read
			
			write(fd0[1],&n,sizeof(n));
			printf("START GAME....\n");
			printf("PARENT(PID = %d) ~ n = %d\n",getpid(),n);
			sleep(1);
			while((read(fd2[0],&n,sizeof(n))) == sizeof(n))
			{
				n++;
				sleep(1);
				if(n >= max)
				{
					printf("PARENT recieves maximum limit = %d\n",n);
					printf("PARENT :DEAD:GAME OVER\n");
					close(fd0[1]);
					close(fd2[0]);
					exit(0);
				}
				else
				{
					write(fd0[1],&n,sizeof(n));
					printf("PARENT(PID = %d) ~ n = %d\n",getpid(),n);
				}
			}
		}
		else
		{
			//Son_2
			int counter;
			close(fd0[1]);
			close(fd2[0]);
			close(fd0[0]);
			close(fd1[1]);
			
			//fd1[0] - read
			//fd2[1] - write
			
			while((read(fd1[0],&counter,sizeof(counter))) == sizeof(counter))
			{
				counter++;
				sleep(1);
				if(counter >= max)
				{
					printf("SON 2 recieves maximum limit = %d\n",counter);
					printf("SON 2 :DEAD:GAME OVER\n");
					close(fd1[0]);
					close(fd2[1]);
					exit(0);
				}
				else
				{
					
					write(fd2[1],&counter,sizeof(counter));
					printf("SON 2(PID = %d) ~ n = %d\n",getpid(),counter);
				}
				
			}
		}
	}
	else
	{
			//Son_1
			int prim_counter;
			close(fd0[1]);
			close(fd1[0]);
			close(fd2[0]);
			close(fd2[1]);
			
			//fd0[0] - read
			//fd1[1] - write
			
			while((read(fd0[0],&prim_counter,sizeof(prim_counter))) == sizeof(prim_counter++))
			{
				
				prim_counter++;
				sleep(1);
				if(prim_counter >= max)
				{
					printf("SON 1 recieves maximum limit = %d\n",prim_counter);
					printf("SON 1 :DEAD:GAME OVER\n");
					close(fd0[0]);
					close(fd1[1]);
					exit(0);
				}
				else
				{
					
					write(fd1[1],&prim_counter,sizeof(prim_counter));
					printf("SON 1(PID = %d) ~ n = %d\n",getpid(),prim_counter);
				}	
			}
	}
	return 0;
}
