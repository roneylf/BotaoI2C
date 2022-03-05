#include <BotaoI2C.h>
BotaoI2C::BotaoI2C()
{
}
BotaoI2C::BotaoI2C(int addressBot, int id)
{
    Wire.begin();
    Wire.beginTransmission(addressBot);
    Wire.write(B00000000);
    Wire.endTransmission();
    this->enabledLeds = false;
    this->addressBot = addressBot;
}

BotaoI2C::BotaoI2C(int addressBot, int id, int addressLed)
{
    Wire.begin();
    Wire.beginTransmission(addressBot);
    //Wire.write(B00000000);
    Wire.write(B11111111);
    Serial.println(Wire.endTransmission());
  
    this->enabledLeds = true;
    Wire.beginTransmission(addressLed);
    //Wire.write(B11111111);
    Wire.write(B00000000);

    Serial.println(Wire.endTransmission());
    this->addressBot = addressBot;
    this->addressLed = addressLed;
}

BotaoI2C::~BotaoI2C()
{
}

int BotaoI2C::ler()
{
    Wire.requestFrom(this->addressBot, 1); // 1 ByteF
    if (Wire.available())
    {
        byte a = Wire.read();
        //B11111110;
        a = ~a;

        for (int i = 0; i < 8; i++)
        {

            //0000 0000 and 0000 0001 = 0000 0000
            //0000 0011 and 0000 0010 = 0000 0010
            if ((a & (B00000001 << i)) == (B00000001 << i) != this->pinos[i])
            {
                this->pinos[i] = ((a & (B00000001 << i)) == (B00000001 << i));
                if (this->pinos[i] == 1)
                {
                    BotaoI2C::acenderLed(i);
                    return i+1;
                }
            }
        }
    }
    return 0;
}

void BotaoI2C::acenderLed(int id)
{
    //Serial.println(id);
    if (this->enabledLeds)
    {
        this->ledbuffer |= (B00000001 << id);
        Wire.beginTransmission(this->addressLed);
        Wire.write(ledbuffer);
        Wire.endTransmission();
    }
}

void BotaoI2C::apagarLed(int id)
{
    Serial.println("apagando o led"+ (String)id);
    if (this->enabledLeds)
    {
        this->ledbuffer = this->ledbuffer ^ (B00000001 << (id - 1));
        Wire.beginTransmission(this->addressLed);
        Wire.write(ledbuffer);
        Wire.endTransmission();
    }
}
