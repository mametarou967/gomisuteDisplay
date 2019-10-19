String getFilePath(enum GomiShubetsu gomiShubetsu,enum FileSize fizeSize,bool checked){
  String filePath;
  char buf[64] = {0};
  
  if(fizeSize == S50X50){
    filePath.concat("/pic50x50/");
  }else{
    filePath.concat("/pic150x150/");
  }

  if(checked){
    filePath.concat("checked/");
  }else{
    filePath.concat("normal/");
  }
  
  switch(gomiShubetsu){
  case KANEN:
    filePath.concat("moeru.jpg");
    break;
  case FUNEN:
    filePath.concat("moenai.jpg");
    break;
  case HOKAPURA:
    filePath.concat("plastic.jpg");
    break;
  case SHIGEN:
    filePath.concat("shigen.jpg");
    break;
  case RIPURA:
    filePath.concat("petbottle.jpg");
    break;
  case SONOTA:
    filePath.concat("sonohoka.jpg");
    break;
  default:
    filePath = "";
    break;
  }

  return filePath;
}
