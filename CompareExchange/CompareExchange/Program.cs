using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Test2019
{
    class Node
    { // Linked List
        public int Key;
        public Node next;
        private static Mutex mutex = new Mutex();

        Node _head;
        public void Init_Link()
        { // Linked List를 초기화
            _head = new Node();
            _head.next = null;
        }

        public int InsertNode_by_CAS(int Key)
        { // Interlocked.CompareExchage()를 이용한 Node 삽입
            Node tempNode;
            if ((tempNode = new Node()) == null)
            {
                Console.WriteLine("Nope");
                return -1;
            }
            try
            {
                while (true)
                {
                    tempNode.Key = Key;
                    tempNode.next = _head.next;
                    if (Interlocked.CompareExchange(ref _head.next, tempNode, tempNode.next) == tempNode.next)
                        break;
                }
                return Key;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }
        }

        public int DeleteNode_by_CAS()
        { // Interlocked.CompareExchage()를 이용한 Node 삭제
            Node tempNode;
            int i;
            if (_head.next == null)
            {
                Console.WriteLine("Nope");
                return -1;
            }
            try
            {
                while (true)
                {
                    tempNode = _head.next;
                    i = tempNode.Key;
                    if (Interlocked.CompareExchange(ref _head.next, tempNode.next, tempNode) == tempNode)
                        break;
                }

                return i;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }
        }

        public int InsertNode_by_Mutex(int Key)
        { // Metex를 이용한 Node 삽입
            Node tempNode;
            if ((tempNode = new Node()) == null)
            {
                Console.WriteLine("Nope(Insertion)");
                return -1;
            }
            try
            {
                mutex.WaitOne();

                tempNode.Key = Key;
                tempNode.next = _head.next;               
                _head.next = tempNode;

                mutex.ReleaseMutex();
              
                return Key;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }
        }

        public int DeleteNode_by_Mutex()
        { // Metex를 이용한 Node 삭제
            Node tempNode;
            int i;
            if (_head.next == null)
            {
                Console.WriteLine("Nope(Deletion)");
                return -1;
            }
            try
            {
                mutex.WaitOne();

                tempNode = _head.next;
                i = tempNode.Key;                
                _head.next = tempNode.next;

                mutex.ReleaseMutex();

                return i;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }
        }

        public void PrintNode()
        { // Linked List를 출력
            Node tempNode;
            tempNode = _head.next;
            while (tempNode != null)
            {
                Console.Write("{0} ", tempNode.Key);
                tempNode = tempNode.next;
            }
            Console.WriteLine();
        }

        public int CheckNode()
        { // Linked List의 Node 개수 Check
            Node tempNode = _head.next;
            int count = 0;

            while (tempNode != null)
            {
                count++;
                tempNode = tempNode.next;
            }

            return count;
        }
    }

    class Program
    {
        private static volatile int _val = 0;
        private static volatile int _val2 = 0;
        
        static void AddValue(int value)
        {
            while (true)
            {
                var orgVal = _val;
                var newVal = orgVal + value;
                if (Interlocked.CompareExchange(ref _val, newVal, orgVal) == orgVal)
                    break;
            }
        }
        static void ThreadBody_AddVal()
        {
            for (int i = 0; i < 100000; i++)
            { // Main 스레드와 병행 수행
                AddValue(1);
                _val2++;
            }

        }

        static void ThreadBody_Mutex(Node list)
        { // Mutex를 이용한 삽입 3번 삭제 2번 루틴을 20000번 반복
            for (int j = 0; j < 200000; j++)
            {
                for (int i = 0; i < 3; i++)
                {
                    list.InsertNode_by_Mutex(i);
                }
                for (int i = 0; i < 2; i++)
                {
                    list.DeleteNode_by_Mutex();
                }
            }
        }

        static void ThreadBody_CAS(Node list)
        { // Interlocked.CompareExchage()를 이용한 삽입 3번 삭제 2번 루틴을 20000번 반복
            for (int j = 0; j < 200000; j++)
            {
                for (int i = 0; i < 3; i++)
                {
                    list.InsertNode_by_CAS(i);
                }
                for (int i = 0; i < 2; i++)
                {
                    list.DeleteNode_by_CAS();
                }
            }
        }

        static void ThreadBody_CAS2(Node list)
        { // 5, 4 삽입, 삭제, 3, 2, 1 삽입, 삭제, 삭제, 0 삽입
            list.InsertNode_by_CAS(5);
            list.InsertNode_by_CAS(4);
            list.DeleteNode_by_CAS();
            list.InsertNode_by_CAS(3);
            list.InsertNode_by_CAS(2);
            list.InsertNode_by_CAS(1);
            list.DeleteNode_by_CAS();
            list.DeleteNode_by_CAS();
            list.InsertNode_by_CAS(0);
        }

        static void Main(string[] args)
        {
            Node list = new Node();
            list.Init_Link();

            Thread t_Mutex1 = new Thread(() => ThreadBody_Mutex(list));
            Thread t_Mutex2 = new Thread(() => ThreadBody_Mutex(list));
            Thread t_CAS1 = new Thread(() => ThreadBody_CAS2(list));
            Thread t_CAS2 = new Thread(() => ThreadBody_CAS2(list));
            Thread t_CAS3 = new Thread(() => ThreadBody_CAS2(list));
            Thread t_CAS4 = new Thread(() => ThreadBody_CAS2(list));
            Thread t_CAS5 = new Thread(() => ThreadBody_CAS(list));
            Thread t_CAS6 = new Thread(() => ThreadBody_CAS(list));

            Console.Write("2013630004 김현진\n\n");

            
            Console.WriteLine("1. AddVal(1)과 단순 덧셈(i++) 비교 (Thread 2개, 각 Thread 100000회)");
            Thread t = new Thread(ThreadBody_AddVal);
            t.Start();
            for (int i = 0; i < 100000; i++)
            { // 스레드 t와 병행 수행
                AddValue(1);
                _val2++;
            }
            t.Join();
            Console.WriteLine("AddVal(1) : {0}", _val);
            Console.WriteLine("단순덧셈 : {0}\n", _val2);
            

            Console.WriteLine("2. Interlocked.CompareExchage()를 이용한 Linked List 구현");
            Console.WriteLine("   Thread 5개, 각 Thread는 5, 4 삽입, 삭제, 3, 2, 1 삽입, 삭제, 삭제, 0 삽입\n");
            t_CAS1.Start(); t_CAS2.Start(); t_CAS3.Start(); t_CAS4.Start();
            ThreadBody_CAS2(list);
            t_CAS1.Join(); t_CAS2.Join(); t_CAS3.Join(); t_CAS4.Join();
            Console.Write("실행 결과 : "); list.PrintNode();
            Console.WriteLine("최종 Node의 개수 : {0}\n", list.CheckNode());
            list.Init_Link();
            

            
            Console.WriteLine("3. Mutex기법과 CompareExchage() 기법 성능 비교");
            Console.WriteLine("   Thread 3개씩, 각 Thread는 (삽입 3번 삭제 2번) 루틴을 200000번 반복\n");
            Stopwatch SW = new Stopwatch();
            string sTime;
            SW.Reset();

            Console.WriteLine("Mutex 사용 Linked List");
            SW.Start();
            t_Mutex1.Start();
            t_Mutex2.Start();
            ThreadBody_Mutex(list);
            t_Mutex1.Join();
            t_Mutex2.Join();
            if (SW.IsRunning)
            {
                SW.Stop();
                sTime = SW.Elapsed.ToString();
                Console.WriteLine("걸린 시간 : {0}", sTime);
            }
            Console.WriteLine("최종 Node 개수 : {0}\n", list.CheckNode());
            

            list.Init_Link();
            SW.Reset();

            Console.WriteLine("CompareExchage() 사용 Linked List");
            SW.Start();
            t_CAS5.Start(); t_CAS6.Start();
            ThreadBody_CAS(list);
            t_CAS5.Join(); t_CAS6.Join();
            if (SW.IsRunning)
            {
                SW.Stop();
                sTime = SW.Elapsed.ToString();
                Console.WriteLine("걸린 시간 : {0}", sTime);
            }
            Console.WriteLine("최종 Node 개수 : {0}", list.CheckNode());
            
        }
    }
}