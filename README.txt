OLED Text Display

Do you often find yourself awake late at night thinking about how much you wished you could type some text that is under 10 characters into the serial port and see your text illuminated upon a lovely little arduino screen before it scrolls away to the right? If so... what a coincidence! I've got just the thing for you!

Hardware: Adafruit Feather Hazzah and Feather OLED cape 

Program: Takes in text from the serial monitor and displays it onto OLED screen (make sure Only accepts words that are 10 characters or less (will not display characters past 10 this). Text is displayed when '\n'/carriage return, aka user has pressed enter or send, is detected on serial port. After 2 seconds text will scroll to the right and new text can be entered.