using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1
{
    public class Product
    {
        // 상품번호 자동 할당을 위한 정적 변수
        private static int _autoIncrementId = 0;

        // 속성 정의
        public int Id { get; private set; }
        public string Name { get; set; }
        public decimal Price { get; set; }
        public int Quantity { get; set; }

        public Product()
        {
            Id = ++_autoIncrementId;
            Name = "Unknown";
            Price = 0;
            Quantity = 0;
        }
        public Product(string name, decimal price, int quantity)
        {
            Id = ++_autoIncrementId;
            Name = name;
            Price = price;
            Quantity = quantity;
        }
        public override string ToString()
        {
            return $"[ID: {Id}] {Name} (가격: {Price:N0}원, 수량: {Quantity}개)";
        }
    }
    public class Warehouse
    {
        private Dictionary<string, int> _inventory = new();
        private Dictionary<int, Product> _rooms = new();

        private int _nextRoomNumber = 101;

        public int TotalItems => _inventory.Count;

        public int this[string name]
        {
            get => _inventory.ContainsKey(name) ? _inventory[name] : 0;
            set => _inventory[name] = value;
        }
        public Product this[int roomNumber]
        {
            get => _rooms.ContainsKey(roomNumber) ? _rooms[roomNumber] : null;
        }
        public Dictionary<int, Product> GetAllRooms()
        {
            return _rooms;
        }
        public int StoreProduct(Product product)
        {
            int roomNumber = _nextRoomNumber++;
            _rooms[roomNumber] = product;
            this[product.Name] += product.Quantity;
            return roomNumber;
        }
        public bool RemoveProduct(int roomNumber)
        {
            if (_rooms.ContainsKey(roomNumber))
            {
                Product p = _rooms[roomNumber];
                this[p.Name] -= p.Quantity;
                if (this[p.Name] <= 0)
                {
                    _inventory.Remove(p.Name);
                }

                _rooms.Remove(roomNumber);
                return true;
            }
            return false;
        }
    }
    public class Service
    {
        private Warehouse _warehouse = new Warehouse();
        public void AddProduct(string name, decimal price, int quantity)
        {
            Product newProduct = new Product(name, price, quantity);
            int roomNumber = _warehouse.StoreProduct(newProduct);
            Console.WriteLine($"[추가 완료] '{name}'이(가) 방 {roomNumber}호에 저장되었습니다.");
        }
        public void SearchProduct(int roomNumber)
        {
            Product foundProduct = _warehouse[roomNumber];
            if (foundProduct != null)
                Console.WriteLine($"[검색 결과] 방 {roomNumber}호: {foundProduct}");
            else
                Console.WriteLine($"[검색 실패] 방 {roomNumber}호는 비어있거나 없는 방입니다.");
        }
        public void UpdateProduct(int roomNumber, decimal newPrice, int newQuantity)
        {
            Product product = _warehouse[roomNumber];
            if (product != null)
            {
                _warehouse[product.Name] -= product.Quantity;
                product.Price = newPrice;
                product.Quantity = newQuantity;
                _warehouse[product.Name] += product.Quantity;

                Console.WriteLine($"[수정 완료] 방 {roomNumber}호의 정보가 성공적으로 변경되었습니다.");
            }
            else
            {
                Console.WriteLine($"[수정 실패] 방 {roomNumber}호를 찾을 수 없습니다.");
            }
        }
        public void DeleteProduct(int roomNumber)
        {
            bool isSuccess = _warehouse.RemoveProduct(roomNumber);
            if (isSuccess)
                Console.WriteLine($"[삭제 완료] 방 {roomNumber}호의 상품이 삭제되었습니다.");
            else
                Console.WriteLine($"[삭제 실패] 방 {roomNumber}호를 찾을 수 없습니다.");
        }
        public void PrintAll()
        {
            var rooms = _warehouse.GetAllRooms();

            Console.WriteLine("\n=== [창고 내 전체 상품 목록] ===");
            if (rooms.Count == 0)
            {
                Console.WriteLine("보관 중인 상품이 없습니다.");
            }
            else
            {
                foreach (var kvp in rooms)
                {
                    Console.WriteLine($"방 {kvp.Key}호 -> {kvp.Value}");
                }
            }
            Console.WriteLine("================================\n");
        }

        /* V2
        internal class Member {
        public int Num { get; set; } // 속성 내부에 private int num을 자동 생성
        public string Name { get; set; }
        public Member(int num, string name) {
            Num = num;
            Name = name;
        }
        public override string ToString() {
            return Num + " / " + Name;
        }
        */

        /* V1
        private int num;
        private string name;

        public void setNum(int num) { this.num = num; }
        public void setName(string name) { this.name = name; }
        public int getNum() { return num; }
        public string getName() { return name; }
        */
    }
}
