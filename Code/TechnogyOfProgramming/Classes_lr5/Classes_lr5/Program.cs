using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Classes_lr5
{
    abstract class IVehicle
    {
        public virtual float Speed()
        {
            return 0.0f;
        }

        public virtual string Mark()
        {
            return "None";
        }
    }

    class Car : IVehicle
    {
        public override float Speed()
        {
            return 40.0f;
        }

        public override string Mark()
        {
            return "Car";
        }
    }

    class Train : IVehicle
    {
        public override float Speed()
        {
            return 30.0f;
        }

        public override string Mark()
        {
            return "Train";
        }
    }

    class ExpressTrain : IVehicle
    {
        public override float Speed()
        {
            return 100.0f;
        }

        public override string Mark()
        {
            return "Express train";
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            IVehicle[] vehicles = { new Car(), new Train(), new ExpressTrain()};
            foreach (var vehicle in vehicles)
            {
                Console.WriteLine(vehicle.Mark() + " moves with " + vehicle.Speed() + " miles per second.");
            }
            Console.ReadKey();
        }
    }
}
