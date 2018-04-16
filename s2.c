#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
int fd[2];
pid_t p;
char rbuff[50],wbuff[50];
int rcount;
pipe(fd);
if(argc<3)
{
printf("\nAtleast need 2 parameters");
}
int fopen=open(argv[1],0);
int tfile=open(argv[2],0777);
if(fopen==-1 || tfile==-1)
{
printf("\nOpening file failed");
}
p=fork();
if(p==0)
{
close(fd[1]);
read(fd[0],rbuff,sizeof(rbuff));
printf("\nThe received string is :%s",rbuff);
write(tfile,rbuff,strlen(rbuff)+1);
}
else
{
close(fd[0]);
while(rcount=read(fopen,rbuff,sizeof(rbuff))>0)
{
write(fd[1],rbuff,sizeof(rbuff));
}
close(fd[1]);
}
}
