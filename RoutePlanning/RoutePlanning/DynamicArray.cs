using System;
using System.Collections.Generic;
using System.Collections;

namespace RoutePlanning
{
    class DynamicArray<T> : IList<T>
    {
        const int DEFAULT_SIZE = 100;

        T[] array = null;
        int top = 0;

        public DynamicArray()
            : this(DEFAULT_SIZE)
        {

        }

        public DynamicArray(int size)
        {
            array = new T[size];
        }

        public int Count
        {
            get { return top; }
        }

        public void Add(T elem)
        {
            if (IsFull())
            {
                T[] newarray = new T[array.Length * 2];
                Array.Copy(array, newarray, array.Length);
                array = newarray;
            }
            array[top++] = elem;
        }

        public void RemoveAt(int index)
        {
            CheckIndex(index);
            if (index != top - 1)
                Array.Copy(array, index + 1, array, index, top - index - 1);
            top--;
        }

        bool IsFull()
        {
            return top == array.Length;
        }

        public int IndexOf(T item)
        {
            return Array.IndexOf<T>(array, item, 0, top);
        }

        public void Insert(int index, T item)
        {
            CheckIndex(index);
            if (IsFull())
            {
                T[] newarray = new T[array.Length * 2];
                Array.Copy(array, 0, newarray, 0, index);
                Array.Copy(array, index, newarray, index + 1, top - index);
                array = newarray;
            }
            else
            {
                Array.Copy(array, index, array, index + 1, top - index);
            }

            array[index] = item;
            top++;
        }

        public T this[int index]
        {
            get
            {
                CheckIndex(index);
                return array[index];
            }
            set
            {
                CheckIndex(index);
                array[index] = value;
            }
        }

        private void CheckIndex(int index)
        {
            if (index < 0 || index >= top)
                throw new IndexOutOfRangeException();
        }
        
        public void Clear()
        {
            top = 0;
        }

        public bool Contains(T item)
        {
            return IndexOf(item) != -1;
        }

        public void CopyTo(T[] array, int arrayIndex)
        {
            CheckIndex(arrayIndex);
            Array.Copy(this.array, arrayIndex, array, 0, top);
        }

        public bool IsReadOnly
        {
            get { return false; }
        }

        public bool Remove(T item)
        {
            int idx = IndexOf(item);
            if (idx == -1)
                return false;
            RemoveAt(idx);
            return true;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return new Enumerator(this);
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return new Enumerator(this);
        }

        public struct Enumerator : IEnumerator<T>, IDisposable, IEnumerator
        {
            DynamicArray<T> array;
            int currIndex;
            T current;

            public Enumerator(DynamicArray<T> array)
            {
                this.array = array;
                currIndex = 0;
                current = default(T);
            }

            public T Current
            {
                get { return current; }
            }

            public void Dispose()
            {
                
            }

            object IEnumerator.Current
            {
                get { return Current; }
            }

            public bool MoveNext()
            {
                if (currIndex < array.Count)
                {
                    current = array[currIndex];
                    currIndex++;
                    return true;
                }
                return false;
            }

            public void Reset()
            {
                currIndex = 0;
            }
        }
    }
}
