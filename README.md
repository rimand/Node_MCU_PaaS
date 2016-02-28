# Node_MCU_PaaS
### Description
- Combine : NodeMCU_v1 + DHT11 + ThingSpeak + Sparkfun + Dweet

### Host : PaaS (WriteData) 
- api.thingspeak.com : ( api.thingspeak.com/update?api_key=(API_KEY)&(FIELD_NUMBER)=(VALUE) )
- dweet.io           : ( dweet.io/dweet/for/(THING_NAME)?(NAME)=(VALUE) )
- data.sparkfun.com  : ( data.sparkfun.com/input/(PUBLIC_KEY)?private_key=(PRIVATE_KEY)&(NAME)=(VALUE) )

### NOTE
- DHT dht(DHTPIN,DHTTYPE,30); // the three parameter is 30 , that use ESP8266 at CPU Frequency 80 MHz
