char *getFilePath(enum GomiShubetsu gomiShubetsu,enum FileSize fizeSize){
  char *filePath = NULL;
  
  switch(gomiShubetsu){
  case KANEN:
    if(fizeSize == S50X50){
      filePath = "/pic50x50/moeru.jpg";
    }else{
      filePath = "/pic150x150/moeru.jpg";
    }
    break;
  case FUNEN:
    if(fizeSize == S50X50){
      filePath = "/pic50x50/moeru.jpg";
    }else{
      filePath = "/pic150x150/moeru.jpg";
    }
    break;
  case HOKAPURA:
    if(fizeSize == S50X50){
      filePath = "/pic50x50/moenai.jpg";
    }else{
      filePath = "/pic150x150/moenai.jpg";
    }
    break;
  case SHIGEN:
    if(fizeSize == S50X50){
      filePath = "/pic50x50/shigen.jpg";
    }else{
      filePath = "/pic150x150/shigen.jpg";
    }
    break;
  case RIPURA:
    if(fizeSize == S50X50){
      filePath = "/pic50x50/petbottle.jpg";
    }else{
      filePath = "/pic150x150/petbottle.jpg";
    }
    break;
  case SONOTA:
    if(fizeSize == S50X50){
      filePath = "/pic50x50/sonohoka.jpg";
    }else{
      filePath = "/pic150x150/sonohoka.jpg";
    }
    break;
  default:
    break;
  }

  return filePath;
}
