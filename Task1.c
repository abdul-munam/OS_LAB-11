#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 0x1111

union semun 
{ 
int val;
struct semid_ds *buf;
unsigned short array;
};

struct sembuf p = { 0, -1, SEM_UNDO}; 
struct sembuf v = { 0, +1, SEM_UNDO};

int main()
{
int id = semget (KEY, 1, 0666 | IPC_CREAT); 

if(id < 0)
{
perror("semget"); 
exit(11);
}

union semun u; 
u.val = 1;

if(semctl(id, 0, SETVAL, u) < 0)
{
perror("semct1"); 
exit(12);
}

int pid;
pid = fork();
srand(pid); 
if(pid < 0) 
{
perror("fork"); 
exit(1);
} 
else if(pid)
{
char *s = "01234567"; 
int l = strlen(s);
for (int i = 0; i < 1; ++i)
{
if(semop (id, &p, 1) < 0) 
{
perror("semop p"); 
exit(13);
} 
putchar(s[i]);
fflush(stdout);
sleep(1);
putchar(s[i]); 
fflush(stdout);
if(semop (id, &v, 1) < 0)
{
perror("semop p"); 
exit(14);
}
sleep(1);
}
}
else
{
char *t = "ABCDEFGH";
int l = strlen(t);
for(int i = 0; i < l; ++i)
{
if(semop(id, &p, 1) < 0)
{
perror("semop p"); exit(15);
}
putchar(t[i]);
fflush(stdout);
sleep(1); 
putchar(t[i]);
fflush(stdout);
if(semop (id, &v, 1) < 0)
{
perror("semop p"); exit(16);
}
sleep(1);
}
}
}