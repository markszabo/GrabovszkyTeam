using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RoutePlanning
{
    public class Graph
    {
        public Node start;
        public Node dest;
        public List<Node> nodes = new List<Node>();        
    }

    public class Node
    {
        public string name = "";
        public List<Node> neighbours = new List<Node>();
        public List<int> distances = new List<int>();
        public int dist;
        public Node prev;
        public bool visited = false;
        public int? x = null, y = null;

        public Node()
        { 
        
        }

        public Node(string name)
        {
            this.name = name;
        }

        public override string ToString()
        {
            return name + " n:" + neighbours.Count + " d:" + dist;
        }
    }
}
