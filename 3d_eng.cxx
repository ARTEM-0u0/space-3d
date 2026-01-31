#include "vectors.cxx"
#include "list.cxx"
#include <sstream>
#include <fstream>
struct polygon
{
	public:
	vec3<float> a;
	vec3<float> b;
	vec3<float> c;
	
	polygon(){a={0,0,0};b=a;c=a;}
	polygon(vec3<float> A,vec3<float> B,vec3<float> C){a=A;b=B;c=C;}
	
	void add(vec3<float> num){a+=num;b+=num;c+=num;}
	void sub(vec3<float> num){a-=num;b-=num;c-=num;}
	void mul(vec3<float> num){a*=num;b*=num;c*=num;}
	void div(vec3<float> num){a/=num;b/=num;c/=num;}
	void mul(float num){a*=num;b*=num;c*=num;}
	void centr(){sub((a+b+c)/3);}
	void rotxy(float ag){a=a.rotxy(ag);b=b.rotxy(ag);c=c.rotxy(ag);}
	void rotyz(float ag){a=a.rotyz(ag);b=b.rotyz(ag);c=c.rotyz(ag);}
	void rotzx(float ag){a=a.rotzx(ag);b=b.rotzx(ag);c=c.rotzx(ag);}
	void rotate(vec3<float> u,float ag){a=a.rotate(u,ag);b=b.rotate(u,ag);c=c.rotate(u,ag);}

	string info(){
		string str="";
		str+=to_string(a.x)+' '+to_string(a.y)+' '+to_string(a.z)+'\n';
		str+=to_string(b.x)+' '+to_string(b.y)+' '+to_string(b.z)+'\n';
		str+=to_string(c.x)+' '+to_string(c.y)+' '+to_string(c.z)+'\n';
		return str;
	}
	void screen(float l,float ept){if(abs(a.z)<ept){a.z+=ept;}if(abs(b.z)<ept){b.z+=ept;}if(abs(c.z)<ept){c.z+=ept;}
	a=vec3<float>{0,0,a.z}+a.screen(l);b=vec3<float>{0,0,b.z}+b.screen(l);c=vec3<float>{0,0,c.z}+c.screen(l);}
};
struct ver_id
{
	public:
	int a;
	int b;
	int c;
	ver_id(){}
	ver_id(int A,int B,int C){a=A;b=B;c=C;}
};
struct model
{
	vec3<float>* verticles = nullptr;
    ver_id* polygons = nullptr;
    
	string name="";
	
    int vert_count = 0;
    int poly_count = 0;

    model() {}
	model(const model& m)
	{
		vert_count = m.vert_count;
		poly_count = m.poly_count;
		name = m.name;
		
		verticles = new vec3<float>[vert_count];
		polygons  = new ver_id[poly_count];
		
		for(int i = 0; i < vert_count; i++)
		{verticles[i] = m.verticles[i];}
		
		for(int i = 0; i < poly_count; i++)
		{polygons[i] = m.polygons[i];}
}
	model& operator=(const model&) = delete;
    ~model()
    {
        delete[] verticles;
        delete[] polygons;
    }
    void copy(model* m)
    {
    	vert_count=m->vert_count;
    	poly_count=m->poly_count;
    	
    	verticles=new vec3<float>[m->vert_count]; 
    	polygons=new ver_id[m->poly_count];
    	
    	for(int i=0;i<m->vert_count;i++)
    	{
    		verticles[i]=m->verticles[i];
    	}
    	
    	for(int i=0;i<m->poly_count;i++)
    	{
    		polygons[i]=m->polygons[i];
    	}
    }
    void add(vec3<float> num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]+=num;
    	}
    }
    void mul(vec3<float> num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]*=num;
    	}
    }
    void mul(float num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]*=num;
    	}
    }
    void centr()
    {
    	vec3<float> cenrtal;
    	for(int i=0;i<vert_count;i++)
    	{
    		cenrtal+=verticles[i];
    	}
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]-=(cenrtal/vert_count);
    	}
    }
    void rotxy(float num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]=verticles[i].rotxy(num);
    	}
    }
    void rotyz(float num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]=verticles[i].rotyz(num);
    	}
    }
    void rotzx(float num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]=verticles[i].rotzx(num);
    	}
    }
    void rotate(vec3<float> u,float num)
    {
    	for(int i=0;i<vert_count;i++)
    	{
    		verticles[i]=verticles[i].rotate(u,num);
    	}
    }
    float size(float l)
    {
    	float max_x=0;
    	float min_x=0;
    	
    	float max_y=0;
    	float min_y=0;
    	
    	float z=0;
    	
    	for(int i=0;i<vert_count;i++)
    	{
    		if(verticles[i].x>max_x)max_x=verticles[i].x;
    		if(verticles[i].x<min_x)min_x=verticles[i].x;
			
    		if(verticles[i].y>max_y)max_y=verticles[i].y;
			if(verticles[i].y<min_y)min_y=verticles[i].y;
			
    		z+=verticles[i].z;
    	}
    	z/=(vert_count);
    	float size=(max_x-min_x+max_y-min_y)/2;
    	if(z<0.001)z=0.001;
    	size*=l/z;
    	return size;
    }
    bool import(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
            return 0;

        string line;

        // ===== первый проход: считаем =====
        while (getline(file, line))
        {
            if (line.size() < 2) continue;

            if (line[0] == 'v' && line[1] == ' ')
                vert_count++;

            else if (line[0] == 'f' && line[1] == ' ')
                poly_count++;
        }

        file.close();

        if (vert_count == 0 || poly_count == 0)
            return 0;

        verticles = new vec3<float>[vert_count];
        polygons = new ver_id[poly_count];

        // ===== второй проход: заполняем =====
        file.open(filename);

        int v_i = 0;
        int f_i = 0;

        while (getline(file, line))
        {
            if (line.size() < 2) continue;

            stringstream ss(line);

            if (line[0] == 'v' && line[1] == ' ')
            {
                ss.ignore(2);
                ss >> verticles[v_i].x
                   >> verticles[v_i].y
                   >> verticles[v_i].z;
                v_i++;
            }
            else if (line[0] == 'f' && line[1] == ' ')
            {
                ss.ignore(2);

                string s1, s2, s3;
                ss >> s1 >> s2 >> s3;

                polygons[f_i].a = stoi(s1.substr(0, s1.find('/'))) - 1;
                polygons[f_i].b = stoi(s2.substr(0, s2.find('/'))) - 1;
                polygons[f_i].c = stoi(s3.substr(0, s3.find('/'))) - 1;

                f_i++;
            }
        }
        file.close();
        name=filename;
        return 1;
    }
};
class obj
{
	public:
	model* obj_mod=nullptr;
	
	vec3<float> pos={0,0,0};
	vec3<float> rot={0,0,0};
	
	obj(model* m){obj_mod=m;}
	void set(vec3<float> Pos, vec3<float> Rot)
	{
		pos=Pos;rot=Rot;
	}
};
class scene
{
	public:
	
	list<model*> models;
	list<obj> objects;
	
	vec3<float> cam_pos={0,0,0};
	vec3<float> cam_rot={0,0,0};
	
	scene(){}
	
	~scene() = default;
	
	void set_cam(vec3<float> pos, vec3<float> rot)
	{
		cam_pos=pos;cam_rot=rot;
	}
	void set_obj(int index, vec3<float> pos, vec3<float> rot)
	{
		objects.get_data(index)->set(pos,rot);
	}
	void add_obj(string name)
	{
		node<model*>* current = models.top;
		for(int i = 0; i < models.count; i++)
		{
			if(current->data->name == name)
			{
				objects.add(obj(current->data));
				return;
			}
			current = current->next;
		}
		model* m = new model();
		if(m->import(name))
		{
			models.add(m);
			objects.add(obj(m));
		}
		else
		{
			delete m;
		}
	}
	void remove_obj(int index)
	{
		node<obj>* current=objects.top;
		node<model*>* cur_mod=models.top;
		node<obj>* test=objects.get(index);
		
		int num=0;
		int index_model=0;
		
		for(int i=0;i<objects.count;i++)
		{
			if(current->data.obj_mod->name==test->data.obj_mod->name)
			{
				num++;
			}
			current=current->next;
		}
		
		for(int i=0;i<models.count;i++)
		{
			if(test->data.obj_mod==cur_mod->data)
			{
				index_model=i;
				break;
			}
			cur_mod=cur_mod->next;
		}
		
		if(num<=1)
		{
			
    delete models.get(index_model)->data; // сначала delete model*
    models.remove(index_model);           // потом убрать из списка

		}
		cout<<num<<' '<<index_model<<' '<<index<<'\n';
		objects.remove(index);
	}
	
};
class screen
{
	public:
	char* text;
	const char palete[17]=" .,-:_;!/){UG&#@";
	int size_x=0;
	int size_y=0;
	
	screen(int size_x, int size_y){
		this->size_x=size_x;
		this->size_y=size_y;
		text=new char[(size_x+1)*size_y];}
		
	void fill(char sym)
	{
		for(int i=0;i<size_y;i++)
		{
			for(int j=0;j<size_x;j++)
			{
				text[i*(size_x+1)+j]=sym;
			}
			text[i*(size_x+1)+size_x]='\n';
		}
	}
	void draw_dot(int x, int y, char sym)
	{
		if(x>=0 && x<size_x && y>=0 && y<size_y)
		text[x+y*(size_x+1)]=sym;
	}
	void draw_line(int x1, int y1, int x2, int y2, char sym)
	{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;
		int err = dx - dy;  
		
		while (true) {
			if(x1>=0&y1>=0&x1<size_x&y1<size_y)
			{
				draw_dot(x1, y1, sym);
			}
			if (x1 == x2 && y1 == y2) break;
			int e2 = 2 * err;
			
			if (e2 > -dy) {
				err -= dy;
				x1 += sx;
			}
			if (e2 < dx) {
				err += dx;
				y1 += sy;
			}
		}
	}
	int computeCode(float x, float y, float xmin, float ymin, float xmax, float ymax) {
		int code = 0;
		if (x < xmin) code |= 1;
		else if (x > xmax) code |= 2;
		if (y < ymin) code |= 4;
		else if (y > ymax) code |= 8;
		return code;
	}
	bool cohenSutherlandClip(float &x1, float &y1, float &x2, float &y2,float xmin, float ymin, float xmax, float ymax) {
		int code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
		int code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
		
		bool accept = false;
		while (true) {
			
			if ((code1 == 0) && (code2 == 0)) {
				accept = true;
				break;
			} else if (code1 & code2) {
				break;
			} else {
				int codeOut;
				float x, y;
				
				if (code1 != 0) codeOut = code1;
				else codeOut = code2;
				
				if (codeOut & 8) {
					x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
					y = ymax;
				} else if (codeOut & 4) {
					x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
					y = ymin;
				} else if (codeOut & 2) {
					y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
					x = xmax;
				} else if (codeOut & 1) {
					y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
					x = xmin;
				}
				if (codeOut == code1) {
					x1 = x;
					y1 = y;
					code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
				} else {
					x2 = x;
					y2 = y;
					code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
				}
			}
		}
		return accept;
	}
	void processLineSegment(float x1, float y1, float x2, float y2,char ch) {
		float xmin = 0, ymin = 0;
		float xmax = size_x, ymax = size_y;
		float clipped_x1 = x1, clipped_y1 = y1;
		float clipped_x2 = x2, clipped_y2 = y2;
		if (cohenSutherlandClip(clipped_x1, clipped_y1, clipped_x2, clipped_y2,xmin, ymin, xmax, ymax)) {
			draw_line(clipped_x1, clipped_y1, clipped_x2, clipped_y2,ch);
		} 
	}
	void draw_poly_norm(polygon p,float l,char sym,bool m)
	{
		vec3<float> v1=p.b-p.a;
		vec3<float> v2=p.c-p.a;
        
		 vec3<float> n={v1.y*v2.z-v1.z*v2.y,
		 						v1.z*v2.x-v1.x*v2.z,
		 						v1.x*v2.y-v1.y*v2.x};
		 n=n.norm();
		 n=n.mln(m*2-1);
		 if(n.scalar(p.a)<0)draw_poly(p,l,sym);
	}
	void draw_poly(polygon p,float l,char sym)
	{
		float ept=0.001;
		vec3<float> a;
		vec3<float> b;
		if(p.a.z>ept&&p.b.z>ept){
			a={p.a.x,p.a.y,p.a.z};
			b={p.b.x,p.b.y,p.b.z};
			a=a.screen(l);
			b=b.screen(l);
			a=a.add(vec3<float>(1,1,0));
			b=b.add(vec3<float>(1,1,0));
			a=a.mul(vec3<float>(size_x/2,size_y/2,1));
			b=b.mul(vec3<float>(size_x/2,size_y/2,1));
			processLineSegment(a.x,a.y,b.x,b.y,sym);
		}else if(p.a.z*p.b.z<=ept){
			float dz=p.b.z-p.a.z;
			if(abs(dz)<ept)dz=ept;
			float t=-p.a.z/dz;
			a={p.a.x+t*(p.b.x-p.a.x),p.a.y+t*(p.b.y-p.a.y),ept};
			if(p.a.z<=ept){
				b={p.b.x,p.b.y,p.b.z};
			}else{
				b={p.a.x,p.a.y,p.a.z};
			}
			if(a.z<ept)a.z=ept;
			if(b.z<ept)b.z=ept;
			a=a.screen(l);
			b=b.screen(l);
			a=a.add(vec3<float>(1,1,0));
			b=b.add(vec3<float>(1,1,0));
			a=a.mul(vec3<float>(size_x/2,size_y/2,1));
			b=b.mul(vec3<float>(size_x/2,size_y/2,1));
			processLineSegment(a.x,a.y,b.x,b.y,sym);
		}
		
		if(p.b.z>ept&&p.c.z>ept){
			a={p.b.x,p.b.y,p.b.z};
			b={p.c.x,p.c.y,p.c.z};
			a=a.screen(l);
			b=b.screen(l);
			a=a.add(vec3<float>(1,1,0));
			b=b.add(vec3<float>(1,1,0));
			a=a.mul(vec3<float>(size_x/2,size_y/2,1));
			b=b.mul(vec3<float>(size_x/2,size_y/2,1));
			processLineSegment(a.x,a.y,b.x,b.y,sym);
		}else if(p.b.z*p.c.z<=ept){
			float dz=p.c.z-p.b.z;
			if(abs(dz)<ept)dz=ept;
			float t=-p.b.z/dz;	
			a={p.b.x+t*(p.c.x-p.b.x),p.b.y+t*(p.c.y-p.b.y),ept};
			if(p.a.z<=ept){
				b={p.c.x,p.c.y,p.c.z};
			}else{
				b={p.b.x,p.b.y,p.b.z};
			}
			if(a.z<ept)a.z=ept;
			if(b.z<ept)b.z=ept;
			a=a.screen(l);
			b=b.screen(l);
			a=a.add(vec3<float>(1,1,0));
			b=b.add(vec3<float>(1,1,0));
			a=a.mul(vec3<float>(size_x/2,size_y/2,1));
			b=b.mul(vec3<float>(size_x/2,size_y/2,1));
			processLineSegment(a.x,a.y,b.x,b.y,sym);
		}
		
		if(p.c.z>ept&&p.a.z>ept){
			a={p.c.x,p.c.y,p.c.z};
			b={p.a.x,p.a.y,p.a.z};
			a=a.screen(l);
			b=b.screen(l);
			a=a.add(vec3<float>(1,1,0));
			b=b.add(vec3<float>(1,1,0));
			a=a.mul(vec3<float>(size_x/2,size_y/2,1));
			b=b.mul(vec3<float>(size_x/2,size_y/2,1));
			processLineSegment(a.x,a.y,b.x,b.y,sym);
		}else if(p.c.z*p.a.z<=ept){
			float dz=p.a.z-p.c.z;
			if(abs(dz)<ept)dz=ept;
			float t=-p.c.z/dz;	
			a={p.c.x+t*(p.a.x-p.c.x),p.c.y+t*(p.a.y-p.c.y),ept};
			if(p.c.z<=ept){
				b={p.a.x,p.a.y,p.a.z};
			}else{
				b={p.c.x,p.c.y,p.c.z};
			}
			if(a.z<ept)a.z=ept;
			if(b.z<ept)b.z=ept;
			a=a.screen(l);
			b=b.screen(l);
			a=a.add(vec3<float>(1,1,0));
			b=b.add(vec3<float>(1,1,0));
			a=a.mul(vec3<float>(size_x/2,size_y/2,1));
			b=b.mul(vec3<float>(size_x/2,size_y/2,1));
			processLineSegment(a.x,a.y,b.x,b.y,sym);
		}
		
	}
	void draw_obj(model* Obj,float l)
	{
		
		for(int i=0;i<Obj->poly_count;i++)
		{
			if(Obj->vert_count>Obj->polygons[i].a&&Obj->vert_count>Obj->polygons[i].b&&Obj->vert_count>Obj->polygons[i].c)
			{
				polygon p={{0,0,0},{0,0,0},{0,0,0}};
				p={Obj->verticles[Obj->polygons[i].a],Obj->verticles[Obj->polygons[i].b],Obj->verticles[Obj->polygons[i].c],};
				draw_poly(p,l,palete[(Obj->polygons[i].a+Obj->polygons[i].b+Obj->polygons[i].c)%15+1]);
			}
		}
	}
	void draw_obj_norm(model* Obj,float l,bool m)
	{
		float target=0.05;
		if(Obj->size(l)>target)
		{
			for(int i=0;i<Obj->poly_count;i++)
			{
				if(Obj->vert_count>Obj->polygons[i].a&&Obj->vert_count>Obj->polygons[i].b&&Obj->vert_count>Obj->polygons[i].c)
				{
					polygon p={{0,0,0},{0,0,0},{0,0,0}};
					p={Obj->verticles[Obj->polygons[i].a],Obj->verticles[Obj->polygons[i].b],Obj->verticles[Obj->polygons[i].c],};
					draw_poly_norm(p,l,palete[(Obj->polygons[i].a+Obj->polygons[i].b+Obj->polygons[i].c)%15+1],m);
				}
			}
		}else{
			draw_dot((Obj->verticles[0].x*l/Obj->verticles[0].z+1)*size_x/2,
							   (Obj->verticles[0].y*l/Obj->verticles[0].z+1)*size_y/2,
							   palete[int(Obj->size(l)/target*16)]);
		}
	}
	void draw_scene(scene* scn, float l)
	{
		node<obj>* current = scn->objects.top;
		for(int i = 0; i < scn->objects.count; i++)
		{
			 model temp = *current->data.obj_mod;   // копия на стеке
			 
			 temp.rotxy(current->data.rot.z);
			 temp.rotyz(current->data.rot.x);
			 temp.rotzx(current->data.rot.y);
			 
			 temp.add(current->data.pos);
			 temp.add(-scn->cam_pos);
			 
			 temp.rotxy(-scn->cam_rot.z);
			 temp.rotyz(-scn->cam_rot.x);
			 temp.rotzx(-scn->cam_rot.y);
			 
 			draw_obj(&temp, l);
 			current = current->next;
		}
	}
};
//sceeen




/*

	char ch=' ';
	while(ch!='a')
	{
		if(_kbhit()){
		ch=getch();
		cout<<int(ch);}
	}









*/