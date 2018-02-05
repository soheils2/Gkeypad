
//#define NUMBER_PIN 11

#include <Arduino.h>


#define makeKeymap(x) ((char*)x)

#ifndef NULL
#define NULL 0
#endif

typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState;



class Gkeypad {

  public:

          
    Gkeypad(char *Keymap, int *Keypins, int NUM_PIN, uint16_t Dbounce=100, uint16_t htime=700){
            NUMBER_PIN=NUM_PIN;
            keyPins= Keypins;
            giantKeymap = Keymap;
            holdTime=htime;
            Bounce=Dbounce;
            };
			
    void setHoldTime(uint16_t htime){
            holdTime=htime;
            }
			
    void setDebounceTime(uint16_t Dbounce){
            Bounce=Dbounce;
            }

			
	int *keyPins;
	char *giantKeymap;
	int NUMBER_PIN;
	int I,J,numkey,oldKey;
	uint16_t holdTime,Bounce;
	uint64_t pushTime;
	
    int correctNum(int ii , int jj){
		int small,big,counter=0;
		if 		(ii <= jj)	{small=ii;big=jj;}//return ((I*NUMBER_PIN)+J);
		else if (jj < ii)	{small=jj;big=ii;}//   return ((J*NUMBER_PIN)+I);
		for(int i=0; i<small ; i++){
            counter+=(NUMBER_PIN)-i-1;
            }
		counter+=big;
		return (counter);
	    }
		  
    int getKey(){
		
		oldKey= numkey;
		// check pin GND //
		inputEX(-1); //make all of the pins as output
		for(int j=0 ; j< NUMBER_PIN ;j++){
			if (!digitalRead(keyPins[j])) {I=NUMBER_PIN; J=j;return(numkey=correctNum(I,J));}
		}
		//end check pin GND //
		
		int k=NUMBER_PIN;
		for(int i=0 ; i< NUMBER_PIN ;i++){
			inputEX(keyPins[i]);
			for(int j=0 ; j< k ;j++){
			  int newj= NUMBER_PIN-j;
			  if (!digitalRead(keyPins[newj])) {
				  digitalWrite(keyPins[i],HIGH);
				  // delay(1);
				  if (!digitalRead(keyPins[newj]))goto skip; //wrong check! GND pin is attached
				  else I=i; J=newj ;
				  return(numkey=correctNum(I,J));
				  }
			}
			skip:
			k--;  //for romoving mirror situation.
		  }
		pushTime=millis();
		I=-1;
		J=0;
		return(NULL);
        }
		  
    char getCharKey(){
		
		if(getKey()){
		numkey=correctNum(I,J);
		return(giantKeymap[numkey-1]);
		}else return(NULL);
		}
		  
    KeyState getState(){
		
		int key=getKey();
			 if (key== NULL)              {pushTime=millis(); return RELEASED;}
		else if (key== oldKey && millis()-pushTime<Bounce)  return IDLE;
		else if (key== oldKey && millis()-pushTime<holdTime)return PRESSED;
		else if (key== oldKey && millis()-pushTime>holdTime)return HOLD;
        }
		  
protected:
               
    void inputEX(int GPIO){
		
		for(int i=0 ; i< NUMBER_PIN ;i++){
		  if (keyPins[i] !=GPIO) pinMode(keyPins[i],INPUT_PULLUP);
		}
		pinMode(GPIO,OUTPUT);
		digitalWrite(GPIO,LOW);
        }
};

