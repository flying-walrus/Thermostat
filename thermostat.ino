#include "thermostat.h"
#include <OneWire.h>
#include <DS18B20.h>
#include <RunningSample.h>
#include <Interval.h>
#include <Relay.h>

// init our library classes. the constants come from thermostat.h
RunningSample Temperatures( SAMPLE_SIZE );
Interval SampleInterval( SAMPLE_FREQUENCY );
Relay Heater( HEATER_PIN );
//Relay AC(AC_PIN) /* i don't have an air conditioner */
DS18B20 Therm( THERMO_PIN );

void setup()
{
  Serial.begin(9600);
}

void loop()
{
 int newData = 0; // tells us if we have data to display
  
  // if it's time, collect the data and maybe do something
  // with it
  if( SampleInterval.go() )
  {
    collectData();
    newData++;
    
    regulateHVAC();
  } 
  
  // if the data has changed, update the display
  if( newData )
  {
     updateDisplay(); 
  }
  
}

void collectData()
{
  float newTemp = 0.0;
  
   newTemp = Therm.getTempF();
   
   if ( newTemp )
    Temperatures.addSample( newTemp );
  
}

void updateDisplay()
{
  Serial.println ( Temperatures.getAverage() );
}

void regulateHVAC()
{
 if( Temperatures.getAverage() < HEATPOINT )
 {
   Heater.on();
   //AC.on()
 }
 else if ( Temperatures.getAverage() > COOLPOINT )
 {
   Heater.off();
   //AC.on();
 }
  
}
