/*
 * OLED assignment tasked for 10/16/17 in Bridging the Hardware/Software Divide Fall 2017
 * 
 * Hardware: Adafruit Feather Hazzah and Feather OLED cape 
 * Program: Takes in text from the serial monitor and displays it onto OLED screen (make sure to set to "9600 baud" and "Both NL & CR").
 * Displays unique startup image
 * Only accepts words that are 10 characters or less (will not display characters past 10 this).
 * Text is displayed when '\n'/carriage return, aka user has pressed enter or send, is detected on serial port 
 * After 2 seconds text will scroll to the right and new text can be entered.
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display = Adafruit_SSD1306();


//Used to take input from serial and keep track
char inputBuffer[10]; //array storing the values we get from serial input, takes max of 10 characters
int bufferPointer=0; // array counter to keep track of where we are in array/how many characters we have

//To be used as "flags" to keep track of where we are in the program
bool theEnd = false;
bool hasBeenDisplayed = false;

//take the current time, to be used for later to create delay
unsigned long waitTime = millis();

void setup() {
  Serial.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setTextWrap(false); //keeps the text from falling onto the next line


unsigned long startTime = millis();
//My startup cat face
while(millis() - startTime < 2000){
display.setCursor(45,0);
display.print("^ ^");
display.setCursor(45,8);
display.print("=.=");
display.display();
display.clearDisplay();
}
display.print(" ");
display.display();
display.clearDisplay();

}

void loop(){

  takeInput();

}

void takeInput(){


      //if we have not reached the end of our input, do all this
      if(!theEnd){
              //if there is input on the serial feed, goes character by character
              if(Serial.available()){
                
                  inputBuffer[bufferPointer]=Serial.read(); //put each character into array
                  Serial.println(inputBuffer[bufferPointer]);

                        //if we encounter a carriage return or if we have reached our max of 10 characters, we need to stop
                        if(inputBuffer[bufferPointer]== '\n' || bufferPointer == 10)
                          {
                            theEnd = true; //stop taking input
                            Serial.end();//stop taking input, added 10.12.17, I reset it when I set theEnd to true
                          }
                          bufferPointer++; //increment bufferPointer
                }

          //if theEnd is true and we haven't displayed yet, do this      
        } else if(theEnd && !hasBeenDisplayed){
              display.clearDisplay(); 
              display.setTextSize(2);
              display.setTextColor(WHITE);
              display.setCursor(0,0);

              //go through each character and display it
              for(int i = 0; i < bufferPointer; i++){
                    display.print(inputBuffer[i]);
                    display.display();
                }
                
              waitTime = millis();
              hasBeenDisplayed = true;
            }

      //If we find ourselves and we have already displayed, then we need to scroll and reset everything
      if(hasBeenDisplayed){     
                //wait 2 seconds before we commence scrolling and then take in new input
               if(millis() - waitTime > 2000){
                scrollText(); //scroll text horizontally to the right
                
                //reset my values
                hasBeenDisplayed = false; 
                theEnd = false;
                Serial.begin(9600);//Begin taking input again, added 10.12.17
                bufferPointer = 0;
                }  
          }
}

//Creates a horizontal scrolling text effect to the right
void scrollText(){

  //Go through each pixel of the screen, which is 128 across
  for(int i = 0; i < 128; i++){
        display.clearDisplay(); //each time reset screen
        display.setCursor(i*2,0); //move cursor over so we can draw to new place

        //print each character of out input string (which we will be using as a character array, inputBuffer[]
        for(int j = 0; j < bufferPointer; j++){
              display.print(inputBuffer[j]);
        }
        display.display(); //it is important to display only after you have printed each letter, or else you get staggery type writer effect
        yield();//keeps Watchdog at bay, the watchdog seems to not like how long this for loop takes
  }
  
}




