
#include <vic.h>


void setup ()
{
  vicore_init(115200);
  Serial.begin(115200);

}

void loop ()
{
  if(Serial.available()){
    vicore_process(Serial.read());
  }

}
