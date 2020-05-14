#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
	int stat;
	pid_t pid;
	char cad[128];
	
	sprintf(cad,"Program %s started.\n",argv[0]);
	write(1,cad,strlen(cad));
	
	pid = getpid();
	/* Emprar aquesta funció per a esbrinar l'estat d'un procés usant el seu PID. */
	/* Aquí no ens cal, ja que, sabem que a l'hora d'executar-se aquest codi el procés */ 
	/* estarà en execució. */
	waitpid(pid, &stat, WNOHANG);

	printf(
		"\n\tPID: %u\tPPID: %u\tUID: %u\tEUID: %u\tGID: %u\tEGID: %u\tPRI: %u\tSTAT: R\n\n", 
		pid, 
		getppid(), 
		getuid(), 
		geteuid(), 
		getgid(), 
		getegid(),
		getpriority(PRIO_PROCESS, pid)
	);
	/* read(0,cad,1); */
	

	sprintf(cad,"Program %s ended.\n",argv[0]);
	write(1,cad,strlen(cad));
		
	exit(0);
}
