#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#define T 56

int max_fd(int actual, int nuevo);
void copia_fd(fd_set * dts, fd_set * org, int maxfd_mas_uno);

int main(){
	int f1,f2,rc,leidos;
	fd_set fd, fd_active;
	char buffer[T];
	f1 = open("fifo1",O_RDONLY);
	if (f1 < 0){
		perror("error open fifo1");
	}
	f2 = open("fifo2",O_RDONLY);
	if (f2 < 0){
		perror("error open fifo2");
	}
	FD_ZERO(&fd); /* Pone a 0 el conjunto fd*/
	FD_SET(f1,&fd); /* Añade el descriptor f1 al conjunto fd */
	FD_SET(f2,&fd); /* Añade el descriptor f2 al conjunto fd */
	
	while(1){
		copia_fd(&fd_active,&fd,max_fd(f1,f2)+1);
		rc = select(max_fd(f1,f2)+1,&fd_active,NULL,NULL,NULL);
		if (FD_ISSET(f1,&fd_active)){ /* Comprueba si f1 pertenece al conjunto fd_active */
			/* Leemos de la fifo 1 */
			leidos = read(f1,buffer,T);
			if (leidos < 0){
				perror("error read f1");
				close(f1);
				close(f2);
			}
			buffer[leidos-1] = '\0';
			printf("Mensaje de la FIFO1: %s.\n",buffer);
		}
		if (FD_ISSET(f2,&fd_active)){ /* Comprueba si f2 pertenece al conjunto fd_active */
			/* Leemos de la fifo 2 */
			leidos = read(f2,buffer,T);
			if (leidos < 0){
				perror("error read f2");
				close(f1);
				close(f2);
			}
			buffer[leidos-1] = '\0';
			printf("Mensaje de la FIFO2: %s.\n",buffer);
		}
 
	}
	
	return 0;
}

int max_fd(int actual, int nuevo){
	if(actual >= nuevo)
		return actual;
	return nuevo;
}

void copia_fd(fd_set * dts, fd_set * org, int maxfd_mas_uno){
	FD_ZERO(dts);
	for (int i = 0; i < maxfd_mas_uno; i++){
		if ( FD_ISSET(i,org) ){
			FD_SET(i,dts);
		}
	}
}
