
#include <Wire.h>

#define SLAVE_ADDRESS 0x38 

#define vddPin 9
#define gndPin 10

unsigned char num_table[16] = {
    0xd7, // 0
    0x03, // 1
    0xb6, // 2
    0xa7, // 3
    0x63, // 4
    0xe5, // 5
    0xf5, // 6
    0x07, // 7
    0xf7, // 8
    0xe7, // 9
    0x77, // A
    0xf1, // b
    0xd4, // C
    0xb3, // D
    0xf4, // E
    0x74  // F
};

void i2cstart()
{
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(0x48);
    Wire.endTransmission();

    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(0xe0);
    Wire.write(0x00);
    Wire.endTransmission();
}

void i2cclear()
{
    byte i;
    byte numx;
    for (i = 0x07; i < 0x48; i = i+1) {
        Wire.beginTransmission(SLAVE_ADDRESS);
        Wire.write(0x48);
        Wire.write(i);
        Wire.endTransmission(); 

        Wire.beginTransmission(SLAVE_ADDRESS);
        Wire.write(0xe0);
        Wire.write(0x00);
        Wire.endTransmission();
    }
}

void delay_char(unsigned char t) {
    while(--t);
}

void setup() {
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);
    pinMode(vddPin, OUTPUT);
    digitalWrite(vddPin, HIGH);
    delay(500);

    Wire.begin();
    i2cstart();
}

void loop() {
    for (int i=0; i<=999 ; i=i+1) {
        i2cclear();
        float i;
        unsigned char k;
        while(1) {
            for(i = -1.10;i<100100;i = i + 0.01) {
                display(i);
                for (k = 0;k <250;k ++) {
                    delay_char(250);
                }
            }
        }
    }
}

void display_icon()
{
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(0x48); 
    Wire.endTransmission(); 
}

void display(float dat) {
    unsigned long temp;
    char i;
    char sum;
    unsigned char num[8]= {0};

    num[7] = 0;
    if (dat < 0) {
        dat = - dat;
        num[7] = 0x20;
    }
    
    Wire.beginTransmission(SLAVE_ADDRESS);
    //Wire.write(0xe0); 
    Wire.write(0); 

    if (dat < 100000 ) {
        temp = 100 * dat; //
        num[6] = temp / 1000000;
        num[5] = temp / 100000 %10;
        num[4] = temp / 10000 %10;
        num[3] = temp / 1000 %10;
        num[2] = temp / 100 %10;
        num[1] = temp / 10 %10;
        num[0] = temp %10;
        sum = 0;
        
        for (i = 6;i >2; i--) {
            sum = num[i] + sum;
            if (sum > 0) {
              break;
            }
        }

        sum = i;
        for (i = 0;i <= sum;i++) {
            num[i] = num_table[num[i]];
        }

        num[sum + 1] = num[7];
        num[2] = num[2] | 0x08; // ドットをつける

        for (i = 0; i < 14-sum; i++) {
            Wire.write(0); 
        }

        for (i = sum +1; i >= 0 ;i--) {
            Wire.write(num[i]);
        }

    } else {

        for (i = 0; i < 16; i++) {
            Wire.write(0x20);
        }
    }
    Wire.write(0);
    Wire.endTransmission(); 
}

