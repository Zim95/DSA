#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the bfs function below.

def create_graph(n):
    graph = {}
    visited = {}
    distance = {}
    for i in range(1, n + 1):
        graph[i] = set()
        visited[i] = False
        distance[i] = -1
    return graph, visited, distance


def add_edges(graph, edges):
    for edge in edges:
        graph[edge[0]].add(edge[1])
        graph[edge[1]].add(edge[0])
    return graph


def bfs(edges, n=70, m=1988, s=16):
    # create a graph and visited
    graph, visited, distance = create_graph(n)
    # add edges
    graph = add_edges(graph, edges)
    # get start node and start bfs
    queue = [(s, 0)]
    while queue:
        # get node_id and distance to node
        node_id, d = queue[0]
        # add distance
        distance[node_id] = d
        visited[node_id] = True
        # get connections
        connections = graph[node_id]
        # increment d by 6
        d = d + 6
        # append to queue
        for connection in connections:
            if visited[connection]:
                continue
            queue.append((connection, d))
        # update queue
        queue = queue[1:]
    distances = []
    for node_id, distance in distance.items():
        if node_id == s:
            continue
        distances.append(str(distance))
    return ' '.join(distances)


if __name__ == '__main__':
    q = int(input())

    for q_itr in range(q):
        nm = input().split()

        n = int(nm[0])

        m = int(nm[1])

        edges = []

        for _ in range(m):
            edges.append(list(map(int, input().rstrip().split())))

        s = int(input())

        result = bfs(n, m, edges, s)

        print(result)
