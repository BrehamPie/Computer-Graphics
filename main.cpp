#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<windows.h>
#include<bits/stdc++.h>
using namespace std;
const float PI = acos(-1.0);
const float eps = 1e-6;
/*------Global Variables------*/
//Eye Positions
GLfloat eye_x,eye_y,eye_z;

//Look At Positions
GLfloat look_x, look_y,look_z;

//
GLfloat up_x, up_y, up_z;
//Angles
GLfloat alpha,bita,theta;
// Scale Factors
GLfloat S;
//Near and Far Plane
GLfloat nearP,farP;
void initialize() {
    eye_x = 0;//95;
    eye_y = 0;
    eye_z = 95;//50;
//    eye_x = 95;
//    eye_y = 20;
//    eye_z = 50;

    look_x = 0;//0;
    look_y = 0;
    look_z = 0;//50;

//    look_x = 0;
//    look_y = 20;
//    look_z = 50;

    up_x = 0;
    up_y = 1;
    up_z = 0;
    alpha = 0,bita = 0,theta = 0;
    S = 1;
    nearP = 4;
    farP = 500;
}
void Pitch(bool clock = true) {
    // Translate to origin
    if(clock)bita++;
    else bita--;
    //if(bita>270)bita = 270;
   // if(bita<-270)bita = -270;
    GLfloat dx = 0;//look_x - eye_x;
    GLfloat dy = 0;//look_y - eye_y;
    GLfloat dz = -eye_z;

    GLfloat new_x = dx;
    GLfloat new_y = dy*cos(bita*PI/180.0)-dz*sin(bita*PI/180.0);
    GLfloat new_z = dy*sin(bita*PI/180.0) +dz*cos(bita*PI/180.0);

    look_x = new_x;
    look_y = new_y;
    look_z = new_z-dz;
    cout<<"Bita:"<<bita<<' '<<new_y<<' '<<new_z<<endl;


}

void Roll(bool clock = true) {
    if(clock)alpha++;
    else alpha--;
    up_x = -sin(PI*alpha/180.0);
    up_y = cos(PI*alpha/180);
}
void Yaw(bool clock = true) {
    if(clock) theta++;
    else theta--;
    GLfloat dx = 0;//look_x - eye_x;
    GLfloat dy = 0;//look_y - eye_y;
    GLfloat dz = -eye_z;

    GLfloat new_x = dx*cos(theta*PI/180.0)+dz*sin(theta*PI/180.0);
    GLfloat new_y = dy;
    GLfloat new_z = -dx*sin(theta*PI/180.0) +dz*cos(theta*PI/180.0);

    look_x = new_x;
    look_y = new_y;
    look_z = -dz+new_z;
    cout<<"Yaw:"<<theta<<' '<<new_x<<' '<<new_z<<endl;
}
void zoom(bool positive = true) {
    float dx = look_x - eye_x;
    float dy = look_y - eye_y;
    float dz = look_z - eye_z;
    float unit_dist = sqrt(dx*dx+dy*dy+dz*dz);
    if(unit_dist<=.1 && positive)return;
    if(!positive)unit_dist*=-1;
    eye_x+=dx/unit_dist;
    eye_y+=dy/unit_dist;
    eye_z+=dz/unit_dist;
    look_x+=dx/unit_dist;
    look_y+=dy/unit_dist;
    look_z+=dz/unit_dist;
    cout<<eye_x<<' '<<eye_y<<' '<<eye_z<<endl;
    cout<<"Look:"<<look_x<<' '<<look_y<<' '<<look_z<<endl;
}
void drawLine(GLfloat A[],GLfloat B[],const GLfloat Color[]) {
    glColor3fv(&Color[0]);
    glBegin(GL_LINES);
    glVertex3fv(&A[0]);
    glVertex3fv(&B[0]);
    glEnd();
}
void drawQuad(GLfloat A[],GLfloat B[],GLfloat C[],GLfloat D[],GLfloat color[]) {
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3fv(&color[0]);
    glVertex3fv(&A[0]);
    glVertex3fv(&B[0]);
    glVertex3fv(&C[0]);
    glVertex3fv(&D[0]);
    glEnd();
    glPopMatrix();

}
void drawMainAxis() {
    glPushMatrix();
    glScalef(50,50,50);
    GLfloat A[]= {0,0,0};
    GLfloat B[]= {1,0,0};
    GLfloat D[] = {0,1,0};
    GLfloat E[] = {0,0,1};
    GLfloat c1[]= {1,0,0};
    GLfloat c2[] = {0,1,0};
    GLfloat c3[] = {0,0,1};
//    GLfloat D[] = {1,1,0};
    drawLine(A,B,c1);
    drawLine(A,D,c2);
    drawLine(A,E,c3);
    glPopMatrix();
    return;
}
void drawCube(GLfloat color[]) {
    GLfloat vertex[8][3] = {
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0},
        {1.0, 1.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {1.0, 0.0, 1.0},
        {1.0, 1.0, 1.0},
        {0.0, 1.0, 1.0}
    };
    GLubyte index[6][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {0, 1, 5, 4},
        {3, 2, 6, 7},
        {0, 3, 7, 4},
        {1, 2, 6, 5}
    };
    for(int i=0; i<6; i++) {
            color[0]+=.01;
            color[1]+=.01;
            color[2]+=.01;
        drawQuad(vertex[index[i][0]],
                 vertex[index[i][1]],
                 vertex[index[i][2]],
                 vertex[index[i][3]],color);
    }
}

void drawFloor() {
    glPushMatrix();
    glTranslatef(5,0,5);
    glScalef(45,5,75);
    GLfloat color[]= {.63,.63,.62};
    drawCube(color);
    glPopMatrix();
}
void drawSideWalls() {
    glPushMatrix();
    glScalef(5,50,80);
    GLfloat color[]= {.8,.86,.86};
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glScalef(50,50,5);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,80);
    glScalef(50,50,5);
    drawCube(color);
    glPopMatrix();
}

void drawRefrigerator() {
    glPushMatrix();
    glTranslatef(5,5,40);
    glScalef(12,30,10);
    GLfloat color[]= {.58,.9,.65};
    drawCube(color);
    glPopMatrix();
    /// Separator Lines
    glPushMatrix();
    GLfloat A[]= {0,5,0},B[]= {0,5,10};
    GLfloat C[] = {0,0,5},D[]= {0,20,5};
    GLfloat linecolor[]= {0,0.04,0.01};
    glTranslatef(17.01,5,40);
    drawLine(A,B,linecolor);
    glTranslatef(0,5,0);
    drawLine(A,B,linecolor);
    glTranslatef(0,5,0);
    drawLine(C,D,linecolor);
    glPopMatrix();
    /// Small horizontal handles
    glPushMatrix();
    glTranslatef(17,7.5,42.5);
    glScalef(.5,.5,5);
    GLfloat handleColor[]= {.08,.28,.12};
    drawCube(handleColor);
    glTranslatef(0,10,0);
    drawCube(handleColor);
    glPopMatrix();
    /// Small Vertical Handles
    glPushMatrix();
    glTranslatef(17,22.5,44);
    glScalef(.5,8,.5);
    drawCube(handleColor);
    glTranslatef(0,0,3);
    drawCube(handleColor);
    glPopMatrix();

    ///refrigerator display
    glPushMatrix();
    GLfloat p[]= {0,0,0},q[]= {0,1,0},r[]= {0,1,1},s[]= {0,0,1};
    glTranslatef(17.1,26.5,47);
    glScalef(0,1.5,2.5);
    drawQuad(p,q,r,s,linecolor);
    glPopMatrix();

}
void drawFoot() {
    glPushMatrix();
    glTranslatef(5,5,5);
    glScalef(9,5,32);
    GLfloat color[]= {.85,.81,.76};
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14,5,5);
    glScalef(35,5,9);
    drawCube(color);
    glPopMatrix();
}
void drawOvenBox() {
    ///Vertical disks
    glPushMatrix();
    glTranslatef(5,10,5);
    glTranslatef(0,0,19);
    glScalef(9,35,1);
    GLfloat color[] = {.05,.2,.05};
    drawCube(color);
    glTranslatef(0,0,12);
    drawCube(color);
    glPopMatrix();
    ///Horizontal Disks
    glPushMatrix();
    glTranslatef(5,10,25);
    glScalef(10,1,11);
    drawCube(color);
    glTranslatef(0,12,0);
    drawCube(color);
    glTranslatef(0,10,0);
    drawCube(color);
    glTranslatef(0,12,0);
    drawCube(color);
    glPopMatrix();
}
void drawOvens() {
    glPushMatrix();
    glTranslatef(7,22,24);
    glPushMatrix();
    glScalef(5,8,10);
    GLfloat color[]={.81,.47,.76};
    GLfloat color2[]={.22,.01,.19};
    GLfloat color3[]={.65,.77,.93};
    drawCube(color);
    glPopMatrix();
    glPushMatrix();
    glScalef(5.2,8.2,3);
    drawCube(color2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,2,2);
    glScalef(5.1,4.5,7.9);
    drawCube(color3);
    glPopMatrix();
    glPopMatrix();
}
void drawDrawers() {
    //Draw Front Drawers
    glPushMatrix();
    glTranslatef(5,10,5);
    glScalef(10,13,19);
    GLfloat color[] = {.64,.57,.5};
    drawCube(color);
    glPopMatrix();
    //Draw Upper Layer
    glPushMatrix();
    glTranslatef(5,23,5);
    glScalef(10,1,19);
    GLfloat ucolor[] = {.32,.28,.25};
    drawCube(ucolor);
    glPopMatrix();


    //Draw Side Drawers
    glPushMatrix();
    glTranslatef(14,10,5);
    glScalef(35,13,10);
    drawCube(color);
    glPopMatrix();

    //Draw Upper Layer
    glPushMatrix();
    glTranslatef(14,23,5);
    glScalef(35,1,10);
    drawCube(ucolor);
    glPopMatrix();
}
void drawPartition(){
    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(10,11.5,10);
    glScalef(.51,.31,9);
    GLfloat color[] = {1,0,0};
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(20,5,9.5);
    glScalef(1,13,1);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(35,5,9.5);
    glScalef(1,13,1);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(20,10,9.5);
    glScalef(15,.41,.61);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(35,13.5,9.5);
    glScalef(9,.41,.61);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(35,8.5,9.5);
    glScalef(9,.41,.61);
    drawCube(color);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(11,13.5,10);
    glScalef(9,.41,.61);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(11,8.5,10);
    glScalef(9,.41,.61);
    drawCube(color);
    glPopMatrix();

}
void drawWindow() {
    GLfloat p[]= {0,0,0},q[]= {0,1,0},r[]= {0,1,1},s[]= {0,0,1};
    GLfloat color[]= {.55,.94,.88};
    glPushMatrix();
    glTranslatef(5,5,5);
    glTranslatef(0.1,25,8);
    glScalef(1,12,8);
    drawQuad(p,q,r,s,color);
    glPopMatrix();

    glPushMatrix();
    GLfloat lineColor[]= {.54,.37,.27};
    glTranslatef(5,5,5);
    glTranslatef(1,25,8);
    glScalef(1,12,8);
    p[2]=0.5,q[2]=0.5;
    glLineWidth(3);
    drawLine(p,q,lineColor);
    p[2]=0,q[2]=0;
    glLineWidth(7.5);
    p[1]=-.1;
    q[1]=1.1;
    drawLine(p,q,lineColor);
    p[1]=0;
    q[1]=1;
    drawLine(q,r,lineColor);
    r[1]=1.1,s[1]=-.1;
    drawLine(r,s,lineColor);
    r[1]=1;
    s[1]=0;
    drawLine(p,s,lineColor);
    glLineWidth(1);
    glPopMatrix();
}
void drawBigWindow(){
    glPushMatrix();
    glTranslatef(0,20,53);
    glScalef(5.5,17,22);
    GLfloat in_color[] = {.4,.58,.94};
    drawCube(in_color);
    glPopMatrix();
    glPushMatrix();
    GLfloat out_color[] ={.12,0.01,0.05};
    glTranslatef(0,19,52);
    glScalef(5.4,19,23.7);
    drawCube(out_color);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,20,63);
    glScalef(5.6,17,1);
    drawCube(out_color);
    glPopMatrix();
}
void drawSideWindow(){
    glPushMatrix();
    glTranslatef(28,28,0);
    glScalef(12,15,5.5);
    GLfloat in_color[] = {.4,.58,.94};
    drawCube(in_color);
    glPopMatrix();
    glPushMatrix();
    GLfloat out_color[] ={.12,0.01,0.05};
    glTranslatef(27,27,0);
    glScalef(14,17,5.4);
    drawCube(out_color);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(33,28,0);
    glScalef(1,15,5.6);
    drawCube(out_color);
    glPopMatrix();
}
void drawStove(){
    glTranslatef(24,24,8);
    glPushMatrix();
    glScalef(16,2,6);
    GLfloat boxColor[]={.85,.34,.52};
    drawCube(boxColor);
    glPopMatrix();
    glPushMatrix();
    GLfloat switchC[]={0,0,0};
    glTranslatef(5,1.2,6.5);
    glScalef(.2,.4,.2);
    drawCube(switchC);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(13,1.2,6.5);
    glScalef(.2,.4,.2);
    drawCube(switchC);
    glPopMatrix();
    glPushMatrix();
    glColor3f(.78,.85,.34);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(5,2.5,3);
    glRotatef(90,1,0,0);
    gluCylinder(quadratic,1.5,1.5,1.0f,32,32);
    glPopMatrix();
    glPushMatrix();
    quadratic = gluNewQuadric();
    glTranslatef(13,2.5,3);
    glRotatef(90,1,0,0);
    gluCylinder(quadratic,1.5,1.5,1.0f,32,32);
    glPopMatrix();
    glTranslatef(-24,-24,-8);
}
void drawTable(){
    glTranslatef(5,0,30);
    glPushMatrix();
    glTranslatef(20,15,20);
    glScalef(25,2,15);
    GLfloat color[] = {.09,.02,.03};
    drawCube(color);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20,5,20);
    glScalef(1,12,1);
    drawCube(color);
    glTranslatef(24,0,0);
    drawCube(color);
    glTranslatef(0,0,14);
    drawCube(color);
    glTranslatef(-24,0,0);
    drawCube(color);
    glPopMatrix();
    glTranslatef(-5,0,-30);
}
void drawChair(float dx,float dy,bool Rotate = false){
    glPushMatrix();
    glTranslatef(35+dx,5,47+dy);
    if(Rotate){
        glRotatef(180,0,1,0);
    }
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(4,1,5);

    GLfloat color[] = {.77,.08,.19};
    drawCube(color);
    glPopMatrix();
    glPushMatrix();
    glScalef(4,13,1);
    drawCube(color);
    glTranslatef(0,0,4);
    glScalef(1,5.0/13.0,1);
    drawCube(color);
    glPopMatrix();
    glPopMatrix();

}
void drawChairs(){
    drawChair(0,0);
    drawChair(7,0);
    drawChair(4,22,true);
    drawChair(11,22,true);
}

void drawShelves(){
    GLfloat color[]={.4,.2,.21};
    GLfloat color2[] = {.04,.93,.05};
    glPushMatrix();
    glTranslatef(5,35,5);
    glScalef(5,5,12);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,35,9);
    glScalef(.4,5,.4);
    drawCube(color2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,35,13);
    glScalef(.4,5,.4);
    drawCube(color2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,40,5);
    glScalef(10,5,5);
    drawCube(color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18,40,10);
    glScalef(.4,5,.4);
    drawCube(color2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(22,40,10);
    glScalef(.4,5,.4);
    drawCube(color2);
    glPopMatrix();
}
void displayFunction() {
    // Clear Current Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Select Matrix for Operation
    glMatrixMode(GL_PROJECTION);

    // Load identity matrix
    glLoadIdentity();

    glFrustum(-6,6,-6,6,nearP,farP);
    // Select Matrix for Operation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Set Camera Definition
    gluLookAt(eye_x,eye_y,eye_z,look_x,look_y,look_z,up_x,up_y,up_z);
    glTranslatef(50,-25,0);
    glRotatef(270,0,1,0);
    glViewport(0,0,800,600);
    glScalef(S,S,S);
    drawMainAxis();
    drawOvens();
    drawPartition();
    drawStove();
    drawBigWindow();
    drawSideWindow();
    drawChairs();
    drawTable();
    drawFloor();
    drawSideWalls();
    drawRefrigerator();
    drawFoot();
    drawOvenBox();
    drawDrawers();
    drawShelves();
   // drawWindow();
    glFlush();
    glutSwapBuffers();


}
void Scale(bool positive = true){
    if(!positive)S-=.1;
    else S+=.1;
    if(S<0)S+=.1;
    if(S>2)S = 2;
}
void FrustumChange(bool positive = true){
    if(positive)nearP++;
    else nearP--;
}
void idleFunction() {
    glutPostRedisplay();
}
void keyBoardFunction(unsigned char key,int x,int y) {
    switch(key) {
    case '+':
        zoom();
        break;
    case '-':
        zoom(false);
        break;
    case '2':
        Pitch(false);
        break;
    case '8':
        Pitch();
        break;
    case '9':
        Roll();
        break;
    case '7':
        Roll(false);
        break;
    case '4':
        Yaw();
        break;
    case '6':
        Yaw(false);
        break;
    case '5':
        initialize();
        break;
    case 'x':
        eye_x--;
        break;
    case 'y':
        eye_y--;
        break;
    case 'z':
        eye_z--;
        break;
    case 'X':
        eye_x++;
        break;
    case 'Y':
        eye_y++;
        break;
    case 'Z':
        eye_z++;
        break;
    case 's':
        Scale();
        break;
    case 'S':
        Scale(false);
        break;
    case 'f':
        FrustumChange();
        break;
    case 'F':
        FrustumChange(false);
        break;
    }
}
int main(int argc,char **argv) {
    initialize();
    // Initialize GLUT Library.
    glutInit(&argc,argv);

    // Determine OpenGL Display mode for the to-be-created window.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);

    // Specify Upper Left Corner of to-be-created Window.
    glutInitWindowPosition(50,50);

    // Specify the size of to-be-created window in pixels.
    glutInitWindowSize(800,600);

    // Select Mode of Shading - Flat or Smooth. Need Lighting to see difference.
    glShadeModel(GL_SMOOTH);

    // Create Window with title.
    glutCreateWindow("Kitchen Room");
    // Enable Necessary Capabilities.
    glEnable(GL_DEPTH_TEST );
    // glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    //glCullFace(GL_BACK);

    // Specify Keyboard function.
    glutKeyboardFunc(keyBoardFunction);

    // Specify display function.
    glutDisplayFunc(displayFunction);

    // Specify idle function.
    glutIdleFunc(idleFunction);

    // Start event processing.
    glutMainLoop();
}





