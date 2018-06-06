#include "utils/commandline.h"

extern CommandLine cmdline;

extern int speed[0]; //medicao atual da velocidade


uint16_t cmd_info(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];

	if(argc==1){
		size+=sprintf(buffer+size, "%d\n", speed[0]);
	} else {
		size+=sprintf(buffer+size, "Syntax: info\r\n");
	}
	return size;
}

//comando a ser enviado no prompt para escrever o valor atual de velocidade na porta serial
CommandLine cmdline({"[A"},
					{cmd_info});
