/*
	© Copyright 2019 Nuovo, TD.
	Author Chatdanai Phakaket
	email nuovo.td@gmail.com
 */

#include <EEPROM.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#define EEPROM_SIZE 2048

class Nuovo
{
	public:
		void begin();
		void init();
		void setResetButton(uint8_t pin,bool on);
		void setAPSSID(String name);
		void setAPPasswd(String passwd);
		void setWiFiSSID(String name);
		void setWiFiPasswd(String passwd);
		void setBToken(String token);
		void handle();
		bool getCheckSetup();
		String getAPSSID();
		String getAPPasswd();	
		String getWiFiSSID();	
		String getWiFiPasswd();	
		String getBToken();

	private:
	    int apNameAddr;
	    int apPasswdAddr;
	    int wifiSSIDAddr;
	    int wifiPasswdAddr;
	    int bTokenAddr;
	    uint8_t resetButton = 0;
	    bool resetButtonOn = HIGH;
	    void pushArgs(String arg,int addr);
	    void run();
	    void wizard();
	    void CreateAP();
	    void startWebServer();
	    bool checkSetup();
	    void WiFiConnect();
	    static void resetSys();
};
