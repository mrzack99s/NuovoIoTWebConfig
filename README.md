## NuovoIoTWebConfig

>	© Copyright 2019 Nuovo, TD. <br>
>	Author Chatdanai Phakaket <br>
>	email zchatdanai@gmail.com or nuovo.td@gmail.com <br>
	
 Initial setup wifi & web configure without code config. Make to easy for the user. I mean they unknows c++ code. 

**=== Setter and Getter ===**

- Setter
	- setResetButton(uint8_t,bool); // bool LOW,HIGH
	- setAPSSID(String)
	- setAPPasswd(String)
	- setWiFiSSID(String)
	- setWiFiPasswd(String)
	- setBToken(String)

- Getter (String)
	- getAPSSID()
	- getAPPasswd()
	- getWiFiSSID()
	- getWiFiPasswd()
	- getBToken()
	- getCheckSetup() // return boolean check initial setup
 
 
**=== If Blynk ===**
 
 At file "BlynkSimpleEsp32_h" **Comment "WiFi.mode(WIFI_STA);" on line 37**
 

```
//WiFi.mode(WIFI_STA);
```


**=== How to use?  ===**

1. include library

```
#include <nuovoIoTWebConfig.h>
```

2. Create object

```
Nuovo nuovo;
```

*At void setup()*

3. If you have set reset button. You must set reset reset button before init(). If blank it means D0 to reset button.
boolean HIGH,LOW ==> It means button input or input_pullup

```
nuovo.setResetButton(pin, LOW); 
```

4. Run initial setup address

```
nuovo.init();
```

5. Then, success all above, If you don't want to set mode use this below

```
nuovo.begin();
```

But If you want to set mode. Why you should set mode? -> set for initial wifi. <br>
You can set mode with function in this below.

```
nuovo.begin("Blynk");
```

*At void loop()*

*Important! don't forget handle request*

```
nuovo.handle();
```
