#include "utils/commandline.h"

extern CommandLine cmdline;


extern int speed[0]; //medicao atual da velocidade
extern int desired_speed;


uint16_t cmd_info(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];

	if(argc==1){
		size+=sprintf(buffer+size, "%d\r\n", speed[0]);
	}
	else if(argc==2){
		//size+=sprintf(buffer+size, "%s\r\n", argv8[1]);
		desired_speed = 0;
		for (int i=0; argv8[1][i]!='\0'; i++){
			desired_speed = 10*desired_speed + (argv8[1][i] - '0');
		}
		size+=sprintf(buffer+size, "%d\r\n", desired_speed);
	}
	else {
		size+=sprintf(buffer+size, "Syntax: info\r\n");
	}
	return size;
}

//comando a ser enviado no prompt para escrever o valor atual de velocidade na porta serial

CommandLine cmdline({"[A"},
						 {cmd_info});
