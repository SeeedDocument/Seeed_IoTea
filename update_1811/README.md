# Seeed IoTea LoRa Solution

*Internet+* is a popular concept at this moment. This time we tried the Internet plus agriculture to make tea garden grows out the Internet Tea.

## Things used in this project

### Hardware components

- LoRa/LoRaWAN Gateway Kit
- Grove - Barometer Sensor(BME280)
- Grove - Dust Sensor
- Grove - Gas Sensor(O₂)
- Grove - CO2 Sensor
- Grove - Digital Light Sensor
- Soil Moisture & Temperature Sensor
- USB Camera
 
### Software apps and online services

- Microsoft Visual Studio 2015

## Story

On Mengding Mountain northeast of Ya’an, Sichuan, the mountain ridge runs west to east in a sea of green. This is a most familiar sight for 36-year-old Deng, one of the very few Mengding tea makers of his generation, with a plantation of 50mu (=3.3 hectares) situated at 1100m above sea level. Deng comes from a family of tea makers, but carrying on the family legacy is not an easy task. “Our teas are grown at high altitude in an organic environment to ensure its excellent quality. But at the same time, the growth density is low, cost is high and budding is uneven, making tea hard to harvest. That’s why high-mountain teas are normally small harvests and their values are not reflected on the market.”For the past two years, Deng has been trying to raise consumer awareness of high-mountain tea to promote their value. And when he met Fan, who was looking for a plantation to implement Seeed’s IoTea technology, a perfect match for a solution was made.

### Hardware Connection

The hardware of this project can be splitted to 4 parts: Power, Sensors, Node and Gateway. Following article will show you how to complete it step by step.

**Power Part**

Power Part mainly contains a Solar Panel and a Lithium Battery, if you just build this project for demonstration, you can ignore them. Or you can follow [Previous tutorial](https://project.seeedstudio.com/SeeedStudio/seeed-lora-iotea-solution-b5ee95) to install node power.

**Sensor Part**

In Sensor Part, because of the many of sensors, we used a weather station, and also made a Acrylic bracket to install them.

![Sensor Part](./images/1.jpg)

As you see in the picture above, Digital Light Sensor always on the top, so that it can collect lighting infomation. The sensors that will generate heat are installed in middle of the Acrylic bracket, such as O2 Sensor, Dust Sensor and CO2 Sensor. At last, Temperature and Humidity Sensor on the bottom of Acrylic bracket.

Besides, Soil Temperature and Humidity Sensor is installed alone in the soil.

**Node Part**

![Node Part](./images/2.jpg)

Node Part is a Seeeduino LoRaWan which installed in a Waterproof Box, it connect to power and sensors via Water Joints. Among them, Dust Sensor connect to LoRaWan's digital pin D3, CO2 Sensor connect to pin D4 & D5, Soil Sensor connect to pin D6 & D7, O2 Sensor connect to analog pin A1 and Light Sensor & Barometer Sensor connect to I2C port.

*NOTE: A 10k Resistor should be added between Soil Sensor's Blue(Data) cable and Red(Vcc) cable.*

Seeeduino LoRaWan collect sensors value once in a while, and send them to Gateway via LoRa. The data format like below:

    {
    	[0],	/* Air tempreature(℃)						*/
    	[1],	/* Air humidity(%)							*/
    	[2],	/* Altitude(m) high byte					*/
    	[3],	/* Altitude(m) low byte						*/
    	[4],	/* CO2 concentration(PPM) high byte			*/
    	[5],	/* CO2 concentration(PPM) low byte			*/
    	[6],	/* Dust concentration(pcs/0.01cf) high byte	*/
    	[7],	/* Dust concentration(pcs/0.01cf) low byte	*/
    	[8],	/* Light intensity(lux) high byte			*/
    	[9],	/* Light intensity(lux) low byte			*/
    	[10],	/* O2 concentration(%)						*/
    	[11],	/* Soil temperature(℃)						*/
    	[12],	/* Soil humidity(%)							*/
    	[13],	/* Battery voltage(V)						*/
    	[14]	/* Sensor error code						*/
    }

Each bit in Sensor Error Code byte has a difference meaning, just like below:

    {
    	bit0: 1;		/* Barometer Sensor Error			*/
    	bit1: 1;		/* CO2 Sensor Error					*/
		bit2: 1;		/* Dust Sensor Error				*/
		bit3: 1;		/* Light Sensor Error				*/
		bit4: 1;		/* O2 Sensor Error					*/
		bit5: 1;		/* Soil Sensor Error				*/
		reserved: 2;	/* Reserved							*/
    }

**Gateway Part**

![Gateway Part](./images/3.jpg)

Gateway Part is a Raspberry Pi which plugged Gateway module RHF0M301–868 and PRI 2 Bridge RHF4T002, it installed in a Waterproof Box and connect to power & USB Camera via Water Joints. Because it use specialized firmware, please follow [Seeed Wiki](http://wiki.seeedstudio.com/LoRa_LoRaWan_Gateway_Kit/) to configure it.

### Software Programming

As Hardware Connection, Software Programming also can be splitted, it can be splitted to 3 parts: Node, Gateway and Website.

**Node Part**

Most of drivers that Node Part required are already contained in `origin_driver` folder. The libraries following down need to be installed manually: 

- [Adafruit_ASFcore](https://github.com/adafruit/Adafruit_ASFcore)

Because the project is complicated, we recommend you use Microsoft Visual Studio instead of Arduino IDE. A plugin called Visual Micro can help you biuld an Arduino project by using Visual Studio, click [here](https://www.visualmicro.com/) for more information.

For better readability and maintainability, we use Object-Oriented Programming this time. The class diagram of this project looks like below:

![class diagram](./images/class_diagram.png)

For those sensors already have OOP driver, we repacked it to adapt this project, for others, we rewrote their drivers by using OOP. The Sensor class in middleware layer is used to unify interfaces of real sensors, for example, a barometer sensor can collect temperature, humidity and altitude at the same time, so it has 3 interfaces to acquire temperature, humidity and altitude. But they have difference method name, which will make the program of acquiring sensors value more complicated, just like this:

    barometer->getTemperature();
    barometer->getHumidity();
    barometer->getAltitude();
    // ...
    another_sensor->getSomeValue();
    // ...

But using OOP, it looks like this:

    for (auto i = 0; i < SENSORS_COUNT; i++) {
    	sensors[i]->getValue();
    }

We also packed an Application class, it implement IApplication interface, the setup() and loop() method in IoTea.ino can call setup() and loop() method in Application object.

*NOTE: USB Serial is used to debug ONLY. After debugging, please comment it's initialize code in setup() method.*

**Gateway Part**

Gateway Part's Python program in home folder is used to take photos and upload them to Amazon S3 Server every hour. Before you use it, configure your AWS by following steps. Firstly, install AWS SDK and AWS CLI to gateway by using commands: 

	pip install boto3
    pip install awscli --upgrade --user

And then, enter AWS CLI install folder and run AWS CLI:

    cd ~/.local/bin && ./aws configure

Configure your AWS Access Key ID, AWS Secret Access ID and Default region name. After that, you are ready to take and upload photos to AWS S3 Server, photo.py looks like:

    #!/usr/bin/python
    
    import boto3
    import os
    import time
    
    # Create an S3 client
    s3 = boto3.client('s3')
    bucket_name = 'static.seeed.cc'
    
    while True:
    	try:
    		localtime = time.localtime(time.time())
    		if int(time.strftime('%M', localtime)) != 0:
    			continue
    		
    		year = time.strftime('%Y', localtime)
    		season = int(time.strftime('%m', localtime)) % 4 + 1
    		filename = time.strftime('%Y%m%d-%H0000', localtime) + '.jpg'
    		
    		# Take photo
    		os.system("fswebcam --no-banner -r 1920x1080 {}".format(filename))
    		
    		upload_path = 'files/iotea/{}s{}/{}'.format(year, season, filename)
    		
    		# Uploads the given file using a managed uploader, which will split up large
    		# files automatically and upload parts in parallel.
    		s3.upload_file(filename, bucket_name, upload_path)
    		print('Uploaded file to {}'.format(upload_path))
    		
    		# Remove local file
    		os.remove(filename)
    		print('Deleted local file {}'.format(filename))
    	except:
    		continue
    	finally:
    		time.sleep(60)

If you don't like to upload your photos, you can comment codes about S3 above. For run this program after booting gateway every time, you can install a Desktop to your Raspberry Pi by using these commands:

    sudo apt-get update
    sudo apt-get install xorg
    sudo apt-get install lxde openbox
    sudo apt-get install pix-icons pix-plym-splash pixel-wallpaper
    sudo apt-get install raspberrypi-ui-mods
    sudo reboot

And then, add `@lxterminal -e python /home/rxhf/photo.py` to file `/home/rxhf/.config/lxsession/LXDE-pi`, let it looks like this:

    @lxpanel --profile LXDE-pi
    @pcmanfm --desktop --profile LXDE-pi
    @lxterminal -e python /home/rxhf/photo.py
    @xscreensaver -no-splash
    @point-rpi

**Website**

You can configure a web site by following [here](https://github.com/SeeedDocument/iotea-hb/blob/master/iotea.md), or using other framework.

## Operation

You can visit our websites to view real-time data:

- [In Yaan](https://iotea.seeed.cc/)
- [Demonstration](https://iotea-hb.seeed.cc/)


[Video](https://www.youtube.com/watch?v=4df5kaaKa6I&feature=youtu.be)