template <typename T>
struct vec2;

template <typename T>
struct vec3
{public:
	T x,y,z;
	vec3 () : x{0},y{0},z{0} {}
	vec3 (T x, T y, T z):x{x},y{y},z{z}{}
	vec3 (vec2<T> v):x{v.x},y{v.y},z{0}{}
	//+
	vec3 add(vec3 b){return vec3{x+b.x,y+b.y,z+b.z};}
	vec3 operator + (const vec3& b)const{return vec3{x+b.x,y+b.y,z+b.z};}
	vec3& operator += (const vec3& b){x+=b.x;y+=b.y;z+=b.z;return *this;}
	//-
	vec3 sub(vec3 b){return vec3{x-b.x,y-b.y,z-b.z};}
	vec3 operator - ()const{return vec3{-x,-y,-z};}
	vec3 operator - (const vec3& b)const{return vec3{x-b.x,y-b.y,z-b.z};}
	vec3& operator -= (const vec3& b){x-=b.x;y-=b.y;z-=b.z;return *this;}
	//*
	vec3 mul(vec3 b){return vec3{x*b.x,y*b.y,z*b.z};}
	vec3 operator * (const vec3& b)const{return vec3{x*b.x,y*b.y,z*b.z};}
	vec3& operator *= (const vec3& b){x*=b.x;y*=b.y;z*=b.z;return *this;}
	// /
	vec3 div(vec3 b){return vec3{x/b.x,y/b.y,z/b.z};}
	vec3 operator / (const vec3& b)const{return vec3{x/b.x,y/b.y,z/b.z};}
	vec3& operator /= (const vec3& b){x/=b.x;y/=b.y;z/=b.z;return *this;}
	//* n
	vec3 mln(T b){return vec3{x*b,y*b,z*b};}
	vec3 operator * (const T& b)const{return vec3{x*b,y*b,z*b};}
	vec3& operator *= (const T& b){x*=b;y*=b;z*=b;return *this;}
	// / n
	vec3 din(T b){return vec3{x/b,y/b,z/b};}
	vec3 operator / (const T& b)const{return vec3{x/b,y/b,z/b};}
	vec3& operator /= (const T& b){x/=b;y/=b;z/=b;return *this;}
	//length
	T length(){return sqrt(x*x+y*y+z*z);}
	//Norm
	vec3 norm(){return mln(1/length());}
	//scalar
	T scalar(vec3<T> b){return x*b.x+y*b.y+z*b.z;}
	//rot
	vec3 rotxy(T agl){return vec3<T>{cos(agl)*x-sin(agl)*y,sin(agl)*x+cos(agl)*y,z};}
	vec3 rotyz(T agl){return vec3<T>{x,cos(agl)*y-sin(agl)*z,sin(agl)*y+cos(agl)*z};}
	vec3 rotzx(T agl){return vec3<T>{cos(agl)*x-sin(agl)*z,y,sin(agl)*x+cos(agl)*z};}
	void info()
	{std::cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<'\n';}
	vec2<T> screen(T l){if(z!=0){return vec2<T>{x*l/z,y*l/z};}else{return vec2<T>{0,0};}}
	
	vec3 cross(vec3 other) {
		return vec3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
	}
	
	vec3 rotate(vec3 u, float a) {
		vec3<T> v=vec3<T>(x,y,z);
		u = u.norm();
		return v*cos(a) + (u.cross(v))*sin(a) + u*(u.scalar(v))*(1 - cos(a));
	}
};

template <typename T>
struct vec2
{public:
	T x,y;
	vec2 (T x, T y):x{x},y{y}{}
	vec2 (vec3<T> v):x{v.x},y{v.y}{}
	//+
	vec2 add(vec2 b){return vec2{x+b.x,y+b.y};}
	vec2 operator + (const vec2& b)const{return vec2{x+b.x,y+b.y};}
	vec2& operator += (const vec2& b){x+=b.x;y+=b.y;return *this;}
	//-
	vec2 sub(vec2 b){return vec2{x-b.x,y-b.y};}
	vec2 operator - ()const{return vec2{-x,-y};}
	vec2 operator - (const vec2& b)const{return vec2{x-b.x,y-b.y};}
	vec2& operator -= (const vec2& b){x-=b.x;y-=b.y;return *this;}
	//*
	vec2 mul(vec2 b){return vec2{x*b.x,y*b.y};}
	vec2 operator * (const vec2& b)const{return vec2{x*b.x,y*b.y};}
	vec2& operator *= (const vec2& b){x*=b.x;y*=b.y;return *this;}
	// /
	vec2 div(vec2 b){return vec2{x/b.x,y/b.y};}
	vec2 operator / (const vec2& b)const{return vec2{x/b.x,y/b.y};}
	vec2& operator /= (const vec2& b){x/=b.x;y/=b.y;return *this;}
	//* n
	vec2 mln(T b){return vec2{x*b,y*b};}
	vec2 operator * (const T& b)const{return vec2{x*b,y*b};}
	vec2& operator *= (const T& b){x*=b;y*=b;return *this;}
	// / n
	vec2 din(vec2 b){return vec2{x/b.x,y/b.y};}
	vec2 operator / (const T& b)const{return vec2{x/b,y/b};}
	vec2& operator /= (const T& b){x/=b;y/=b;return *this;}
	//length
	T length(){return sqrt(x*x+y*y);}
	//Norm
	vec2 norm(){return mln(1/length());}
	//rot
	vec2 rot(T agl){return vec2{cos(agl)*x-sin(agl)*y,sin(agl)*x+cos(agl)*y};}
	//cnv deg to rad
	static T cnv(T deg,T PI){return deg*PI/180;}
	void info()
	{std::cout<<"x: "<<x<<" y: "<<y<<'\n';}
};