#ifndef GPS_H_
#define GPS_H_

#define GPS_Status 		(*(volatile unsigned char *)(0x84000210))
#define GPS_Control 	(*(volatile unsigned char *)(0x84000210))
#define GPS_TxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_RxData 		(*(volatile unsigned char *)(0x84000212))
#define GPS_Baud    	(*(volatile unsigned char *)(0x84000214))

#endif /* GPS_H_ */
