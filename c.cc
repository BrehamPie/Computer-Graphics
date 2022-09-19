#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

double Txval=0,Tyval=0,Tzval=0, arodure=60;
double eyex = 0;
double eyey = 0;
double eyez = 200;
double centerx = 0;
double centery = 0;
double centerz = 0;
double upx = 0;
double upy = 1;
double upz = 0;
double myval = 0;
double windowHeight=900, windowWidth=900;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
double far_id =1000.0;
double near_id = 4.0;




GLfloat up_fence_coordinate[8][3] = {
    {28.0,1.0,0.0},
    {28.0,3.0,0.0},
    {28.0,3.0,2.0},
    {28.0,1.0,2.0},

    {-28.0,1.0,0.0},
    {-28.0,3.0,0.0},
    {-28.0,3.0,2.0},
    {-28.0,1.0,2.0}

};
static GLubyte up_fence_indices[6][4] = {
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},
    {5,1,2,6},
    {1,3,0,4}

};
void draw_up_fence_cube() {
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++) {
        //glColor3f(0.1f, 0.1f, 0.1f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3fv(&up_fence_coordinate[up_fence_indices[i][0]][0]);
        glVertex3fv(&up_fence_coordinate[up_fence_indices[i][1]][0]);
        glVertex3fv(&up_fence_coordinate[up_fence_indices[i][2]][0]);
        glVertex3fv(&up_fence_coordinate[up_fence_indices[i][3]][0]);
    }
    glEnd();


}

GLfloat mini_fence_coordinate[8][3] = {
    {3.0,-5.0,0.0},
    {3.0,5.0,0.0},
    {1.0,5.0,0.0},
    {1.0,-5.0,0.0},

    {3.0,-5.0,2.0},
    {3.0,5.0,2.0},
    {1.0,5.0,2.0},
    {1.0,-5.0,2.0},

};
static GLubyte mini_fence_indices[6][4] = {
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},
    {5,1,2,6},
    {1,3,0,4}

};


void draw_mini_fence_cube() {
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++) {
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][0]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][1]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][2]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][3]][0]);
    }
    glEnd();
}

GLfloat house_coordinate[8][3] = {
    {-18.0,-5.0,-5.0},
    {-18.0,25.0,-5.0},
    {18.0,25.0,-5.0},
    {18.0,-5.0,-5.0},

    {-18.0,-5.0,-43.0},
    {-18.0,25.0,-43.0},
    {18.0,25.0,-43.0},
    {18.0,-5.0,-43.0},

};
static GLubyte house_indices[6][4] = {
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},
    {5,1,2,6},
    {1,3,0,4}

};

void draw_house_cube() {
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++) {
        glColor3f(0.5, 0, 1);
        glVertex3fv(&house_coordinate[house_indices[i][0]][0]);
        glVertex3fv(&house_coordinate[house_indices[i][1]][0]);
        glVertex3fv(&house_coordinate[house_indices[i][2]][0]);
        glVertex3fv(&house_coordinate[house_indices[i][3]][0]);
    }
    glEnd();
}

GLfloat house_down_roof_coordinate[8][3] = {
    //{-20.0,-5.0,-2.0},

    {-18.0,25.0,-5.0},
    {-25,30,3},
    {25,30,3},
    {18.0,25.0,-5.0},
    //{20.0,-5.0,-2.0},

    {-18.0,25.0,-43.0},
    {-25,30.0,-49.0},
    {25,30,-49.0},
    {18.0,25.0,-43.0},

};
static GLubyte house_down_roof_indices[6][4] = {
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},
    {5,1,2,6},
    {1,3,0,4}

};


void draw_house_down_roof_cube() {
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++) {
        // glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
        glColor3f(.239, .047, 0.008);//Bronze
        glVertex3fv(&house_down_roof_coordinate[house_down_roof_indices[i][0]][0]);
        glVertex3fv(&house_down_roof_coordinate[house_down_roof_indices[i][1]][0]);
        glVertex3fv(&house_down_roof_coordinate[house_down_roof_indices[i][2]][0]);
        glVertex3fv(&house_down_roof_coordinate[house_down_roof_indices[i][3]][0]);
    }
    glEnd();
}



GLfloat house_top_roof_pyramid[5][3] = {

    {-25,30,3},
    {25,30,3},
    //{20.0,-5.0,-2.0},
    {-25,30.0,-49.0},
    {25,30,-49.0},
    {0,48,-26.0}

};

static GLubyte house_top_roof_pyramid_Indices[4][3] = {
    {4, 3, 2},
    {4, 2, 0},
    {4, 3, 1},
    {4, 0, 1}
};


void draw_house_roof_top_pyramid() {
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++) {
        glColor3f(.239, .047, 0.008);//Bronze
        glVertex3fv(&house_top_roof_pyramid[house_top_roof_pyramid_Indices[i][0]][0]);
        glVertex3fv(&house_top_roof_pyramid[house_top_roof_pyramid_Indices[i][1]][0]);
        glVertex3fv(&house_top_roof_pyramid[house_top_roof_pyramid_Indices[i][2]][0]);
    }
    glEnd();
}

GLfloat door_coordinate[4][3] = {
    {-9.0, -5, -4.989},
    {-9.0, 7, -4.989},
    {-1.0, 7, -4.9899},
    {-1.0, -5, -4.9899}
};



void draw_door() {

    glBegin(GL_QUADS);

    glColor3f(0,1,0);
    glVertex3fv(&door_coordinate[0][0]);
    glVertex3fv(&door_coordinate[1][0]);
    glVertex3fv(&door_coordinate[2][0]);
    glVertex3fv(&door_coordinate[3][0]);

    glEnd();
}

GLfloat window_coordinate[4][3] = {
    {4.0, 9, -4.989},
    {4.0, 13, -4.989},
    {8.0, 13, -4.9899},
    {8.0, 9, -4.9899}
};



void draw_window() {

    glBegin(GL_QUADS);

    glColor3f(0,1,0);
    glVertex3fv(&window_coordinate[0][0]);
    glVertex3fv(&window_coordinate[1][0]);
    glVertex3fv(&window_coordinate[2][0]);
    glVertex3fv(&window_coordinate[3][0]);

    glEnd();
}





void draw_every() {





    draw_house_cube();
    draw_house_down_roof_cube();
    draw_house_roof_top_pyramid();
    draw_door();


    draw_window();
    glTranslatef(5.50,0,0);
    draw_window();
    glTranslatef(-5.5,0,0);

    draw_window();
    glTranslatef(0,5.5,0);
    draw_window();
    //  glTranslatef(0,-5.5,0);
    draw_window();
    glTranslatef(5.50,0,0);
    draw_window();
    glTranslatef(-5.5,0,0);
    glTranslatef(0,-5.5,0);




    //one side
    draw_up_fence_cube();
    glTranslatef(0.0,-3,0);
    draw_up_fence_cube();
    glTranslatef(0.0,3,0);
    // draw_mini_fence_cube();
    // make_multi_min();
    for( GLint i=0; i<6; i++) {

        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
        glTranslatef(4.0,0,0);
    }
    glTranslatef(-24.0,0,0);
    for( GLint i=0; i<6; i++) {
        glTranslatef(-4.0,0,0);
        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
    }
    glTranslatef(24.0,0,0);



    // 2nd side
    glRotatef(90, 0, 1, 0 );
    glTranslatef(24,0,24);
    draw_up_fence_cube();
    glTranslatef(0.0,-3,0);
    draw_up_fence_cube();
    glTranslatef(0.0,3,0);
    // draw_mini_fence_cube();
    // make_multi_min();
    for( GLint i=0; i<6; i++) {

        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
        glTranslatef(4.0,0,0);
    }
    glTranslatef(-24.0,0,0);
    for( GLint i=0; i<6; i++) {
        glTranslatef(-4.0,0,0);
        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
    }
    glTranslatef(24.0,0,0);


    glRotatef(90, 0, 1, 0 );
    glTranslatef(24,0,24);
    draw_up_fence_cube();
    glTranslatef(0.0,-3,0);
    draw_up_fence_cube();
    glTranslatef(0.0,3,0);
    // draw_mini_fence_cube();
    // make_multi_min();
    for( GLint i=0; i<6; i++) {

        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
        glTranslatef(4.0,0,0);
    }
    glTranslatef(-24.0,0,0);
    for( GLint i=0; i<6; i++) {
        glTranslatef(-4.0,0,0);
        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
    }
    glTranslatef(24.0,0,0);

    glRotatef(90, 0, 1, 0 );
    glTranslatef(24,0,24);
    draw_up_fence_cube();
    glTranslatef(0.0,-3,0);
    draw_up_fence_cube();
    glTranslatef(0.0,3,0);
    // draw_mini_fence_cube();
    // make_multi_min();
    for( GLint i=0; i<6; i++) {

        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
        glTranslatef(4.0,0,0);
    }
    glTranslatef(-24.0,0,0);
    for( GLint i=0; i<6; i++) {
        glTranslatef(-4.0,0,0);
        // glRotatef(60, 0, 0, 1 );
        draw_mini_fence_cube();
    }
    glTranslatef(24.0,0,0);


}
double limit = 360;
double roll_value = 5;
GLfloat angleYaw = 90.0, anglePitch = 270.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 360.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 180.0, angleRollLimit2 = -90.0;
int f=0;
double scale_x = 1;
double scale_y = 1;
double scale_z = 1;
int bv = 0;



void b_swap() {
    if(bv==1) {
        int tmp = eyey;
        eyey = eyez;
        eyez = tmp;

        tmp = upy;
        upy = upz;
        upz = tmp;

    }
}

void init(int d) {
    if(d!=f) {
        angleYaw = 90.0;
        anglePitch = 270.0;
        angleRoll = 90.0;
        eyex = 0;
        eyey = 0;
        eyez = 200;
        centerx = 0;
        centery = 0;
        centerz = 0;
        upx = 0;
        upy = 1;
        upz = 0;
        f=d;
        scale_x=1.5;
        scale_y=1.5;
        scale_z=1.5;
    }
    b_swap();
}

void setCameraEye_Yaw() { // y axis , y u
    init(1);
    f=1;
    centery = 200.0*(cos(angleYaw*3.1416/180.0));
//    eyex = 200.0*(cos(angleYaw*3.1416/180.0));//-sin(anglePitch*3.1416/180.0));
//    eyez = 200.0*(sin(angleYaw*3.1416/180.0));//+cos(anglePitch*3.1416/180.0));
}

void setCameraEye_Roll() { // z axis ,i o
    init(2);
    f=2;
    upx = 200.0*(cos(angleRoll*3.1416/180.0));//-sin(angleYaw*3.1416/180.0));
    upy = 200.0*(sin(angleRoll*3.1416/180.0));//+cos(angleYaw*3.1416/180.0));

    cout<<upx<<' '<<upy<<endl;
//    eyex = 200.0*sin(angleYaw*3.1416/180.0);
//    eyey = 200.0*(cos(angleYaw*3.1416/180.0));
//    upx = 1;
//    upy = 1;
//    upz = 1;

//    upx = eyex;
//    upy = eyey;
//    upz = 0;
}

void setCameraEye_Pitch() { // x axis , r t
    init(3);
    f=3;

    centerx = 400.0*(cos(anglePitch*3.1416/180.0));
}

//void setCameraEye_all()
//{
//    eyex = cos(angleYaw)*cos(anglePitch)*eyex+eyey*(cos(angleYaw)*sin(anglePitch)*sin(angleRoll)-sin(angleYaw)*cos(angleRoll))+eyez*(cos(angleYaw)*sin(anglePitch)*cos(angleRoll)+sin(angleYaw)*sin(angleRoll));
//    eyey = sin(angleYaw)*cos(anglePitch)*eyex+eyey*(sin(angleYaw)*sin(anglePitch)*sin(angleRoll)+cos(angleYaw)*cos(angleRoll))+eyez*(sin(angleYaw)*sin(anglePitch)*cos(angleRoll)-cos(angleYaw)*sin(angleRoll));
//    eyez = -sin(anglePitch)*eyex + eyey*cos(anglePitch)*sin(angleRoll)+eyez*cos(anglePitch)*cos(angleRoll);
//}

void normal_view() {
//    init(5);
//    f=5;
    bv = 0;
    //b_swap();
    //bv=0;
    init(5);

}

void bird_view() {
//     init(6);
//     f=6;
    bv = 1;
    b_swap();

}



bool ini = 0;
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5, -5, 5, near_id, far_id);

    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez, centerx,centery,centerz, upx,upy,upz); // camera , ,

    glViewport(0, 0, windowHeight, windowWidth);
    //glRotatef(30, 0, 0, 1 );
    glScalef(scale_x,scale_y,scale_z);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    // glTranslatef(0,0,Tzval);
    //glTranslatef(Txval,Tyval,Tzval);
//       glTranslatef(Txval,0,0);
    //setCameraEye_Pitch();
    if(ini==0) {
        setCameraEye_Pitch();
        ini=1;
    }


    draw_every();


    glFlush();
    glutSwapBuffers();
}








void myKeyboardFunc( unsigned char key, int x, int y ) {
    switch ( key ) {
    case 'r':
        if(anglePitch>=anglePitchLimit1)
            break;
        anglePitch += roll_value;

        //printf("%lf  p\n ", anglePitch);
        //if(anglePitch > limit)
        //    anglePitch -= limit;
        setCameraEye_Pitch();
        glutPostRedisplay();

        // eyex = eyex;

        break;
    case 't':
        if(anglePitch==anglePitchLimit2)
            break;
        anglePitch -= roll_value;
        //if(anglePitch < 0)
        //   anglePitch += limit;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'y':
        if(angleYaw==angleYawLimit1)
            break;
        angleYaw += roll_value;
        //if(angleYaw > limit)
        //    angleYaw -= limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'u':
        if(angleYaw==angleYawLimit2)
            break;
        angleYaw -= roll_value;
        //if(angleYaw < 0)
        //   angleYaw += limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'i':
        //if(angleRoll>=angleRollLimit1)
        //   break;
        angleRoll += roll_value;
        //if(angleRoll >= limit)
        //    angleRoll -= limit;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'o':
        //if(angleRoll<=angleRollLimit2)
        //   break;
        angleRoll -= roll_value;
        //if(angleRoll < 0)
        //    angleRoll += limit;
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;

//    case 'y':
//    case 'Y':
//        bRotate = !bRotate;
//       // uRotate = false;
//        axis_x=0.0;
//        axis_y=1.0;
//
//        break;

//    case 'x':
//    case 'X':
//        uRotate = !uRotate;/**<  */
//        //bRotate = false;
//        axis_x=1.0;
//        axis_y=0.0;
//
//        break;
    case 'a':
        eyex-=2;
        break;
    case 'd':
        eyex+=2;
        break;
    case 'w':
        eyey+=2;
        break;
    case 's':
        eyey-=2;
        break;
    case 'f':
        eyez+=2;
        glutPostRedisplay();
        break;
    case 'g':
        eyez-=2;
        glutPostRedisplay();
        break;
    case 'z':
        //eyez-=2;
        //init(4);
        f=4;
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'c':
        //eyez-=2;
        //init(4);
        f=4;
        if(scale_x==0.05)break;
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;
    case 'b':
        bird_view();
        break;
    case 'n':
        normal_view();
        break;
    case 27:	// Escape key
        exit(1);
    }
}

/*
r, t => pitch
y, u => Yaw
i, o => roll
w, s => y move
a, d => x move
f, g => z move, zoom in/out
c, z => scaling


*/


void animate() {
    if (bRotate == true) {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true) {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}


int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(200,200);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
