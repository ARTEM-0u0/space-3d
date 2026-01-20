#include <iostream.h>
#include <conio.h>
#include "3d_eng.cxx"

//#include "vectors.cxx"

using namespace std;
int main(int argc, char *argv[]){
	//vec3<float>* v=new vec3<float>[10];
	scene scn;
	scn.add_obj("objects/test.obj");
	scn.add_obj("objects/test.obj");
	
	
	
	scn.objects.get(0)->data.pos.z=2;
	scn.objects.get(1)->data.pos.z=1;
	
	screen scr=screen(100,50);
	scr.fill(' ');
	scr.draw_scene(&scn,1);
	cout<<scr.text;
	cout<<sizeof(scr);
	
return 0;} 

/*
k=l/z
x*k
y*k

//код в main можно заменить на код внизу

model Obj;
	Obj.import("objects/Icosahedron.obj");
	//Obj.mul({3,3,3});
	screen scr=screen(100,50);
	scr.fill(' ');
	float a=0;
	bool flag=1;
	bool flag2=1;
	float x(0),y(0),z(3);
	while(true)
	{
		cout<<"\033[2J";
		cout<<"\033[?25l";
		Obj.centr();
		if(_kbhit()){			
			char ch=_getch();
			if(flag2)
			{
				if(ch=='x'){Obj.rotxy(0.1);}
				if(ch=='y'){Obj.rotyz(0.1);}
				if(ch=='z'){Obj.rotzx(0.1);}
			}else{
				if(ch=='x'){Obj.rotxy(-0.1);}
				if(ch=='y'){Obj.rotyz(-0.1);}
				if(ch=='z'){Obj.rotzx(-0.1);}
			}
			if(flag)
			{
				if(ch=='X'){x+=0.1;}
				if(ch=='Y'){y+=0.1;}
				if(ch=='Z'){z+=0.1;}
			}
			else
			{
				if(ch=='X'){x-=0.1;}
				if(ch=='Y'){y-=0.1;}
				if(ch=='Z'){z-=0.1;}
			}
			if(ch=='R'){flag=(!flag);}
			if(ch=='r'){flag2=(!flag2);}
		}
		Obj.add({x,y,z});
		screen scr=screen(100,50);
		scr.fill(' ');
		scr.draw_obj_norm(&Obj,1,0);
		a+=0.030;
		cout<<scr.text;
		for(int i=0;i<10000000;i++){}
	}
	cout<<scr.text;

	
*/
