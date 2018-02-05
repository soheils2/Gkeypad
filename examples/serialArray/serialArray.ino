//************************************************************
// this is a simple example that uses the Gkeypad library by soheils2
//
// 1. scan pins and get key number
// 2. if it changed print it on serial.print
// 3. show where is the exact character is on terminal
// 
//
//************************************************************

#include <Gkeypad.h>


const int PINS = 5;
int giantPins[PINS]={2,3,4,5,6};
const int MaxKeys = ( (PINS*(PINS+1)) /2 ); //always 

char giantKeys[MaxKeys] = {
  'a','b','c','d','e',
  'f','g','h','i',
  'j','k','l',
  'm','n',
  'o'
}; 
	
Gkeypad gKeyborad=Gkeypad( makeKeymap(giantKeys), giantPins, PINS); 

void setup(){
  Serial.begin(115200);
  
  gKeyborad.setHoldTime(1000);       // Default is 700mS
  gKeyborad.setDebounceTime(100);    // Default is 100


}

void loop() {

keyToSerial();

}


int lastkey=-1;
void keyToSerial() {
  int nkey = gKeyborad.getKey();
  if(lastkey != nkey ){
    lastkey= nkey;
    if(nkey!=NULL){
         Serial.print(" numKey: ");
         Serial.print(nkey);
         Serial.print("  char:");
         Serial.println(gKeyborad.getCharKey());
		 
		 
         printarray(nkey,PINS);
		 
    }
  }
  delay(1);
}


void printarray(int num,int pins){
  int until=pins-1,count=0;
  for(int i =0; i<pins;i++){
    for (int j =0;j<=until;j++){
      if(count==num-1)Serial.print("' ', ");
      else Serial.print(" *   ");
      count++;
    }
  Serial.println();
  until--;
  }
}