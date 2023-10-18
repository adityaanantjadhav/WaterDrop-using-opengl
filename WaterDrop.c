#include<stdio.h>
#include<GL/glut.h>
int r1=0,r2=0,r3=0,q=0,xc,yc;
int dxc,dyc=300;

void bresnhamcircle(int r,int xc,int yc){
	int x=0,p;
	int y=r;
	int d= 3-2*r;
	glBegin(GL_POINTS);
	do{
		glVertex2d(x+xc,y+yc);
		glVertex2d(-x+xc,y+yc);
		glVertex2d(x+xc,-y+yc);
		glVertex2d(-x+xc,-y+yc);
		glVertex2d(y+xc,x+yc);
		glVertex2d(-y+xc,x+yc);
		glVertex2d(-y+xc,-x+yc);
		glVertex2d(y+xc,-x+yc);
		if(d<0){
			x=x+1;
			d=d+4*x+6;
		}
		else{
			x=x+1;
			y=y-1;
			d=d+4*x-4*y+10;
		}
		
	}while(x<=y);
	
}

void timer(int){
	
	glutPostRedisplay();
	glutTimerFunc(100,timer,0);
	dyc=dyc-10;
		if(q==99 && dyc<yc){
		r1=r1+10;							//after every 100ms r1 is incremented by 10 and then draw is called 																										
		if(r1>40)							//again so entire circle is shifted by 10 faster the time smoother 
			r2=r2+10;						//it looks
		if(r2>33){
 			r3=r3+10;
 		}
 		}
}

void wave(int w,int r){						//w is no of circles in a wave
 		float c=1.0f;						//c is color of circle
 		float cin=0.3/w;					//cin is change in color
 		for(int i=w;i>0;i--){
		 	for(int j=0;j<i;j++){
			 	glColor3f(0,0,c);				//color becomes dark from faint
			 	bresnhamcircle(r,xc,yc);
			 	r=r+1;
			 }c=c-cin;
		 }
	 	for(int i=0;i<w;i++){
	 		for(int j=0;j<i;j++){
			 	glColor3f(0,0,c);
			 	bresnhamcircle(r,xc,yc);
			 	r=r+1;
			 }
			 c=c+cin;
		 }
		 for(int i=w;i>0;i--){
		 	for(int j=0;j<i;j++){
			 	glColor3f(0,0,c);
			 	bresnhamcircle(r,xc,yc);
			 	r=r+1;			 	
			 }c=c-cin;
		 }
		 for(int i=0;i<w;i++){
			 	glColor3f(0,0,c);						//no color change
			 	bresnhamcircle(r,xc,yc);
			 	r=r+1;
		 }
}

void drop(){
	glBegin(GL_POINTS);
	float dcolor=0.5;
	glColor3f(0,0,0.5);
    if(dyc>yc){
		for(int a=20;a>10;a--)
		{
			bresnhamcircle(a,dxc,dyc);
		    glClear(GL_COLOR_BUFFER_BIT);
		    glColor3f(0,0,dcolor);
		    dcolor=dcolor+0.05;
		}
	}
    
}


void myMouse(int button, int state, int x, int y)
{	
	y=300-y;
	x=x-300;
	glBegin(GL_POINTS);
	
   if (button == GLUT_LEFT_BUTTON )
   {	
   		if(state==GLUT_UP){
	   		xc=x;
	   		yc=y;
	   		r1=0;
	   		r2=0;
	   		r3=0;
	   		q=99;
	   		dxc=xc;
	   		dyc=300;
	   	}
   }
}

 void Draw(){
 	glutMouseFunc(myMouse);
 	glClear(GL_COLOR_BUFFER_BIT);
 		drop();
 	if(r1>40){					
		wave(5,r2);				
	}
	if(r2>33){
		wave(4,r3);
	}
 	glEnd();
 	glFlush(); 	
 
 }

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(-300,-300);
	glutCreateWindow("bresnham");
	glClearColor(0,0,1,0);
	glColor3f(0,0,0.5);
	gluOrtho2D(-300,300,-300,300);
	glutDisplayFunc(Draw);
	glutTimerFunc(0,timer,0);
	         //repeatedlly call display func(draw)
	glutMainLoop();
	return 0;
}
