using System;
using _0721_practice;

PersonManager manager = new PersonManager();
bool isRunning = true;

Console.WriteLine("회원 관리 프로그램을 시작합니다.");

while (isRunning)
{
    Console.WriteLine("\n=======================================================");
    Console.WriteLine("[1] 추가  [2] 검색  [3] 수정  [4] 삭제  [5] 전체목록  [0] 종료");
    Console.WriteLine("=======================================================");
    Console.Write("메뉴를 선택하세요: ");

    string choice = Console.ReadLine();

    switch (choice)
    {
        case "1":
            Console.Write("이름 입력: ");
            string name = Console.ReadLine();
            Console.Write("전화번호 입력: ");
            string phone = Console.ReadLine();
            manager.AddPerson(name, phone);
            break;

        case "2":
            Console.Write("검색할 회원 번호 입력: ");
            if (int.TryParse(Console.ReadLine(), out int searchId))
            {
                manager.SearchPerson(searchId);
            }
            else
            {
                Console.WriteLine("잘못된 입력입니다. 숫자만 입력해주세요.");
            }
            break;

        case "3":
            Console.Write("수정할 회원 번호 입력: ");
            if (int.TryParse(Console.ReadLine(), out int updateId))
            {
                Console.Write("새로운 전화번호 입력: ");
                string newPhone = Console.ReadLine();
                manager.UpdatePhone(updateId, newPhone);
            }
            else
            {
                Console.WriteLine("잘못된 입력입니다. 숫자만 입력해주세요.");
            }
            break;

        case "4":
            Console.Write("삭제할 회원 번호 입력: ");
            if (int.TryParse(Console.ReadLine(), out int deleteId))
            {
                manager.DeletePerson(deleteId);
            }
            else
            {
                Console.WriteLine("잘못된 입력입니다. 숫자만 입력해주세요.");
            }
            break;

        case "5":
            manager.PrintAll();
            break;

        case "0":
            Console.WriteLine("프로그램을 종료합니다.");
            isRunning = false;
            break;

        default:
            Console.WriteLine("잘못된 선택입니다. 0~5 사이의 숫자를 입력해주세요.");
            break;
    }
}