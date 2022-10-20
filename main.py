from __future__ import annotations

from queue import PriorityQueue


class Node:
    def __init__(self, val: int):
        self.val = val
        self.neighbours = set()

    def add_neighbour(self, neighbour: Node, edge_weight: int):
        self.neighbours.add((neighbour, edge_weight))

    def get_val(self):
        return self.val

    def get_neighbours(self):
        return self.neighbours

    def __lt__(self, other):
        return self.val < other.val

    def __gt__(self, other):
        return self.val > other.val


class Graph:

    def __init__(self, file: str):
        self.nodes = []
        self.read_from_file(file)

    def read_from_file(self, file: str):
        with open(file) as file:
            lines = file.read().splitlines()
            
        edge_count = int(lines[0].split(" ")[1])
        self.clients = [int(client) for client in lines[1].split(" ")]
        for i in range(edge_count):
            start_node, end_node, latency = lines[i + 2].split(" ")
            start = Node(int(start_node))
            end = Node(int(end_node))
            present_start = self.get_node(start)
            present_end = self.get_node(end)
            if not present_start:
                start.add_neighbour(end if not present_end else present_end, int(latency))
                self.nodes.append(start)
            else:
                node = self.get_node(start)
                node.add_neighbour(end if not present_end else present_end, int(latency))
            if not present_end:
                end.add_neighbour(start if not present_start else present_start, int(latency))
                self.nodes.append(end)
            else:
                node = self.get_node(end)
                node.add_neighbour(start if not present_start else present_start, int(latency))

    def get_node(self, q_node: Node):
        for node in self.nodes:
            if node == q_node:
                return node
        return None

    def print(self):
        for node in self.nodes:
            print(node)


class Solution:
    def __init__(self, file: str, fileout: str):
        self.fileout = fileout
        self.network = Graph(file)

    def write_to_file(self, val: int):
        with open(self.fileout, "w") as fileout:
            fileout.write(str(val))

    def dijkstra(self, start: Node):
        node_distance = {node: float('inf') for node in self.network.nodes if node != start}
        node_distance[start] = 0
        q = PriorityQueue()
        q.put((0, start))
        for node in self.network.nodes:
            if node != start:
                node_distance[node] = float('inf')
        while not q.empty():
            curr_distance, curr_node = q.get()
            for neighbour in curr_node.get_neighbours():
                neighbour_node, edge_weight = neighbour
                if node_distance[curr_node] + edge_weight < node_distance[neighbour_node]:
                    node_distance[neighbour_node] = node_distance[curr_node] + edge_weight
                    q.put((node_distance[neighbour_node], neighbour_node))
        return node_distance

    def get_minimal_delay(self):
        max_delay_list = []
        for node in self.network.nodes:
            if node.value not in self.network.clients:
                curr_node_distance = self.dijkstra(node)
                curr_delays_list = []
                for curr_node, distance in curr_node_distance.items():
                    if curr_node.value in self.network.clients:
                        curr_delays_list.append(distance)
                max_delay_list.append(max(curr_delays_list))
        self.write_to_file(min(max_delay_list))
        return min(max_delay_list)
