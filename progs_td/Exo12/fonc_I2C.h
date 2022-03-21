/************************************************************************
* TITLE: fonc_i2c.h               
* AUTHOR:               
* DESCRIPTION: include pour liaison I2C          
* VERSION : 1.0
*           
************************************************************************/


/* DEFINE **************************************************************/



/* PROTOTYPE ***********************************************************/

void Init_I2C(void);
void Start_I2C(void);
void Write_I2C(char data);
uint8_t Read_I2C(void);
void Ack_I2C(void);
void NoAck_I2C(void);
void Stop_I2C(void);


