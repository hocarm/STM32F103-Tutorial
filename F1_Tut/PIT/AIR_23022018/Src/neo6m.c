#include "neo6m.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*________________________________GPS_Function__________________________________*/
// Ham xoa ki tu trong chuoi
void Delete_Char(char s[], int pos)
{
	int n = strlen(s); 
	for(int i = pos + 1; i < n; i++)
	{
		s[i - 1] = s[i];
	}
	s[strlen(s) - 1] = '\0'; // Ki tu ket thuc
}

// Ham tim kiem ki tu trong chuoi
int Search_Char(unsigned char Char, char *Str, unsigned char Time, int Len)
{
    int   i=0;
    int  j=0;
    while((j<Time)&&(i<=Len))
    {
        if(Str[i] == Char)    j++;  
        i++;  
    }
    return i;
}

// Ham clear bo nho dem rx
void CLEAR_GPS_RX_Buffer() 
{
	for (int j=0; j<GPS_BUFFER_SIZE; j++)
	nmeaMessage.GPS_RX_Buffer[j] = 0; //clear Rx_Buffer before receiving new data
	for(int j=0; j< 10; j++)
	dataGps.Latitude[j] = 0;					//clear latitude buffer
	for(int j=0; j< 11; j++)
	dataGps.Longtitude[j] = 0;				//clear longtitude buffer
}

// Ham lay vi tri chuoi $GPRMC
int GPS_GetGPRMC()
{
	int k = 0;
	for(int k=0; k < (GPS_BUFFER_SIZE); k++)
	{
		if( (nmeaMessage.GPS_RX_Buffer[k] == 'M') && (nmeaMessage.GPS_RX_Buffer[k] == 'C') )
		{
			k = k - 5; // get the $
			return k;
		}
	}
	return k;
}

//Ham lay thong tin gps
unsigned char GPS_DeviceInfo(char* time, char* status, char* latitude, char* S_N, char* longitude, char* E_W, char* speed, char* dir, char* date)
{
  int i = 0;
	int k = 0;
	int Temp1, Temp2;
	Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,1,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 2
  // printf("%d\n",Temp1);
	Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,2,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 2
  // printf("%d\n",Temp2);
	if(nmeaMessage.GPS_RX_Buffer[Temp2] == 'V'){
		return 0;
	}
	else{
//-------------------------------------------------------------------------------------------------		
    //LAY VI DO:
		Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,3,GPS_BUFFER_SIZE);	 //Tim vi tri co ',' lan 3
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,4,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 4
	  //	printf("%d\n",Temp2);
		//Tach chuoi vi do
		k = 0;
		for(i = Temp1; i < Temp2-1; i++){
			dataGps.Latitude[k] = nmeaMessage.GPS_RX_Buffer[i];
			k++;	
		}
    dataGps.Latitude[i] = 0;
		
		Delete_Char(dataGps.Latitude,4);	
		lat = atoi(dataGps.Latitude);
//-------------------------------------------------------------------------------------------------				
    //LAY KINH DO:
		Temp1 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,5,GPS_BUFFER_SIZE);	 //Tim vi tri co ',' lan 5
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_RX_Buffer,6,GPS_BUFFER_SIZE);	//Tim vi tri co ',' lan 6
		//printf("%d\n",Temp2);
		k = 0;
		for(i = Temp1 ; i < Temp2-1; i++){
			dataGps.Longtitude[k] = nmeaMessage.GPS_RX_Buffer[i];
			k++;	
		}
		dataGps.Longtitude[i] = 0;
		
		Delete_Char(dataGps.Longtitude,5);
    lng = atoi(dataGps.Longtitude);
//-------------------------------------------------------------------------------------------------			
		//LAY VAN TOC:
		Temp1 = Search_Char(',',nmeaMessage.GPS_VTG_Buffer,7,GPS_VTG_SIZE);	 //Tim vi tri co ',' lan 3
		//printf("%d\n",Temp1);
		Temp2 = Search_Char(',',nmeaMessage.GPS_VTG_Buffer,8,GPS_VTG_SIZE);	//Tim vi tri co ',' lan 4
	  //	printf("%d\n",Temp2);
		//Tach chuoi van toc
		k = 0;
		for(i = Temp1; i < Temp2-1; i++){
			dataGps.Speed[k] = nmeaMessage.GPS_VTG_Buffer[i];
			k++;	
		}
    dataGps.Speed[i] = 0;
		velocity = atof(dataGps.Speed);
		
	return 1;	
	}
}

// Tim kiem dau , trong chuoi GPS
void Scan_for_dots(){
	uint8_t i = 0;
	while (i!=26){
		if (nmeaMessage.GPS_RX_Buffer[i] == ','){
			nmeaMessage.GPS_RX_Buffer[i] = 'y';
		}
		i++;
	}
}

/*___________________________________________LayChuoi_GPRMC_GPVTG________________________________________________*/

/*_____________________________________________________________________________________________*/

void Processing_$GPGRMC(){
	if(Nmea_Line1 == 1){
	if (ch == '$'){
		nmeaMessage.GPS_Counter = 1;
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = '$';
	}
	if (nmeaMessage.GPS_Counter == 2){
		if (ch == 'G'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'G';
		}
	}
	if (nmeaMessage.GPS_Counter == 3){
		if (ch == 'P'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'P';
		}
	}
	if (nmeaMessage.GPS_Counter == 4){
		if (ch == 'R'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'R';
		nmeaMessage.GPS_Flag++;
		}
	}
	if (nmeaMessage.GPS_Counter == 5){
		if (ch == 'M'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'M';
		nmeaMessage.GPS_Flag++;
			
		}
	}
	if (nmeaMessage.GPS_Counter == 6){
		if (ch == 'C'){
		nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter-1] = 'C';
		nmeaMessage.GPS_Flag++;
		}
	}
	if (ch == '*'){
		if (nmeaMessage.GPS_Flag == 3){
			statusGps.GPS_ans_stt = GPS_DeviceInfo(dataGps.Time, dataGps.Status, dataGps.Latitude, dataGps.S_N, 
																				 dataGps.Longtitude, dataGps.E_W, dataGps.Speed, dataGps.Dir, dataGps.Date);
			if(statusGps.GPS_ans_stt){
				printf("Kinh do: %s\n", dataGps.Latitude);
				printf("Vi do: %s\n", dataGps.Longtitude);
				printf("Toc do: %s\n",dataGps.Speed);
			}
			//printf("%s\n", nmeaMessage.GPS_RX_Buffer);
			Nmea_Line1 = 0; 
			Nmea_Line2 = 1;
			}
		nmeaMessage.GPS_Flag = 0;
		nmeaMessage.GPS_Counter = 0;
	}

	if (0 < nmeaMessage.GPS_Counter && nmeaMessage.GPS_Counter < 50){
			if (nmeaMessage.GPS_Flag == 3){
				nmeaMessage.GPS_Counter_Tmp = nmeaMessage.GPS_Counter-1;
				nmeaMessage.GPS_RX_Buffer[nmeaMessage.GPS_Counter_Tmp] = ch;
				nmeaMessage.GPS_Counter++;
			}
			else {
				nmeaMessage.GPS_Counter++;
		}
	}
	

	
/*-------------------------------------------------------------------*/	
}
}



void Processing_$GPVTG(){
	if(Nmea_Line2 == 1){
	if (ch == '$'){
		nmeaMessage.GPS_SCounter = 1;
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = '$';
	}
	if (nmeaMessage.GPS_SCounter == 2){
		if (ch == 'G'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'G';
		}
	}
	if (nmeaMessage.GPS_SCounter == 3){
		if (ch == 'P'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'P';
		}
	}
	if (nmeaMessage.GPS_SCounter == 4){
		if (ch == 'V'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'V';
		nmeaMessage.GPS_SFlag++;
		}
	}
	if (nmeaMessage.GPS_SCounter == 5){
		if (ch == 'T'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'T';
		nmeaMessage.GPS_SFlag++;	
		}
	}
	if (nmeaMessage.GPS_SCounter == 6){
		if (ch == 'G'){
		nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter-1] = 'G';
		nmeaMessage.GPS_SFlag++;
		}
	}
	if (ch == '*'){
		if (nmeaMessage.GPS_SFlag == 3){
			//printf("%s\n", nmeaMessage.GPS_VTG_Buffer);
			Nmea_Line1 = 1;
			Nmea_Line2 = 0;
		}
		nmeaMessage.GPS_SFlag = 0;
		nmeaMessage.GPS_SCounter = 0;
	}
	if (0 < nmeaMessage.GPS_SCounter && nmeaMessage.GPS_SCounter < 50){
			if (nmeaMessage.GPS_SFlag == 3){
				nmeaMessage.GPS_SCounter_Tmp = nmeaMessage.GPS_SCounter-1;
				nmeaMessage.GPS_VTG_Buffer[nmeaMessage.GPS_SCounter_Tmp] = ch;
				nmeaMessage.GPS_SCounter++;
			}
			else {
				nmeaMessage.GPS_SCounter++;
		}
	}
/*_____________________________________________________________________________*/	
  }
}
