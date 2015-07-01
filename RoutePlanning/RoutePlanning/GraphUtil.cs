using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Diagnostics;

namespace RoutePlanning
{
    static class GraphUtil
    {
        public static Graph BuildGraph(string filename)
        {
            DateTime t1 = DateTime.Now;
            Bitmap bmp = (Bitmap)((Bitmap)Image.FromFile(filename)).Clone();
            Node[,] pixels = new Node[bmp.Height, bmp.Width];
            Node start = null;
            Node dest = null;
            for (int i = 0; i < bmp.Width; i++)
            {
                for (int j = 0; j < bmp.Height; j++)
                {
                    Color c = bmp.GetPixel(i, j);
                    if (!colorEq(Color.Black, c))
                    {
                        pixels[j, i] = new Node();
                        pixels[j, i].name = j + " " + i;
                        if (colorEq(Color.FromArgb(0,255,0), c))
                            start = pixels[j, i];
                        else if (colorEq(Color.Red, c))
                            dest = pixels[j, i];
                    }
                }
            }

            for (int i = 0; i < bmp.Height; i++)
            {
                for (int j = 0; j < bmp.Width; j++)
                {
                    if (pixels[i, j] == null)
                        continue;

                    int ni, nj; 
                    ni = i - 1;
                    nj = j;
                    if (inArray(pixels, ni, nj) && pixels[ni, nj] != null) pixels[i, j].neighbours.Add(pixels[ni, nj]);                                   
                    ni = i;
                    nj = j + 1;
                    if (inArray(pixels, ni, nj) && pixels[ni, nj] != null) pixels[i, j].neighbours.Add(pixels[ni, nj]);
                    ni = i;
                    nj = j - 1;
                    if (inArray(pixels, ni, nj) && pixels[ni, nj] != null) pixels[i, j].neighbours.Add(pixels[ni, nj]);
                    ni = i + 1;
                    nj = j;
                    if (inArray(pixels, ni, nj) && pixels[ni, nj] != null) pixels[i, j].neighbours.Add(pixels[ni, nj]);
                   

                    for (int n = 0; n < pixels[i, j].neighbours.Count; n++)
                    {
                        pixels[i, j].distances.Add(1);
                    }
                }
            }
            Graph g = new Graph();
            foreach (var n in pixels)
            {
                if (n != null)
                    g.nodes.Add(n);
            }
            g.start = start;
            g.dest = dest;
            DateTime t2 = DateTime.Now;
            Debug.WriteLine("imread, graph build: " + (t2 - t1).TotalMilliseconds + "ms");
            return g;
        }

        public static List<Node> GetPath(Graph g)
        {
            DateTime t1 = DateTime.Now;

            List<Node> unvis = new List<Node>();
            foreach (var n in g.nodes)
            {
                if (n != g.start)
                    n.dist = g.nodes.Count + 5;
                else
                    n.dist = 0;
                unvis.Add(n);
            }

            TimeSpan minsec = TimeSpan.Zero;
            while (unvis.Count > 0) // && g.dest.visited == false)
            {
                DateTime t11 = DateTime.Now;
                Node curr = getmin(unvis, g);
                DateTime t21 = DateTime.Now;
                minsec += (t21 - t11);

                for (int i = 0; i < curr.neighbours.Count; i++)
                {
                    Node currn = curr.neighbours[i];
                    if (currn.visited)
                        continue;

                    if (currn.dist > curr.dist + curr.distances[i])
                    {
                        currn.prev = curr;
                        currn.dist = curr.dist + curr.distances[i];
                    }
                }
                unvis.Remove(curr);
                curr.visited = true;
            }

            DateTime t2 = DateTime.Now;
            Debug.WriteLine("getpath: " + (t2 - t1).TotalMilliseconds + "ms");
            Debug.WriteLine("where getmin: " + minsec.TotalMilliseconds + "ms");
            return GetPathFromNode(g, g.start);
        }

        public static List<Node> GetPath_DA(Graph g)
        {
            DateTime t1 = DateTime.Now;

            DynamicArray<Node> unvis = new DynamicArray<Node>();
            foreach (var n in g.nodes)
            {
                if (n != g.start)
                    n.dist = g.nodes.Count + 5;
                else
                    n.dist = 0;
                unvis.Add(n);
            }

            TimeSpan minsec = TimeSpan.Zero;
            while (unvis.Count > 0) // && g.dest.visited == false)
            {
                DateTime t11 = DateTime.Now;
                Node curr = getmin(unvis, g);
                DateTime t21 = DateTime.Now;
                minsec += (t21 - t11);

                for (int i = 0; i < curr.neighbours.Count; i++)
                {
                    Node currn = curr.neighbours[i];
                    if (currn.visited)
                        continue;

                    if (currn.dist > curr.dist + curr.distances[i])
                    {
                        currn.prev = curr;
                        currn.dist = curr.dist + curr.distances[i];
                    }
                }
                unvis.Remove(curr);
                curr.visited = true;
            }

            DateTime t2 = DateTime.Now;
            Debug.WriteLine("getpath: " + (t2 - t1).TotalMilliseconds + "ms");
            Debug.WriteLine("where getmin: " + minsec.TotalMilliseconds + "ms");
            return GetPathFromNode(g, g.start);
        }
        
        public static List<Node> GetPathPQ(Graph g)
        {
            DateTime t1 = DateTime.Now;

            PriorityQueue<Node> open = new PriorityQueue<Node>(new NodeComp(g));
            foreach (var n in g.nodes)
            {
                if (n != g.start)
                    n.dist = int.MaxValue / 3;
                else
                    n.dist = 0;
            }
            open.Add(g.start);

            TimeSpan minsec = TimeSpan.Zero;
            while (open.Count > 0) // && g.dest.visited == false)
            {
                DateTime t11 = DateTime.Now;
                Node curr = open.PopFirst();
                DateTime t21 = DateTime.Now;
                minsec += (t21 - t11);

                for (int i = 0; i < curr.neighbours.Count; i++)
                {
                    Node currn = curr.neighbours[i];
                    if (currn.dist > curr.dist + curr.distances[i])
                    {
                        currn.prev = curr;
                        currn.dist = curr.dist + curr.distances[i];
                        if (!open.Contains(currn))
                            open.Add(currn);
                    }
                }
                curr.visited = true;
            }

            DateTime t2 = DateTime.Now;
            Debug.WriteLine("getpath: " + (t2 - t1).TotalMilliseconds + "ms");
            Debug.WriteLine("where getmin: " + minsec.TotalMilliseconds + "ms");
            return GetPathFromNode(g, g.dest);
        }

        public static List<Node> GetPathPQ_DA(Graph g)
        {
            DateTime t1 = DateTime.Now;

            PriorityQueue_DA<Node> open = new PriorityQueue_DA<Node>(new NodeComp(g));
            foreach (var n in g.nodes)
            {
                if (n != g.start)
                    n.dist = int.MaxValue / 3;
                else
                    n.dist = 0;
            }
            open.Add(g.start);

            TimeSpan minsec = TimeSpan.Zero;
            while (open.Count > 0) // && g.dest.visited == false)
            {
                DateTime t11 = DateTime.Now;
                Node curr = open.PopFirst();
                DateTime t21 = DateTime.Now;
                minsec += (t21 - t11);

                for (int i = 0; i < curr.neighbours.Count; i++)
                {
                    Node currn = curr.neighbours[i];
                    if (currn.dist > curr.dist + curr.distances[i])
                    {
                        currn.prev = curr;
                        currn.dist = curr.dist + curr.distances[i];
                        if (!open.Contains(currn))
                            open.Add(currn);
                    }
                }
                curr.visited = true;
            }

            DateTime t2 = DateTime.Now;
            Debug.WriteLine("getpath: " + (t2 - t1).TotalMilliseconds + "ms");
            Debug.WriteLine("where getmin: " + minsec.TotalMilliseconds + "ms");
            return GetPathFromNode(g, g.dest);
        }

        public static List<Node> GetPathFromNode(Graph g, Node start)
        {
            if (g == null || start == null)
                return null;
            List<Node> path = new List<Node>();
            for (Node node = start; node.prev != null; node = node.prev)
            {
                path.Insert(0, node);
            }
            return path;  
        }

        public const float q = 0f;

        //static Node getmin(IList<Node> unvis, Graph g)
        //{
        //    if (unvis.Count == 0) return null;
        //    Node curr = unvis[0];
        //    int cx, cy;
        //    GetCoords(curr, out cx, out cy);
        //    foreach (var n in unvis)
        //    {
        //        int nx, ny;
        //        GetCoords(n, out nx, out ny);
        //        int dx, dy;
        //        GetCoords(g.dest, out dx, out dy);

        //        if (n.dist + q * Math.Abs(nx + ny - dx - dy) < curr.dist + q * Math.Abs(cx + cy - dx - dy))
        //        {
        //            curr = n;
        //            GetCoords(curr, out cx, out cy);
        //        }
        //    }
        //    return curr;
        //}

        static Node getmin(IList<Node> unvis, Graph g)
        {
            if (unvis.Count == 0) return null;
            Node curr = unvis[0];
            int cx, cy;
            GetCoords(curr, out cx, out cy);
            for(int i = 0; i < unvis.Count; ++i)
            {
                Node n = unvis[i];
                int nx, ny;
                GetCoords(n, out nx, out ny);
                int dx, dy;
                GetCoords(g.dest, out dx, out dy);

                if (n.dist + q * Math.Abs(nx + ny - dx - dy) < curr.dist + q * Math.Abs(cx + cy - dx - dy))
                {
                    curr = n;
                    GetCoords(curr, out cx, out cy);
                }
            }
            return curr;
        }

        static bool colorEq(Color c1, Color c2)
        {
            return c1.R == c2.R && c1.G == c2.G && c1.B == c2.B;
        }
        static bool inArray(Node[,] pixels, int r, int c)
        {
            return 0 <= r && 0 <= c && r < pixels.GetLength(0) && c < pixels.GetLength(1);
        }

        public static Bitmap DrawPath(Bitmap bmp, List<Node> path, int pixelsize, Graph g = null, bool drawdist = false)
        {
            if (path == null)
                return null;
            DateTime t1 = DateTime.Now;
            Bitmap newbmp = (Bitmap)bmp.Clone();
            Graphics gfx1 = Graphics.FromImage(newbmp);

            foreach (var n in path)
            {
                int x, y;
                GetCoords(n, out x, out y);
                Color c = bmp.GetPixel(x, y);
                if (!colorEq(c, Color.Red) && !colorEq(c, Color.Green))
                {
                    newbmp.SetPixel(x, y, Color.Orange);
                }
            }

            if(g!= null)
                foreach (var n in g.nodes)
                {
                    int x, y;
                    GetCoords(n, out x, out y);
                    if (n.visited && colorEq(newbmp.GetPixel(x, y), Color.White))
                        newbmp.SetPixel(x, y, Color.LightGray);
                }
            Bitmap bigbmp = DrawBitmapBig(newbmp, pixelsize);
            Graphics gfx = Graphics.FromImage(bigbmp);

            if (g != null && drawdist)
                foreach (var n in g.nodes)
                {
                    int x, y;
                    GetCoords(n, out x, out y);
                    if (n.visited && colorEq(bmp.GetPixel(x, y), Color.White))
                    {
                        gfx.DrawString(n.dist.ToString(), new Font("Arial", 7), new SolidBrush(Color.Black), new PointF(x* pixelsize, y*pixelsize));
                    }
                }

            DateTime t2 = DateTime.Now;
            Debug.WriteLine("drawpath: " + (t2 - t1).TotalMilliseconds + "ms");
            return bigbmp;
        }
        public static void GetCoords(Node node, out int x, out int y)
        {
            if (node.x.HasValue && node.y.HasValue)
            {
                x = node.x.Value;
                y = node.y.Value;
                return;
            }
                
            string[] ss = node.name.Split(new char[] { ' ' });
            x = Convert.ToInt32(ss[1]);
            y = Convert.ToInt32(ss[0]);
            node.x = x;
            node.y = y;
        }
        static Bitmap DrawBitmapBig(Bitmap bmp, int zoomsize)
        {
            Bitmap newbmp = new Bitmap(bmp.Width * zoomsize, bmp.Height * zoomsize);
            Graphics gfx = Graphics.FromImage(newbmp);
            for (int i = 0; i < bmp.Width; i++)
            {
                for (int j = 0; j < bmp.Height; j++)
                {
                    Color c = bmp.GetPixel(i, j);
                    gfx.FillRectangle(new SolidBrush(c), i * zoomsize, j * zoomsize, zoomsize, zoomsize);
                    //for (int ii = 0; ii < zoomsize; ii++)
                    //{
                    //    for (int jj = 0; jj < zoomsize; jj++)
                    //    {
                    //        newbmp.SetPixel(i * zoomsize + ii, j * zoomsize + jj, c);
                    //    }
                    //}
                }
            }
            return newbmp;
        }
    }

    class NodeComp : IComparer<Node>
    {
        Graph g;
        public NodeComp(Graph g)
        {
            this.g = g;
        }
        //const float q = 1f;
        public int Compare(Node n1, Node n2)
        {
            int x1, y1, x2, y2, dx, dy;
            GraphUtil.GetCoords(n1, out x1, out y1);
            GraphUtil.GetCoords(n2, out x2, out y2);
            GraphUtil.GetCoords(g.dest, out dx, out dy);
            return -(int)(n1.dist + GraphUtil.q * Math.Abs(x1 + y1 - dx - dy) - n2.dist + GraphUtil.q * Math.Abs(x2 + y2 - dx - dy));
        }
    }
}
