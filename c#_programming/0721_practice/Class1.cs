using System;
using System.Collections.Generic;
using System.Linq;

namespace _0721_practice
{
    public class Person
    {
        private static int _nextId = 1;

        public int Id { get; private set; }
        public string Name { get; set; }
        public string Phone { get; set; }
        public Person(string name, string phone)
        {
            Id = _nextId++;
            Name = name;
            Phone = phone;
        }
        public override string ToString()
        {
            return $"번호: {Id}, 이름: {Name}, 전화: {Phone}";
        }
    }
    public class PersonManager
    {
        private List<Person> _people = new List<Person>();
        public void AddPerson(string name, string phone)
        {
            Person newPerson = new Person(name, phone);
            _people.Add(newPerson);
            Console.WriteLine($"[추가 완료] {name}님이 등록되었습니다. (할당된 번호: {newPerson.Id})");
        }
        public void SearchPerson(int id)
        {
            Person person = _people.FirstOrDefault(p => p.Id == id);

            if (person != null)
            {
                Console.WriteLine($"[검색 결과] {person}");
            }
            else
            {
                Console.WriteLine($"[검색 실패] {id}번 회원을 찾을 수 없습니다.");
            }
        }
        public void UpdatePhone(int id, string newPhone)
        {
            Person person = _people.FirstOrDefault(p => p.Id == id);

            if (person != null)
            {
                person.Phone = newPhone;
                Console.WriteLine($"[수정 완료] {id}번 회원의 전화번호가 {newPhone}으로 변경되었습니다.");
            }
            else
            {
                Console.WriteLine($"[수정 실패] {id}번 회원을 찾을 수 없습니다.");
            }
        }
        public void DeletePerson(int id)
        {
            Person person = _people.FirstOrDefault(p => p.Id == id);

            if (person != null)
            {
                _people.Remove(person);
                Console.WriteLine($"[삭제 완료] {id}번 회원의 정보가 삭제되었습니다.");
            }
            else
            {
                Console.WriteLine($"[삭제 실패] {id}번 회원을 찾을 수 없습니다.");
            }
        }
        public void PrintAll()
        {
            Console.WriteLine("========== 전체 목록 ==========");
            if (_people.Count == 0)
            {
                Console.WriteLine("등록된 회원이 없습니다.");
            }
            else
            {
                foreach (var person in _people)
                {
                    Console.WriteLine(person);
                }
            }
            Console.WriteLine("===============================");
        }
    }
}