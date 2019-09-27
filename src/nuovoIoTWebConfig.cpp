/*
	© Copyright 2019 Nuovo, TD.
	Author Chatdanai Phakaket
	email nuovo.td@gmail.com
 */


#include "nuovoIoTWebConfig.h"
#include "web_pages/config_pages.h"
DNSServer dnsServer;
WiFiServer server(80);
WebServer server1(8080);
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 10, 1);
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void Nuovo::begin(){

	if(checkSetup())
		run();
	else
		wizard();
}

void Nuovo::begin(String mode){
	setMode(mode);
	if(checkSetup())
		run();
	else
		wizard();
}

void Nuovo::init(){
	if (!EEPROM.begin(EEPROM_SIZE)){
		   Serial.println("failed to initialise EEPROM"); 
		   delay(1000000);
		}
	WiFi.mode(WIFI_AP_STA);
	apNameAddr = 0;
	apPasswdAddr = 30;
	wifiSSIDAddr = 60;
	wifiPasswdAddr = 90;
	bTokenAddr = 120;

	if(resetButtonOn == LOW)
	   	pinMode(resetButton,INPUT_PULLUP);
	else
	   	pinMode(resetButton,INPUT);

	attachInterrupt(resetButton, resetSys, FALLING);
}

void Nuovo::setAPSSID(String name){
	pushArgs(name,apNameAddr);
}
void Nuovo::setAPPasswd(String passwd){
	pushArgs(passwd,apPasswdAddr);
}
void Nuovo::setWiFiSSID(String name){
	pushArgs(name,wifiSSIDAddr);
}
void Nuovo::setWiFiPasswd(String passwd){
	pushArgs(passwd,wifiPasswdAddr);
}
void Nuovo::setBToken(String token){
	pushArgs(token,bTokenAddr);
}
void Nuovo::setResetButton(uint8_t pin,bool on){
	resetButton = pin;
	resetButtonOn = on;
}

bool Nuovo::getCheckSetup(){
	return checkSetup();
}

String Nuovo::getAPSSID(){
	String ret = EEPROM.readString(apNameAddr);
	ret.trim();
	return ret;
}
String Nuovo::getAPPasswd(){
	String ret =  EEPROM.readString(apPasswdAddr);
	ret.trim();
	return ret;
}
String Nuovo::getWiFiSSID(){
	String ret =  EEPROM.readString(wifiSSIDAddr);
	ret.trim();
	return ret;
}
String Nuovo::getWiFiPasswd(){
	String ret =  EEPROM.readString(wifiPasswdAddr);
	ret.trim();
	return ret;
}
String Nuovo::getBToken(){
	String ret =  EEPROM.readString(bTokenAddr);
	ret.trim();
	return ret;
}

void Nuovo::handle(){
	dnsServer.processNextRequest();
	WiFiClient client = server.available();   // listen for incoming clients

	if (client) {
		String header="";
	    String currentLine = "";
	    while (client.connected()) {
	      if (client.available()) {
	        char c = client.read();
	        header += c;
	        if (c == '\n') {
	          if (currentLine.length() == 0) {
	            client.println("HTTP/1.1 200 OK");
	            client.println("Content-type:text/html");
	            client.println();
	            client.print(config_pages);

	            break;
	          } else {
	            currentLine = "";
	          }
	        } else if (c != '\r') {
	          currentLine += c;
	        }
	      }
	    }
	    client.stop();
	}
	server1.handleClient();
}


///// Private function

void Nuovo::pushArgs(String arg,int addr){
	EEPROM.writeString(addr,arg);
	EEPROM.commit();
}

void Nuovo::run(){
	CreateAP();
	if(Mode != "Blynk")
		WiFiConnect();
	Serial.println("Initial setup !!!");
	Serial.print("AP Name = ");
	Serial.println(getAPSSID());
	Serial.print("WiFi SSID = ");
	Serial.println(getWiFiSSID());
	Serial.print("Blynk token = ");
	Serial.println(getBToken());
}
void Nuovo::setMode(String mode){
	Mode = mode;
}
void Nuovo::wizard(){
	setAPSSID("NuovoIoTWebConfig");
	CreateAP();
    Serial.println("Initial setup !!!");
    Serial.print("AP Name = ");
    Serial.println(getAPSSID());
}
void Nuovo::WiFiConnect(){
	WiFi.begin(getWiFiSSID().c_str(), getWiFiPasswd().c_str());
	while (WiFi.status() != WL_CONNECTED);
}
void Nuovo::CreateAP(){
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
	if(getAPPasswd() == "\0")
	    WiFi.softAP(getAPSSID().c_str());
	else
	    WiFi.softAP(getAPSSID().c_str(), getAPPasswd().c_str());
	    	
	startWebServer();
}
bool Nuovo::checkSetup(){
	if(getAPSSID()!= "\0" && getAPPasswd() != "\0"
	   && getWiFiSSID() != "\0" && getWiFiPasswd() != "\0")
	    return	true;

	return false; 
}
void Nuovo::startWebServer(){
	dnsServer.start(DNS_PORT, "*", apIP);
	server.begin();
	server1.on("/config",HTTP_POST,[]() {
		EEPROM.writeString(0,server1.arg("apName"));
		EEPROM.writeString(30,server1.arg("apPasswd"));
		EEPROM.writeString(60,server1.arg("wifiName"));
		EEPROM.writeString(90,server1.arg("wifiPasswd"));
		EEPROM.writeString(120,server1.arg("bToken"));
		EEPROM.commit();
    	server1.send(200, "text/html", "<center><h2>Update configure success System restart in 4 s!! </h2></center>");
  		delay(4000);
		ESP.restart();
  	});
	server1.begin();
}

void IRAM_ATTR Nuovo::resetSys() {
	portENTER_CRITICAL_ISR(&mux);
    EEPROM.writeString(0,"\0");
	EEPROM.writeString(30,"\0");
	EEPROM.writeString(60,"\0");
	EEPROM.writeString(90,"\0");
	EEPROM.writeString(120,"\0");
	EEPROM.commit();
	portEXIT_CRITICAL_ISR(&mux);

    Serial.println("System reset in 4 s.");
	delay(4000);
	ESP.restart();
}

