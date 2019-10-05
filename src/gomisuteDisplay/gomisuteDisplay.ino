#include <M5Stack.h>

char csvBuffer[400][3][10] = {0};

// 最終的にはnumberなんかはenumにしたい
// bufferも併せてclass化できると良い

bool loadGomiListFromCSV(const char* fileName,int number){
  File file = SD.open(fileName);
  const char delimiter = ',';
  const char lineBreakChar1 = 0xd;
  const char lineBreakChar2 = 0xa;
  const char endOfFile = 0xff;

  int row = 0;
  int column = 0;
  char buf[64] = {0};
  int bufIndex = 0;
  int dummyCount = 0;

  while(1){
    char c = file.read();
    switch(c){
    case delimiter:
      Serial.printf("delimiter\n");
      // 文字のコピー
      if((column == 0 || column == 1 || column == ( number - 1 + 2 )) && (row > 0)){
        int csvBufferIndexX = row - 1;
        int csvBufferIndexY = 0;
        if(column == 0 || column == 1){ csvBufferIndexY = column; }
        else{ csvBufferIndexY = 2;}
        Serial.printf("[%d][%d]%d,%d,%d,%d,%d,write\n",csvBufferIndexX,csvBufferIndexY,buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
        memcpy(csvBuffer[csvBufferIndexX][csvBufferIndexY],buf,10);
      }
      column = column + 1;
      // bufferの初期化
      bufIndex = 0;
      memset(buf,0x0,64);
      break;
    case lineBreakChar1:
      Serial.printf("breakChar1\n");
      break;
    case lineBreakChar2:
      Serial.printf("breakChar2\n");
      row = row + 1;
      column = 0;
      // bufferの初期化
      bufIndex = 0;
      memset(buf,0x0,64);
      break;
    case endOfFile:
      Serial.printf("endOfFile\n");
      break;
    default:
      buf[bufIndex++] = c;
      Serial.printf("0x%d\n",c);
    }
    dummyCount = dummyCount + 1;
    if(dummyCount > 200){
      Serial.printf("dummyCount = 0x%d => break\n",dummyCount);
      break;
    }
  }
}


void setup() {

  Serial.begin(115200);
  Serial.println("start");
  
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(WHITE);

  // File file = SD.open("/test.csv");
  Serial.println("hello");
  // Serial.println(file);

  loadGomiListFromCSV("/test.csv",3);
  Serial.println("hello2");

  /*
  for(int k = 0;k < 20;k++){
    Serial.printf("%d----",k);
    
    for(int m = 0;m < 10;m++){
      Serial.printf("%d\n",csvBuffer[k][0][m]);
    }

    for(int m = 0;m < 10;m++){
      Serial.printf("%d\n",csvBuffer[k][1][m]);
    }

    for(int m = 0;m < 10;m++){
      Serial.printf("%d\n",csvBuffer[k][2][m]);
    }
    
    // printPt16(csvBuffer[k][2],0,k * 16,BLACK);
  }
  */
  /*
  for(int i = 0;i < 38;i++){
    buf[0] = file.read();
    Serial.printf("0x%x\n",buf[0]);
  }
  */
  // buf[10] = '\n';
  // M5.Lcd.print(buf);
  Serial.println("end");
  
  printMainText("本日 10/30(月)",BLACK,0);
  printMainPicture("/pic150x150/moeru.jpg",0);
  printMainText("明日 10/31(火)",BLACK,1);
  printMainPicture("/pic150x150/can.jpg",1);
  // Sub
  printSubText("水",BLACK,0);
  printSubPicture("/pic50x50/moenai.jpg",0);
  printSubText("木",BLACK,1);
  printSubPicture("/pic50x50/petbottle.jpg",1);
  printSubText("金",BLACK,2);
  printSubPicture("/pic50x50/plastic.jpg",2);
  printSubText("土",BLUE,3);
  printSubPicture("/pic50x50/shigen.jpg",3);
  printSubText("日",RED,4);
  printSubPicture("/pic50x50/sonohoka.jpg",4);
  printSubText("月",BLACK,5);
  printSubPicture("/pic50x50/blank.jpg",5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
