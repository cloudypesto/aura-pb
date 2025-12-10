#pragma once

double linearToCubed(double input, double maxInput, double k);
double pctToVoltage(double input);
int sign(double num);


//Pose struct
    struct Pose
    {
        double x;
        double y;
        double heading;
        double rotation;

        public:
        //Constructor
        Pose(double x, double y, double heading);

        Pose(double x, double y, double heading , double rotation);

        /**
         * @brief Function to set this pose to a deisred pose
         * 
         * @param x What to set the x value
         * @param y What to set the y value
         * @param heading What to set the heading
         */
        void set(double x, double y, double heading);

        /**
         * @brief Function to set this pose to a deisred pose
         * 
         * @param pose The pose to set this pose to
         */
        void set(Pose pose);
    };


    //Point Struct
    struct Point
    {
        double x;
        double y;

        Point();

        Point(double x, double y);
        
        Point(Pose pose);

        void set(double x, double y);

        Point operator*(float scalar) const
        {
            return {x * scalar, y * scalar};
        }
        double operator*(Point point) const
        {
            return {x * point.x + y * point.y};
        }
        Point operator+(const Point& point) const
        {
            return {x + point.x, y + point.y};
        }
        Point operator-(const Point& point) const
        {
            return {x - point.x, y - point.y};
        }

        double cross(Point point)
        {
            return (x * point.y - y * point.x);
        }
    };