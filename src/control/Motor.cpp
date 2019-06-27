/*
 * Motor.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: lenovoi7
 */
#include "Motor.h"

/*
 * Usou-se ziegler-nichols frequency response method
 * Kc=3.2
 * Tc =0.7s
 */
float Motor::cp=8000.0f;
float Motor::cd=1000.0f;
float Motor::ci=10.0f;


Motor::Motor(
		Pwm *A_High,
		GPIO *A_Low,
		Pwm *B_High,
		GPIO *B_Low,
		Encoder *Enc)
		//Timer_Time2 *MTimer

{
	Motor_A_High = A_High;
	Motor_A_Low = A_Low;
	Motor_B_High = B_High;
	Motor_B_Low = B_Low;
	Motor_Enc = Enc;
	//Motor_Time = MTimer;
}

int16_t Motor::Get_Desloc(){
	return Motor_Enc->get_position()-last_position;
}

float Motor::Get_control_signal(){
	return control_signal;
}

//será chamada pelo handler da interrupção gerada pelo TIM6(a cada 1 ms)
void Motor::Control_Speed(float desired_speed){
	//Get_Speed();

	error=(desired_speed-real_wheel_speed)/1000;
	ierror = 0;
	for(int j = 18; j > 0; j--){
		last_error[j+1]=last_error[j];
		ierror = ierror + last_error[j+1];
	}
	last_error[0]=error;
	ierror = ierror + last_error[0];
	//if(ierror > 1000) ierror = 1000;
	//if(ierror < -1000) ierror = -1000;

	derror=error-last_error[1];

	control_signal=cp*error + ci*ierror + cd*derror;

	if(control_signal>1000) {
		dutycycle=1000;
	}
	if(control_signal<-1000) {
		dutycycle=-1000;
	}
	else dutycycle=control_signal;
	Set_Speed(dutycycle);
};

void Motor::Get_Speed(){
	//position é medida em divisões de encoder (ou 1/400 de volta)
	current_position = (int16_t)Motor_Enc->get_position();
	Motor_Enc->set_position(20000);

	int16_t distance=current_position-20000;

	float speed=(float)distance*CONVERSION; //converte da unidade da roda para m/s (vel do centro da roda)
	                                     //talvez seja melhor converter de m/s pra unidade da roda
	real_wheel_speed=1000*speed; //x1000 para nao ter que usar float
};

void Motor::Set_Speed(float speed)
{
	if (speed > 0)
	{
		if (speed>1000)
		{
			dutycycle=1000;
		}
		else
		{
			dutycycle=(int)speed;
		}
		STM_EVAL_LEDOff(LED4);
		STM_EVAL_LEDOn(LED3);
		Motor_A_Low->Reset();
		Motor_B_High->set_DutyCycle(0);
		while(Motor_A_Low->Status());
		Motor_A_High->set_DutyCycle(dutycycle);
		Motor_B_Low->Set();
	}
	else
	{
		speed=-speed;
		if(speed>1000)
		{
			dutycycle=1000;
		}
		else
		{
			dutycycle=(int)speed;
		}
		STM_EVAL_LEDOff(LED3);
		STM_EVAL_LEDOn(LED4);
		Motor_B_Low->Reset();
		Motor_A_High->set_DutyCycle(0);
		while(Motor_B_Low->Status());
		Motor_B_High->set_DutyCycle(dutycycle);
		Motor_A_Low->Set();
	}
	return;
}

void Motor::SetPID(float p, float i, float d) {
	cp=p;
	ci=i;
	cd=d;
}

void Motor::GetPID(float p, float i, float d){
	p=cp;
	i=ci;
	d=cd;
}
