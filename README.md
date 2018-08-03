# Seeed_IoTea

IoTea的节点代码和PCB图。
<a href="https://cn1.loriot.io/apps/websocket.html?token=vnwDBQAAAA1jbjEubG9yaW90LmlvliKTqUfFMlIiSug0jy9a2A==">点我查看原始数据。</a>

## 主要器材清单

### 网关

- <a href="https://www.seeedstudio.com/LoRa-LoRaWAN-Gateway-868MHz-Kit-with-Raspberry-Pi-3-p-2823.html">LoRa LoRaWAN Gateway - 868MHz Kit with Raspberry Pi 3</a>
- <a href="https://www.seeedstudio.com/Raspberry-Pi-Ultimate-Cooling-Dual-Fan-p-2926.html">Raspberry Pi Ultimate Cooling Dual Fan</a>

### 节点

- <a href="https://www.seeedstudio.com/s/Seeeduino-LoRaWAN-p-2780.html">Seeeduino LoRaWAN</a>
- <a href="https://www.seeedstudio.com/s/Grove-Temp%26Humi%26Barometer-Sensor-(BME280)-p-2653.html">BME 280 空气温湿度传感器</a>
- <a href="https://www.seeedstudio.com/s/Grove-Dust-Sensor%EF%BC%88PPD42NS%EF%BC%89-p-1050.html">Dust sensor</a>
- <a href="https://www.seeedstudio.com/s/Grove-Carbon-Dioxide-Sensor(MH-Z16)-p-1863.html">CO2 sensor</a>
- <a href="https://www.seeedstudio.com/s/Grove-Oxygen-Sensor(ME2-O2-%D0%A420)-p-1541.html">O2 sensor</a>
- <a href="https://www.seeedstudio.com/s/Grove-Digital-Light-Sensor-p-1281.html">Digital Light Sensor</a>
- <a href="https://www.seeedstudio.com/s/Soil-Moisture-%26-Temperature-Sensor-p-1356.html">Soil Moisture & Temperature Sensor</a>


# 代码部分：
## 1. 数据格式

节点向网关上传的数据为：

```c
unsigned char Lora_data[15] = {0,1,2,3,,4,5,6,7,8,9,10,11,12,13,14};
```

各项数据含义：

- **Lora_data[0]**：空气温度，摄氏度
- **Lora_data[1]**：空气湿度，百分比
- **Lora_data[2]**：海拔高度高8位，米
- **Lora_data[3]**：海拔高度低8位
- **Lora_data[4]**：CO2浓度高8位
- **Lora_data[5]**：CO2浓度低8位
- **Lora_data[6]**：灰尘浓度高8位
- **Lora_data[7]**：灰尘浓度低8位
- **Lora_data[8]**：光照强度高8位
- **Lora_data[9]**：光照强度低8位
- **Lora_data[10]**：氧气含量，单位为千分之一
- **Lora_data[11]**：土壤温度，摄氏度
- **Lora_data[12]**：土壤湿度，百分比
- **Lora_data[13]**：电池电压，单位为0.1V
- **Lora_data[14]**：错误代码

错误代码含义：

```
Lora_data[14] = [bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0]
```
- bit0：1 为 BME 280 空气温湿度传感器错误
- bit1：1 为 CO2 传感器错误
- bit2：1 为灰尘传感器错误
- bit3：1 为 Digital Light Sensor 错误
- bit4：1 为氧气传感器数据错误
- bit5：1 为土壤温湿度传感器错误
- bit6：保留
- bit7：保留

另外本文件夹内有错误代码转换器：Error_code_transform.exe ，可以打开这个.exe文件并输入十六进制的错误代码，然后就得到了传感器错误类型。

## 2. 参数调节

### 1. 数据发送运行周期

```c
// seeedtea.ino
#define interval_time 600			//间隔时间，秒
```
更改此参数可改变数据发送间隔。在每次循环中，数据采集需耗时约 1 分钟，不建议将此值改为60秒以内。值越大，系统运行越省电。

### 2. 灰尘传感器预热时间

```c
// seeedtea.ino
#define Preheat_time 30000			//Dust Sensor预热时间，单位 ms
//Dust_other.cpp
#define sampletime_ms 30000		//采样时间30s;
```
灰尘传感器需要一定预热时间来让传感器内的空气流动起来。

### 3. 电压系数

```c
//POWER_Ctrl.cpp
#define Battery_coefficient 0.159864	//ADC读数乘以这个系数就是电池电压
#define Solar_coefficient   0.22559	  //ADC读数乘以这个系数就是太阳能电压
```

### 4. 风扇参数调节

```c
//POWER_Ctrl.cpp
#define Fan_start_temp 45     //风扇开始运行温度
#define Fan_start_light 500   //风扇开始运行光照强度
```

### 5. 氧气传感器参数

```c
//Oxygen.cpp
#define O2_percentage 208.00  //初始化时会按照这个值校准氧气传感器，单位为千分之一
```

### 6. 宏开关，注释后会停止相应模块工作

```c
// seeedtea.ino
#define LORA_RUN      //注释后lora初始化和数据发送停止
#define SENSOR_RUN    //注释后外部传感器停止工作

//POWER_Ctrl.cpp
#define FAN_ON        //使用一个固定的电池电压代替采集到的电池电压，解除电压对风扇的判断
                      //测试使用。实际应用需注释掉
/******* DS18B20 模式控制 **********************/
#define Slower_Mode		//慢速模式获取温度。注释掉即为快速模式
```

### 7. 引脚定义

D2：接 LED 指示灯和外部复位单片机

I2C：SCL 和 SDA

```c
//Dust_other.h
#define Dust_pin 3

//CO2.cpp
#define CO2_serial Serial1    //CO2 传感器使用D0和D1硬件串口

//seeedtea.ino
#define dataPin 6   //土壤水分和温度传感器数据引脚
#define clockPin 7  //土壤水分和温度传感器时钟引脚

//POWER_Ctrl.h
#define DS18B20_pin 8   //板载温度传感器
#define Fan_pin 9       //风扇引脚
#define Air_CtrlPin 10  //空气传感器控制引脚
#define Soil_CtrlPin 11 //土壤传感器控制引脚
#define Battery_pin A2  //电池电压采集引脚
#define Solar_pin A3    //太阳能电压采集引脚

//Oxygen.h
#define O2_pin A1
```

### 8. 看门狗定时器

看门狗定时器用于监测系统运行状态，当系统运行异常时会复位单片机，从而使其可以长期不间断运行。

需要引用的库：

- Adafruit_SleepyDog.h            已经添加进项目中
- Adafruit_ASFcore-master.zip     打包放在项目文件夹中，需要手动添加进Arduino IDE中

#### 相关函数：

##### 1. 使能看门狗

```c
int WatchdogSAMD::enable(int maxPeriodMS, bool isForSleep)
```
输入参数：
- int maxPeriodMS：等待时间，单位毫秒。超时会复位。最大允许16000毫秒。

返回值：
- int类型，返回实际等待时间

##### 2. 复位看门狗

```c
void WatchdogSAMD::reset()
```

输入参数：无

输出参数：无

调用该函数来复位看门狗定时器，简称“喂狗”。超出等待时间未复位就会使单片机重启。

##### 3. 停止看门狗

```c
void WatchdogSAMD::disable()
```

停止看门狗定时器。

## 3. 传感器详细信息

### 1.	Temp&Humi&Barometer Sensor

供电：5Vor3.3V

参数范围：温度-40-85℃ 湿度0%-100% 气压300-100hPa

IIC通信，地址0X76，

相关函数：bme280.getTemperature(), bme280.getHumidity(), bme280.getPressure()

Lora_data[0]： 温度 Lora_data[1]： 湿度

Lora_data[2]：高8位Lora_data[3]：低8位 气压

### 2.	Dust Sensor（PPD42NS）

供电：5V 单位：pcs/L或pcs/0.01cf

相关函数：Dust_value = Dust_concentration()

Lora_data[6]：高8位  Lora_data[7]：低8位 灰尘

### 3.	Carbon Dioxide Sensor(MH-Z16)

供电：4.5V-6V 范围：0-2000ppm

UART通信

相关函数：unsigned int CO2_dataRecieve(void)

Lora_data[4]：高8位   Lora_data[5]：低8位  CO2浓度

### 4.	Digital Light Sensor

供电：5V 范围0.1-40000LUX

IIC通信，地址 0X29,

相关函数：TSL2561.readVisibleLux()

Lora_data[8]：高8位   Lora_data[9]：低8位  光照

### 5.	Oxygen Sensor(ME2-O2-Ф20)

供电：3.3V/5V 范围：0-25%

读模拟值

int O2_value()

Lora_data[10] 氧气浓度（通过该函数获得的值要除以10，得到百分比）

### 6.	Soil Moisture & Temperature Sensor

供电：3.3V 范围：温度-40-+123.8℃ 湿度0-100%

sht1x.readTemperatureC() sht1x.readTemperatureF() sht1x.readHumidity()

Lora_data[11] 土壤温度 Lora_data[12] 土壤湿度
