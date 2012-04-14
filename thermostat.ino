#include "thermostat.h"
#include <OneWire.h>
#include <DS18B20.h>
#include <RunningSample.h>
#include <Interval.h>
#include <Hvac.h>

// init our library classes. the constants come from thermostat.h
RunningSample Temperatures( SAMPLE_SIZE );
Interval SampleInterval( SAMPLE_FREQUENCY );
Hvac Heater( HEATER_PIN );
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
    
    regulateHeater();
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
  Serial.println ( Heater.running() );
}

void regulateHeater()
{
 if( Temperatures.getAverage() < SETPOINT )
 {
   Heater.on();
 }
 else
 {
   Heater.off();
 }
  
}
