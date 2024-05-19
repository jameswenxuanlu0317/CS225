#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image image, sticker1, sticker2, sticker3; 
  image.readFromFile("alma.png");
  sticker1.readFromFile("i.png");
  sticker2.readFromFile("i.png");
  sticker3.readFromFile("i.png");
  sticker1.scale(0.3);
  sticker2.scale(0.3);
  sticker3.scale(0.3);
  StickerSheet *sticker=new StickerSheet(image, 3);
  sticker->addSticker(sticker1, 100, 200);
  sticker->addSticker(sticker2, 300, 400);
  sticker->addSticker(sticker3, 500, 600);
  Image output=sticker->render();
  output.writeToFile("myImage.png");
  delete sticker;
  
  return 0;
}
