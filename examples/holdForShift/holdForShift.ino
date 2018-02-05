//************************************************************
// this is a simple example that uses the Gkeypad library by soheils2
//
// 1. scan pins and get key number & state
// 2. if one key is pressed less than HoldTime returns    :  char from first array
// 3. if one key is pressed more than HoldTime returns    :  char from second array
// 
// 
//
//************************************************************

#include <Gkeypad.h>

#define HTime 350

  const int PINS = 5; // 5 pins can make 15 keys
  int giantPins[PINS]={2,3,4,5,6};
  const int MaxKeys = ( (PINS*(PINS+1)) /2 ); //always use this line for get maximum keys

    
  char giantKeys1[MaxKeys] = {
      'a','b','c','d','e',
      'f','g','h','i',
      'j','k','l',
      'm','n',
      'o'
    }; 
    
  char giantKeys2[MaxKeys] = {
      'A','B','C','D','E',
      'F','G','H','I',
      'J','K','L',
      'M','N',
      'O'
    }; 
	
Gkeypad gKeyborad=Gkeypad( makeKeymap(giantKeys1), giantPins, PINS);//or you can use this:
//Gkeypad gKeyborad=Gkeypad( makeKeymap(giantKeys), giantPins, PINS,Debounce=100,HoldTime=700); 

void setup(){
  Serial.begin(115200);
  
  gKeyborad.setHoldTime(HTime);       // Default is 700mS

Serial.println("**********//hello//********");
}

int lkey = NULL;
void loop() {
  int  key  = gKeyborad.getKey();
  if (key!=lkey ){
  if (key){
	  delay(HTime+5);
	  KeyState State=gKeyborad.getState();
	  if(State == HOLD) Serial.println(giantKeys2[key-1]);
	  else              Serial.println(giantKeys1[key-1]);
    
  }
    lkey=key;
  }
}



