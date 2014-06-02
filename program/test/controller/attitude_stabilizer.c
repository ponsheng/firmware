
#include "attitude_stabilizer.h"
void PID_roll(attitude_stablizer_pid_t* PID_control,imu_raw_data_t* imu_raw_data,attitude_t* attitude){

	float error = (PID_control -> setpoint) - (attitude -> roll);

	float P = error * (PID_control -> kp);

	float D = -(imu_raw_data -> gyro[0]) * (PID_control -> kd);

	(PID_control -> output) = P+D;
 
}


void PID_output(attitude_stablizer_pid_t* PID_roll,attitude_stablizer_pid_t* PID_pitch){

motor_output_t motor;

	motor. m1 =0.0;
	motor. m2 =0.0;
	motor. m3 =0.0;
	motor. m4 =0.0;
	motor. m5 =0.0;
	motor. m6 =0.0;
	motor. m7 =0.0;
	motor. m8 =0.0;
	motor. m9 =0.0;
	motor. m10 =0.0;
	motor. m11 =0.0;
	motor. m12 =0.0;

	motor . m1 = - (PID_roll->output);
	motor . m2 =   (PID_roll->output);
	motor . m3 =   (PID_roll->output);
	motor . m4 = - (PID_roll->output);
	set_pwm_motor(&motor);
}