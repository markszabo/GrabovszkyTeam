using System;

using System.Linq;
using System.Text;
using System.Collections.Generic;

namespace RoutePlanning
{
    class PriorityQueue_DA<T>
    {
        DynamicArray<T> elements;
        IComparer<T> comparer;
        public PriorityQueue_DA(IComparer<T> comparer)
        {
            elements = new DynamicArray<T>();
            this.comparer = comparer;
        }

        public void Add(T element)
        {
            for (int i = 0; i < elements.Count; i++)
            {
                if (comparer.Compare(elements[i], element) <= 0)
                {
                    elements.Insert(i, element);
                    return;
                }
            }
            elements.Add(element);
        }

        public int Count
        {
            get { return elements.Count; }
        }

        public void RemoveAt(int i)
        {
            elements.RemoveAt(i);
        }

        public T GetFirst()
        {
            return elements[0];
        }

        public T GetLast()
        {
            return elements[elements.Count - 1];
        }

        public T PopFirst()
        {
            T elem = GetFirst();
            elements.RemoveAt(0);
            return elem;
        }

        public T PopLast()
        {
            T elem = GetLast();
            elements.RemoveAt(elements.Count - 1);
            return elem;
        }

        public T this[int idx]
        {
            get { return elements[idx]; }
        }

        public bool Contains(T elem)
        {
            return elements.Contains(elem);
        }

        internal void Remove(T elem)
        {
            elements.Remove(elem);
        }
    }
}