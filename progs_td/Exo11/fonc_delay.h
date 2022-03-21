/************************************************************************
* TITLE: fonc_delay.h              
* AUTHOR:               
* DESCRIPTION:  
* VERSION : 1.1
*           2.0 suppression attend_2ms
*	  2.1 ajout temporisation 10us, 100us
*         2.2 type uint8_t
************************************************************************/

/*******************************************************************************
* Function Name  : attend_10us
* Description    : temporisation de 10us
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_100us( void);

/*******************************************************************************
* Function Name  : attend_100us
* Description    : temporisation de 100us
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_10us( void);

/*******************************************************************************
* Function Name  : attend_1ms
* Description    : temporisation de 1ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_1ms( void);

/*******************************************************************************
* Function Name  : attend_500ms
* Description    : temporisation de 500ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_500ms( void);

/*******************************************************************************
* Function Name  : attend_ms
* Description    : temporisation reglable de 0 a 255ms
* Input          : Nombre de millisecondes de 0 a 255
* Output         : None
* Return         : None
*******************************************************************************/
void attend_ms( uint8_t nb_ms);
