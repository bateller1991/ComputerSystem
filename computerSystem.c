
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////
typedef struct byte{
    int* bits;
    char* address;
} byte;
typedef struct diskStorage{
    double capacity;
    int numOfWords;
    int wordSize;
    int diskIndex;
    double freeBytes;
    double usage;
    byte* bytes;
    char* diskStart;
    char* diskEnd;
} diskStorage;
typedef struct ramStorage{
    double capacity;
    double usage;
    double freeBytes;
    int numOfWords;
    int ramIndex;
    int wordSize;
    char* ramStart;
    char* ramEnd;
    byte* bytes;
} ramStorage;
typedef struct computerSystem{
    ramStorage* ram; //
    diskStorage* disk;
    int wordSize;
    char* hardwareSpecs;
} computerSystem;
/////////////////////////////////////////////////////////////////////////

char switchCase(int v){
    switch(v){
        case(0):
            return '0';
        case(1):
            return '1';
        case(2):
            return '2';
        case(3):
            return '3';
        case(4):
            return '4';
        case(5):
            return '5';
        case(6):
            return '6';
        case(7):
            return '7';
        case(8):
            return '8';
        case(9):
            return '9';
        case(10):
            return 'A';
        case(11):
            return 'B';
        case(12):
            return 'C';
        case(13):
            return 'D';
        case(14):
            return 'E';
        case(15):
            return 'F';
        default:
            return '?';
            
    }
}


int switchCase2(char c){
    switch(c){
        case('0'):
            return 0;
        case('1'):
            return 1;
        case('2'):
            return 2;
        case('3'):
            return 3;
        case('4'):
            return 4;
        case('5'):
            return 5;
        case('6'):
            return 6;
        case('7'):
            return 7;
        case('8'):
            return 8;
        case('9'):
            return 9;
        case('A'):
            return 10;
        case('B'):
            return 11;
        case('C'):
            return 12;
        case('D'):
            return 13;
        case('E'):
            return 14;
        case('F'):
            return 15;
        default:
            return -1;
    }
}

float getNumericalAddress(char* uvalue){
    char* hex = (char*)malloc(sizeof(char)*8);
    int i = 2, j = 0;
    while(i < 10){
        hex[j++] = uvalue[i++];
    }
    int bin[32];
    int curri = 0;
    const int SIZE = 32, HEX_SIZE = 8;
    
    while(curri < SIZE){
        bin[curri++] = 0;
    }
    int val = 0;
    curri = 0;
    int currHalfByte = 0;
    char c;
    int p = 3, a = 0;
    while(currHalfByte < HEX_SIZE){
        c = hex[currHalfByte++];
        val = switchCase2(c);
        p = 3;
        while(p >= 0){
            a = (int)(pow(2,p--));
            if(val - a >= 0){
                bin[curri] = 1;
                val -= a;
            }
            curri++;
        }
    }
    float sign = 1;
    if(bin[0] == 1){
        sign *= -1;
    }
    
    curri = 1;
    int expo = 7;
    val = 0;
    while(curri < 9){
        if(bin[curri++] == 1){
            val += (int)(pow(2, expo));
        }
        expo--;
    }
    val -= 127;
    p = -1;
    float fraction = 0;
    while(curri < SIZE){
        if(bin[curri++] == 1){
           fraction += (float)(pow(2,p));   
        }
        p--;
    }
    float s = (float)sign;
    fraction += 1;
    float powerandbase = (float)(pow(2, val));
    float answer = s * fraction * powerandbase;
   return answer;
}


computerSystem* createBaseComputer(int wordSize){
    printf("\n\n\tCreating Computer:\n\n");
    computerSystem* pc = (computerSystem*)malloc(sizeof(computerSystem));
    printf("\n\nPC System Initialized... ");
    pc->ram = (ramStorage*)malloc(sizeof(ramStorage));
    pc->ram->usage = 0.0000;
    printf("\n\nRam Storage Initialized...");
    pc->disk = (diskStorage*)malloc(sizeof(diskStorage));
    printf("\n\nDisk Storage Initialized...");
    pc->wordSize = wordSize;
    printf("\n\nSystem has been set to 'x16' architecture.");
    return pc;
}

double getUserDouble(char* message){
    double d = 0;
    printf("%s", message);
    scanf("%lf", &d);
    return d;
}



void printRam(int startingByte, int endingByte, ramStorage* r){
    int lc = 0;
    const int BYTESIZE = 8;
    int b = 0;
    printf("\n\n\tPrinting Ram Range [%d, %d].\n\n", startingByte, endingByte);
    for(int i = startingByte; i < endingByte; i++){
        printf("%s: ", r->bytes[i].address);
        for(int j = 0; j <= BYTESIZE; j++){
            b = r->bytes[i].bits[j];
            printf("%d", b);
            lc++;
            if(lc == 8){
                i++;
                printf("   %s:  ", r->bytes[i].address);
                j = 0;
            }
        }
        printf("\n");
        lc = 0;
    }
    printf("\n\n\n");
}

void printDisk(int startingByte, int endingByte, diskStorage* d){
    int lc = 0;
    const int BYTESIZE = 8;
    int b = 0;
    printf("\n\n\tPrinting Disk-Drive Range [%d, %d].\n\n", startingByte, endingByte);
    for(int i = startingByte; i < endingByte; i++){
        printf("%s: ", d->bytes[i].address);
        for(int j = 0; j <= BYTESIZE; j++){
            b = d->bytes[i].bits[j];
            printf("%d", b);
            lc++;
            if(lc == 8){
                i++;
                printf("   %s:  ", d->bytes[i].address);
                j = 0;
            }
        }
        printf("\n");
        lc = 0;
    }
    printf("\n\n\n");
}

char* getAddress(float f){
    int q = 2;
    if(f == 0){
        char* ret = (char*)malloc(sizeof(char) * 10);
        ret[0] = '0';
        ret[1] = 'x';
        while(q < 10){
            ret[q++] = '0';
        }
        return ret;
    }
    int bin[32];
    int curri = 0, exponent = -1, mantissa = 0;
    const int SIZE = 32, OFFSET = 127, MANTISSA_INDEX = 9;
    while(curri < SIZE){
        bin[curri++] = 0;
    }
    curri = 0;
    if(f < 0){
        f *= -1;
        bin[curri] = 1;
    }
    curri++;
    double base = (double)(f), denominator = 1;
    do{
        base = (double)(f);
        denominator = pow(2, (++exponent + 1));
        base /= denominator;
    } while(base >= 1);
    base *= 2;
    base -= 1;
    if(base < 0){
        base*= -1;
    }
    mantissa = OFFSET + exponent;
    int compare = mantissa, power = 0;
    exponent = 7;
    while(curri < MANTISSA_INDEX){
        power = (int)(pow(2,exponent--));
        if(compare - power >= 0){
            compare -= power;
            bin[curri] = 1;
        }
        curri++;
    }
    while(curri <  SIZE){
        base *= 2;
        if(base >= 1){
            bin[curri] = 1;
            base -= 1;
        }
        curri++;
    }
    curri = 0;
    exponent = 3;
    const int HEX_SIZE = 10;
    unsigned char* hex = (char*)malloc(sizeof(char) * HEX_SIZE);
    int value = 0, halfByteNumber = 2;
    hex[0] = '0';
    hex[1] = 'x';
    while(halfByteNumber < HEX_SIZE){
        while(exponent >= 0){
            if(bin[curri++] == 1){
                value += (int)(pow(2, exponent));
            }
            exponent--;
        }
        hex[halfByteNumber++] = switchCase(value);
        exponent = 3;
        value = 0;
    }
    return hex;
}

ramStorage* initializeRam(ramStorage* ram, int wordSize){
    ram->capacity = getUserDouble("\n\nEnter RAM capacity (in Bytes): ");
    ram->numOfWords = ((int)((int)(ram->capacity)/wordSize));
    ram->bytes = (byte*)malloc((int)(sizeof(byte) * ram->capacity));
    int index = 0;
    ram->ramStart = (char*)malloc(sizeof(char) * 10);
    ram->ramEnd = (char*)malloc(sizeof(char) * 10);
    ram->ramStart = getAddress((float)(0));
    for(float i = 0; i < ram->capacity; i++){
        index = (int)i;
        ram->bytes[index].bits = (int*)malloc(sizeof(int) * 8);
        ram->bytes[index].address = (char*)malloc(sizeof(char) * 10);
        ram->bytes[index].address = getAddress(i);
        if(i == ram->capacity - 1){
            ram->ramEnd = ram->bytes[index].address;
        }
    }
    ram->ramIndex = 0;
    ram->freeBytes = ram->capacity;
    ram->wordSize = wordSize;
    ram->usage = 0;
    return ram;
}

diskStorage* establishDiskStorage(diskStorage* d, int wordSize, float plusI){
    d->capacity = getUserDouble("\n\nEnter Size of Hard Disk Memory (in bytes): ");
    d->numOfWords = (int)(d->capacity / wordSize);
    d->freeBytes = d->capacity;
    d->wordSize = wordSize;
    d->usage = 0;
    d->bytes = (byte*)malloc((int)(sizeof(byte) * d->capacity));
    d->diskStart = (char*)malloc(sizeof(char) * 10);
    d->diskEnd = (char*)malloc(sizeof(char) * 10);
    d->diskStart = getAddress(++plusI);
    for(int i = 0; i < d->capacity; i++){
        d->bytes[i].bits = (int*)malloc(sizeof(int) * 8);
        d->bytes[i].address = (char*)malloc(sizeof(char) * 10);
        d->bytes[i].address = getAddress(plusI);
        if(i == d->capacity - 1){
            d->diskEnd = d->bytes[i].address;
        }
        plusI++;
    }
    d->diskIndex = 0;
    return d;
}

void printComputerState(ramStorage* r, diskStorage* d){
    printf("\n\n\n\nComputer Task Manager Performance:\n\n");
    printf("\tRAM:\n");
    printf("RAM Usage: %lf Bytes.\n", r->usage);
    printf("RAM Capacity: %lf Bytes.\n", r->capacity);
    printf("Available RAM Space: %lf Bytes.\n", r->freeBytes);
    printf("RAM Addressing Range: [%s, %s].", r->ramStart, r->ramEnd);
    
    printf("\n\n\tDisk:\n");
    printf("Disk Usage: %lf Bytes.\n", d->usage);
    printf("Disk Capacity: %lf Bytes.\n", d->capacity);
    printf("Available Drive Space: %lf Bytes.\n", d->freeBytes);
    printf("Disk Addressing Range: [%s, %s].\n", d->diskStart, d->diskEnd);
    
}

int main(){
    printf("\n\n\tComputer Archetecture Program:\n\n");
    int wordSize = 16;
    computerSystem* pc = createBaseComputer(wordSize);
    pc->ram = initializeRam(pc->ram, pc->wordSize);
    float startDisk = getNumericalAddress(pc->ram->ramEnd);
    printRam(0,10000, pc->ram);
    pc->disk = establishDiskStorage(pc->disk, pc->wordSize, startDisk);
    printDisk(0, 10000, pc->disk);
    printComputerState(pc->ram, pc->disk);
    return 0;
}





















