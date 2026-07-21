using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp5
{
    class PocketMon
    {
        protected string name;
        protected int hp;
        protected int exp;
        protected int lv;

        public virtual void eat()
        {
            Console.WriteLine(name + " 밥먹음");
        }

        public virtual void sleep()
        {
            Console.WriteLine(name + " 잠잠");
        }

        public virtual bool play()
        {
            Console.WriteLine(name + " 놀기");
            return true;
        }

        public virtual bool exc()
        {
            Console.WriteLine(name + " 운동함");
            return true;
        }

        public virtual void lvCheck()
        {
            Console.WriteLine(name + " 레벨체크");
        }

        public void printState()
        {
            Console.WriteLine(name + " 상태확인");
            Console.WriteLine("hp:" + hp);
            Console.WriteLine("exp:" + exp);
            Console.WriteLine("lv:" + lv);
        }
    }

    class Picachu : PocketMon
    {
        public Picachu()
        {
            name = "Picachu";
            hp = 30;
            exp = 0;
            lv = 1;
            printState();
        }
        public override void eat()
        {
            base.eat();
            hp += 5;
        }

        public override void sleep()
        {
            base.sleep();
            hp += 10;
        }

        public override bool play()
        {
            base.play();
            hp -= 8;
            exp += 6;
            lvCheck();
            return hp > 0;//캐릭터 살았나, 죽었나
        }

        public override bool exc()
        {
            base.exc();
            hp -= 16;
            exp += 10;
            lvCheck();
            return hp > 0;//캐릭터 살았나, 죽었나
        }

        public override void lvCheck()
        {
            base.lvCheck();
            if(exp >= 20)
            {
                hp -= 20;
                lv++;
                Console.WriteLine(name + "의 레벨 1증가");
                printState();
            }
        }

        public void elec()
        {
            Console.WriteLine(name + " 백만볼트 공격");
        }
    }

    class Gobook : PocketMon
    {
        public Gobook()
        {
            name = "Gobook";
            hp = 20;
            exp = 0;
            lv = 1;
            printState();
        }
        public override void eat()
        {
            base.eat();
            hp += 3;
        }

        public override void sleep()
        {
            base.sleep();
            hp += 5;
        }

        public override bool play()
        {
            base.play();
            hp -= 6;
            exp += 3;
            lvCheck();
            return hp > 0;//캐릭터 살았나, 죽었나
        }

        public override bool exc()
        {
            base.exc();
            hp -= 9;
            exp += 5;
            lvCheck();
            return hp > 0;//캐릭터 살았나, 죽었나
        }

        public override void lvCheck()
        {
            base.lvCheck();
            if (exp >= 15)
            {
                hp -= 15;
                lv++;
                Console.WriteLine(name + "의 레벨 1증가");
                printState();
            }
        }

        public void water()
        {
            Console.WriteLine(name + " 물대포 공격");
        }
    }
    class Lee : PocketMon
    {
        public Lee()
        {
            name = "Lee";
            hp = 40;
            exp = 0;
            lv = 1;
            printState();
        }
        public override void eat()
        {
            base.eat();
            hp += 6;
        }

        public override void sleep()
        {
            base.sleep();
            hp += 13;
        }

        public override bool play()
        {
            base.play();
            hp -= 9;
            exp += 10;
            lvCheck();
            return hp > 0;//캐릭터 살았나, 죽었나
        }

        public override bool exc()
        {
            base.exc();
            hp -= 20;
            exp += 20;
            lvCheck();
            return hp > 0;//캐릭터 살았나, 죽었나
        }

        public override void lvCheck()
        {
            base.lvCheck();
            if (exp >= 30)
            {
                hp -= 30;
                lv++;
                Console.WriteLine(name + "의 레벨 1증가");
                printState();
            }
        }

        public void nungcool()
        {
            Console.WriteLine(name + " 넝쿨 공격");
        }
    }
    class Menu
    {
        private PocketMon p;//부모 타입 변수 선언. 객체는 없음

        public void selCh()
        {
            Console.WriteLine("캐릭터선택\n1.피카추(기본) 2.꼬부기 3.이상해씨");
            int ch = Int32.Parse(Console.ReadLine());
            //캐릭터를 생성해서 PocketMon으로 업캐스팅하여 저장
            switch (ch)
            {
                case 2:
                    p = new Gobook();
                    break;
                case 3:
                    p = new Lee();
                    break;
                default:
                    p = new Picachu();
                    break;
            }
        }
        public void run()
        {
            int m;
            bool flag = true;
            while (flag)
            {
                Console.WriteLine("1.밥먹기 2.잠자기 3.놀기 4.운동하기 5.상태확인 6.특기공격 7.종료");
                m = int.Parse(Console.ReadLine());
                switch (m)
                {
                    case 1:
                        p.eat();
                        break;
                    case 2:
                        p.sleep();
                        break;
                    case 3:
                        flag = p.play();
                        if (!flag)
                        {
                            Console.WriteLine("캐릭터 사망");
                        }
                        break;
                    case 4:
                        flag = p.exc();
                        if (!flag)
                        {
                            Console.WriteLine("캐릭터 사망");
                        }
                        break;
                    case 5:
                        p.printState();
                        break;
                    case 6:
                        if(p is Picachu)
                        {
                            ((Picachu)p).elec();
                        }
                        else if(p is Gobook)
                        {
                            ((Gobook)p).water();
                        }
                        else if (p is Lee)
                        {
                            ((Lee)p).nungcool();
                        }
                        break;
                    case 7:
                        flag = false;
                        break;
                }
            }
        }
    }
}
