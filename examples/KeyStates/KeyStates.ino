//************************************************************
// this is a simple example that uses the Gkeypad library by soheils2
//
// 1. scan pins and get key state
// 2. if  no key is pressed returns                    	  :  RELEASED
// 3. if one key is pressed less than bounce-time returns :  IDLE
// 4. if one key is pressed more than bounce-time returns :  PRESSED
// 5. if one key is pressed more than HoldTime returns    :  HOLD
// 
// 
//
//************************************************************

#include <Gkeypad.h>


  const int PINS = 5; // 5 pins can make 15 keys
  int giantPins[PINS]={2,3,4,5,6};
  const int MaxKeys = ( (PINS*(PINS+1)) /2 ); //always use this line for get maximum keys
/*  
 *   **************how it works?***************
 *   this is an example that shows wich character shows the pin we want!
 *   EX1: 0/10 : button between pin giantPins[0] and giantPins[10].
 *   EX2: 4/G  : button between pin giantPins[4] and GND!
 *   
  char giantKeys[MaxKeys] = {
    
      '0/1' ,'0/2' ,'0/3' ,'0/4' ,'0/G',
      '1/2' ,'1/3' ,'1/4' ,'1/G' ,
      '2/3' ,'2/4' ,'2/G' ,
      '3/4' ,'3/G' ,
      '4/G'
    
    };   
  
 *   Keymap:  when you call gKeyborad.getKey(); this is the numkeys you get:
 *
  char giantKeys[MaxKeys] = {
    
      'key1'  , 'key2'  , 'key3'  , 'key4' , 'key5',
      'key6'  , 'key7'  , 'key8'  , 'key9' ,
      'key10' , 'key11' , 'key12' ,
      'key13' , 'key14' ,
      'key15'
    
    };
    
*/
    
  char giantKeys[MaxKeys] = {
      'a','b','c','d','e',
      'f','g','h','i',
      'j','k','l',
      'm','n',
      'o'
    }; 
	
Gkeypad gKeyborad=Gkeypad( makeKeymap(giantKeys), giantPins, PINS);//or you can use this:
//Gkeypad gKeyborad=Gkeypad( makeKeymap(giantKeys), giantPins, PINS,Debounce=100,HoldTime=700); 

void setup(){
  Serial.begin(115200);
  
  gKeyborad.setHoldTime(1000);       // Default is 700mS
  gKeyborad.setDebounceTime(100);    // Default is 100


}

void loop() {

stateToSerial();
}


KeyState lastState=RELEASED;
void stateToSerial(){
  
  KeyState State=gKeyborad.getState();
  if(lastState!=State){
  switch (State){
   case IDLE :
       Serial.println("IDLE");
       break;
       
   case RELEASED:
       Serial.println("RELEASED");
       break;
        
   case HOLD:
      Serial.println("HOLD");
       break;
       
   case PRESSED :
       Serial.println("PRESSED");
       break;            
  }
  lastState=State;
  }
}


