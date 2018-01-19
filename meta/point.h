#ifndef MY_POINT_H
#define MY_POINT_H

namespace point{
    //1d point class
    template<typename T>
    class Point1D{
    protected:
        T x;
    public:
        Point1D(T val):x(val){};
        Point1D(): x(0){};
        virtual ~Point1D(){};

    public:
        virtual T getX()const{ return x;}
        virtual void setX(const T val){x = val;}
    };

    //2d point class
    template<typename T>
    class Point2D:public Point1D<T>{
    protected:
        T y;
    public:
		Point2D(T vx, T vy) :y(vy) { setX(vx); };
		Point2D() : y(0) { setX(0); };
        virtual ~Point2D(){};
    public:
        virtual T getY()const{ return y;}
        virtual void setY(const T val){y = val;}
    };

    //3d point class 
    template<typename T>
    class Point3D:public Point2D<T>{
    protected:
        T z;
    public:
        Point3D(T vx,T vy,T vz):z(vz){
			setX(vx);
			setY(vy);
		};
        Point3D(): z(0){
			setX(0);
			setY(0);
		};
        virtual ~Point3D(){};
    public:
        virtual T getZ()const{ return z;}
        virtual void setZ(const T val){z = val;}
    };

    template<typename T>
    class YPoint{
    public:
        YPoint(T x,T y,T z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        YPoint(){
            x = y = z = 0.0;
        }
        virtual ~YPoint(){}
    public:
        virtual T getX()const {return x;}
        virtual T getY()const {return y;}
        virtual T getZ()const {return z;}

        virtual void setX(const T val){x = val;};
        virtual void setY(const T val){y = val;};
        virtual void setZ(const T val){z = val;};

    public:
        const YPoint& operator=(const YPoint p){
            this->setX(p.getX());
            this->setY(p.getY());
            this->setZ(p.getZ());
            return *this;
        }

    public:
        T x;
        T y;
        T z;
    };
};

#endif