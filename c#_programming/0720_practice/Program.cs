using ConsoleApp1;
using ConsoleApp5;

/* 포켓몬
Menu menu = new Menu();
menu.selCh();
menu.run();
*/

/* 응용
Service service = new Service();
service.PrintAll();

service.AddProduct("노트북", 1500000, 5);
service.AddProduct("마우스", 30000, 50);
service.AddProduct("키보드", 80000, 20);
service.PrintAll();

service.SearchProduct(101);

Console.WriteLine("\n-> 102번 방(마우스) 정보 수정 중...");
service.UpdateProduct(102, 35000, 100);
service.SearchProduct(102);

Console.WriteLine("\n-> 103번 방(키보드) 삭제 중...");
service.DeleteProduct(103);

service.PrintAll();
*/

/* 인덱서 사용 (.ContainsKey())
Warehouse wh = new();
wh["aaa"] = 1;
wh["bbb"] = 2;
Console.WriteLine("aaa:" + wh["aaa"]);
*/

/* 배열 생성
Member[] arr = new Member[] { new Member(1, "aaa"), new Member(2, "bbb") };
foreach (Member member in arr) {
    Console.WriteLine(member);
}
*/

/* setter getter
Class1 c1 = new Class1();
c1.setNum(1);
c1.setName("name");
Console.WriteLine(c1);  // ToString()의 반환값
Console.WriteLine(c1.GetHashCode());
Console.WriteLine("num:" + c1.getNum() + " / name:" + c1.getName());
*/

/* 객체 생성
foreach (var arg in args)
{
    Console.WriteLine(arg);
    Class1 c;   // Class1 타입의 참조값을 담을 참조 변수 선언
    c = new Class1();   // new가 나와야 메모리 할당 받아 객체 생성된 거임. 힙에 객체를 생성해서 그 참조값을 c에 저장
    Class1 c2 = c;  // c가 갖는 참조값을 c2에 복사 (주소값만 복사됨)

}
*/