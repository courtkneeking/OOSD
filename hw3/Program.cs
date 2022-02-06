using System;
using System.Collections.Generic;

namespace HW3_2021_OOP
{
    static class Constants
    {
        public const double AccRate = 3.5;          // Acceleration rate for cars in m/s
        public const double AccRateEmpty = 2.5;     // Acceleration rate for light trucks in m/s
        public const double AccRateFull = 1.0;      // Acceleration rate for heavy trucks in m/s
        public const double DecRate = 7.0;          // Braking rate for cars in m/s
        public const double DecRateEmpty = 5.0;     // Braking rate for light trucks in m/s
        public const double DecRateFull = 2.0;      // Braking rate for light trucks in m/s
        public const double MpsToMph = 2.237;
    }

    class Program
    {
        static void Main(string[] args)
        {
            Car car = new Car(); car.SetDesiredSpeed(65.0);
            Truck truck1 = new Truck(4); truck1.SetDesiredSpeed(55.0);
            Truck truck2 = new Truck(8); truck2.SetDesiredSpeed(50.0);
            List<Vehicle> vehicles = new List<Vehicle>();
            vehicles.Add(car); vehicles.Add(truck1); vehicles.Add(truck2);
            for (int i = 0; i < 11; i++)
            {
                foreach (Vehicle v in vehicles)
                {
                    v.UpdateSpeed(1);
                    string s = v.GetType().ToString();
                    Console.WriteLine("{0} speed: {1:F} mph", s, v.GetCurrentSpeed());
                }
            }
        }
    }

    abstract class Vehicle
    {
        private double currentSpeed = 0.0;
        private double desiredSpeed;

        protected abstract void Accelerate(int secondsDelta);
        protected abstract void Decelerate(int secondsDelta);

        public double GetCurrentSpeed()
        {
            return currentSpeed;
        }

        public void SetDesiredSpeed(double mph)
        {
            desiredSpeed = mph;
        }

        protected void SetCurrentSpeed(double speed)
        {
            if(currentSpeed <= speed) // accelerating
            {
                if (speed > desiredSpeed) currentSpeed = desiredSpeed;
                else currentSpeed = speed;
            }
            else // braking
            {
                if (speed < desiredSpeed) currentSpeed = desiredSpeed;
                else currentSpeed = speed;
            }
        }

        public void UpdateSpeed(int seconds)
        {
            if (currentSpeed > desiredSpeed) Decelerate(seconds);
            else if (currentSpeed < desiredSpeed) Accelerate(seconds);
        }
    }

    class Car : Vehicle
    {
        protected override void Accelerate(int secondsDelta)
        {
            SetCurrentSpeed(GetCurrentSpeed() + Constants.AccRate * secondsDelta * Constants.MpsToMph);
        }

        protected override void Decelerate(int secondsDelta)
        {
            SetCurrentSpeed(GetCurrentSpeed() - Constants.DecRate * secondsDelta * Constants.MpsToMph);
        }
    }

    class Truck : Vehicle
    {
        private int loadWeight;      // in tons

        public Truck(int weight)
        {
            loadWeight = weight;
        }

        protected override void Accelerate(int secondsDelta)
        {
            if (loadWeight <= 5)
                SetCurrentSpeed(GetCurrentSpeed() + Constants.AccRateEmpty * secondsDelta * Constants.MpsToMph);
            else
                SetCurrentSpeed(GetCurrentSpeed() + Constants.AccRateFull * secondsDelta * Constants.MpsToMph);
        }

        protected override void Decelerate(int secondsDelta)
        {
            if (loadWeight <= 5)
                SetCurrentSpeed(GetCurrentSpeed() - Constants.DecRateEmpty * secondsDelta * Constants.MpsToMph);
            else
                SetCurrentSpeed(GetCurrentSpeed() - Constants.DecRateFull * secondsDelta * Constants.MpsToMph);
        }
    }
}
