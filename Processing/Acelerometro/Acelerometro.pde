//import saito.objloader.*;
//OBJModel model;
PImage backufpb;
PFont font;
Table table;
int i=0;
int linhas;

void setup(){
  size(800,600);
  //model = new OBJModel (this,"CHALLENGER71.obj");
  //model.scale(40);
  font = createFont("fonteteste",32);
  table = loadTable("Teste06.11.txt","header,csv");
  linhas = table.getRowCount();
  backufpb = loadImage("back2.jpg");
  smooth(); noStroke();
}

void draw(){
  background(backufpb);
  ellipse(400,350,200,200);
  fill(255,0,0);
  rect(300,347,200,5);
  rect(397,250,5,200);
  
  TableRow row = table.getRow(i);
  float x = row.getFloat("GyroX");
  float y = row.getFloat("GyroY");
  float z = row.getFloat("GyroZ");
  float speed = row.getFloat("Velocidade");
  float latitude = row.getFloat("Latitude");
  float longitude = row.getFloat("Longitude");
  float accx = row.getFloat("AccX");
  float accy = row.getFloat("AccY");
  String hora = row.getString("HoraMinutosSegundos");
  
  textFont(font);
  fill(255,255,255);
  textSize(18);
  text("Yaw: " + (z) + "º",670,465);
  text("Pitch: " + (y) + "º",670,485);
  text("Roll: " + (x) + "º",670,505);
  text("Latitude: " + latitude,20,480);
  text("Longitude: " + longitude,20,500);
  text("Hora: " + hora,20,520);
  text("AccX: " + accx,400,540);
  text("AccY: " + accy,400,560);
  textSize(24);
  text(speed,85,300);

  textSize(21);
  text("km/h",100,330);

// ///G Force
  float faccX = (accx-1)*50;
  float faccY = accy*50;
  pushMatrix();
  translate(400+faccX,350+faccY);
  fill(0,0,255);
  ellipse(0,0,25,25);
  //box(75,25,250);  
  popMatrix();

  int s = second(); int m = minute(); int h = hour();
  int d = day();  int n = month(); int a = year();
  textSize(12);
  fill(255,255,255);
  text(d+"/"+n+"/"+a+"  "+h+":"+m+":"+s+"  Linha "+i, 5,595);

  i++;
  if (i==linhas){
    println("Fim de arquivo");
    delay(1000);
    exit();
  }
  delay(10);
}