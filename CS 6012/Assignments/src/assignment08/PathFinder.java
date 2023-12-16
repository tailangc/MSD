package assignment08;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Queue;


public class PathFinder {
    public static void solveMaze(String inputFile, String outputFile) {
        try (BufferedReader input = new BufferedReader(new FileReader(inputFile));
             PrintWriter output = new PrintWriter(new FileWriter(outputFile))) {

            String[] dimensions = input.readLine().split(" ");
            int height = Integer.parseInt(dimensions[0]);
            int width = Integer.parseInt(dimensions[1]);

            char[][] maze = new char[height][width];
            for (int i = 0; i < height; i++) {
                String line = input.readLine();
                maze[i] = line.toCharArray();
            }
            char[][] solution = findShortestPath(maze);
            output.println(height + " " + width);
            for (int i = 0; i < height; i++) {
                output.println(new String(solution[i]));
            }
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static char[][] findShortestPath(char[][] maze) {
        int height = maze.length;
        int width = maze[0].length;
        Graph graph = new Graph(height * width);
        Node start = null;
        Node goal = null;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (maze[i][j] == 'S') {
                    start = new Node(i * width + j);
                } else if (maze[i][j] == 'G') {
                    goal = new Node(i * width + j);
                }
                if (maze[i][j] != 'X') {
                    addEdges(graph, maze, i, j);
                }
            }
        }
        bfs(graph, start, goal);
        reconstructPath(maze, start, goal);
        return maze;
    }

    private static void addEdges(Graph graph, char[][] maze, int i, int j) {
        int height = maze.length;
        int width = maze[0].length;
        int currentIndex = i * width + j;
        //check left
        if (j > 0 && maze[i][j - 1] != 'X') {
            graph.addEdge(currentIndex, i * width + (j - 1));
        }
        //check right
        if (j < width - 1 && maze[i][j + 1] != 'X') {
            graph.addEdge(currentIndex, i * width + (j + 1));
        }
        //check up
        if (i > 0 && maze[i - 1][j] != 'X') {
            graph.addEdge(currentIndex, (i - 1) * width + j);
        }
        //check down
        if (i < height - 1 && maze[i + 1][j] != 'X') {
            graph.addEdge(currentIndex, (i + 1) * width + j);
        }
    }


    private static void bfs(Graph graph, Node start, Node goal) {
        Queue<Node> queue = new LinkedList<>();
        queue.add(start);
        while (!queue.isEmpty()) {
            Node current = queue.poll();

            for (Node neighbor : graph.getNeighbors(current.getIndex())) {

                if (!neighbor.isVisited()) {
                    neighbor.setVisited(true);
                    neighbor.setParent(current);
                    queue.add(neighbor);
                    if (neighbor.equals(goal)) {
                        goal.setParent(current);
                        return;
                    }

                }

            }
        }
    }


    private static void reconstructPath(char[][] maze, Node start, Node goal) {
        Node current = goal.getParent();
        System.out.println("find path");
        System.out.println(current.getIndex());
        while (current != null && current != start) {
            System.out.println(current.getIndex());
            int i = current.getIndex() / maze[0].length;
            int j = current.getIndex() % maze[0].length;

            maze[i][j] = '.';

            current = current.getParent();
        }
    }
    public static void main(String[] args) {
        PathFinder.solveMaze("input.txt", "output.txt");
    }
}

class Graph {
    private int vertices;
    private boolean[][] adjacencyMatrix;
    public Graph(int vertices) {
        this.vertices = vertices;
        this.adjacencyMatrix = new boolean[vertices][vertices];
    }
    public void addEdge(int source, int destination) {
        this.adjacencyMatrix[source][destination] = true;
    }

    public LinkedList<Node> getNeighbors(int vertex) {
        LinkedList<Node> neighbors = new LinkedList<>();
        for (int i = 0; i < vertices; i++) {
            if (adjacencyMatrix[vertex][i]) {
                neighbors.add(new Node(i));
            }
        }
        return neighbors;
    }
}
class Node {
    private int index;
    private boolean visited;
    private Node parent;
    public Node(int index) {
        this.index = index;
        this.visited = false;
        this.parent = null;
    }
    public int getIndex() {
        return index;
    }
    public boolean isVisited() {
        return visited;
    }
    public void setVisited(boolean visited) {
        this.visited = visited;
    }
    public Node getParent() {
        return parent;
    }
    public void setParent(Node parent) {
        this.parent = parent;
    }
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Node node = (Node) obj;
        return index == node.index;
    }
    @Override
    public int hashCode() {
        return index;
    }
}