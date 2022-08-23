#!/bin/python3

import math
import os
import random
import re
import sys


'''
Problem - https://www.hackerrank.com/
challenges/journey-to-the-moon/problem
'''


sys.setrecursionlimit(10 ** 6)


def dfs(node_id, graph, visited, connected_comps):
    connections = graph[node_id]
    for connection in connections:
        if visited[connection]:
            continue
        else:
            visited[connection] = True
            c, v = dfs(connection, graph, visited, connected_comps)
            connected_comps = c
            visited = v
    connected_comps.append(node_id)
    return connected_comps, visited


def get_possible_ways(connected_groups):
    total = 0
    result = 0
    for size in connected_groups:
        result += size * total
        total += size
    return result


def journeyToMoon(n, astronaut):
    graph = {}
    visited = {}

    # create graph and visited
    for i in range(0, n):
        graph[i] = []
        visited[i] = False

    # add the edges
    for astro_pair in astronaut:
        graph[astro_pair[0]].append(astro_pair[1])
        graph[astro_pair[1]].append(astro_pair[0])

    connected_groups = []
    for node_id, connections in graph.items():
        if visited[node_id]:
            continue
        if not connections:
            connected_groups.append(1)
            continue
        visited[node_id] = True
        connected_group, v = dfs(node_id, graph, visited, [])
        visited = v
        connected_groups.append(len(connected_group))
    possible_ways = get_possible_ways(connected_groups)
    return possible_ways


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    np = input().split()

    n = int(np[0])

    p = int(np[1])

    astronaut = []

    for _ in range(p):
        astronaut.append(list(map(int, input().rstrip().split())))

    result = journeyToMoon(n, astronaut)

    fptr.write(str(result) + '\n')

    fptr.close()
