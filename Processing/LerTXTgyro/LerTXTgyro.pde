PImage grid;
Table table;
int i=0;
int linhas;

void setup(){
  size(800,600,P3D);
  grid = loadImage("grid.jpg");
  table = loadTable("testerealp.txt","header,csv");
  linhas = table.getRowCount();
  smooth();
}

void draw(){
  background(0,0,255);
  //image(grid,0,0);
  TableRow row = table.getRow(i);
  float x = row.getFloat("x");
  float y = row.getFloat("y");
  float z = row.getFloat("z");

  text("Eixo x: " + radians(-x),150,500);
  text("Eixo y: " + radians(y),350,500);
  text("Eixo z: " + radians(z),550,500);

  pushMatrix();
  translate(200,300,0);
  rotateX(radians(-x));
  box(75,25,250);
  popMatrix();

  pushMatrix();
  translate(400,300);
  rotateY(radians(y));
  box(75,25,250);
  popMatrix();

  pushMatrix();
  translate(600,300);
  rotateZ(radians(z));
  box(75,25,250);
  popMatrix();

  println(x + "," + y + "," + z);
    i++;
    delay(50);
  if (i==linhas){
    println("Fim de arquivo");
    delay(1000);
    exit();
  }
}
