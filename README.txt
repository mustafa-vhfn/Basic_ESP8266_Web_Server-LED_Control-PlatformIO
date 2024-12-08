### Follow these steps to run the program ###

1) Create a virtual environment and install the python platformio library:
    $ python3 -m venv venv
    $ source venv/bin/activate
    $ pip3 install platformio
    
2) Upload the LittleFS files (HTML and CSS):
	$ pio run --target uploadfs 
	(NB: Make sure the ESP8266 is properly connected to your computer before executing this command.)
	
3) Upload the main code to the ESP8266:
	$ pio run --target upload
	
4) Open the serial monitor to see the IP address:
	$ pio device monitor
	
5) Enter the IP address into a browser to control the LEDs.
