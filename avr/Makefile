# To obtain list of devices and programmers read
# http://www.nongnu.org/avrdude/user-manual/avrdude.html
DEVICE     = atmega328p
CLOCK      = 16000
PROGRAMMER = usbtiny
BAUD       = 19200
FILENAME   = main
COMPILE    = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

all: clean build upload

build:
	# compiles the program twice
	# once in the .out format (.o), 
	# and once in the newer (and better designed) .elf format
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	
	# uses avr-utils to create a .hex file specific for the device
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	# uploads .hex file to device and confirms upload was successful
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -b $(BAUD) -U flash:w:$(FILENAME).hex 

clean:
	# removes all files created by build process
	rm main.o
	rm main.elf
	rm main.hex
